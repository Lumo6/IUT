Param ([parameter(Mandatory=$false)]
       [System.IO.FileInfo]$Doxyfile,
       [switch]$WarningToStdOut=$false)


function end_progress()
{
    $callstack = Get-PSCallStack
    $lst = new-object System.Collections.Generic.HashSet[string]
    foreach($call in $callstack)
    {
        [void]$lst.Add($call.ScriptName)
    }

    Write-Progress -Activity "MakeDox" -Completed -Id $lst.Count
}

function progress([string] $message)
{
    $callstack = Get-PSCallStack
    $lst = new-object System.Collections.Generic.HashSet[string]
    foreach($call in $callstack)
    {
        [void]$lst.Add($call.ScriptName)
    }

    if($VerbosePreference -ne [System.Management.Automation.ActionPreference]::SilentlyContinue) {
        Write-Output $message
    }
    Write-Progress -Activity "MakeDox" -CurrentOperation $message -Id $lst.Count
}

function GetParam([string[]] $DoxyParams, [string]$ParamName)
{
    [System.Collections.ArrayList]$Return = New-Object -TypeName System.Collections.ArrayList

    $continue = $false
    foreach($DoxyParam in $DoxyParams)
    {
        $DoxyParam = $DoxyParam -replace '#.*',''
        if(!$continue) {
            $DoxyParamSplit = $DoxyParam -split '=',2
            if($DoxyParamSplit[0].Trim() -eq $ParamName) {
                [void]$Return.Add(($DoxyParamSplit[1].Trim() -replace '\\$','').Trim())
                if($DoxyParamSplit[1].Trim() -match '\\$') {
                    $continue = $true
                } else {
                    break
                }
            }
        } else {
            [void]$Return.Add(($DoxyParam.Trim() -replace '\\$','').Trim())
            if(!($DoxyParam.Trim() -match '\\$')) {
                break
            }
        }
    }

    $Return
}

function CleanUnusefullLines([string[]] $DoxyParams)
{
    [System.Collections.ArrayList]$Return = New-Object -TypeName System.Collections.ArrayList

    foreach($DoxyParam in $DoxyParams)
    {
        $DoxyParam = ($DoxyParam -replace '#.*','').Trim();
        if($DoxyParam.Length -ne 0) {
            [void]$Return.Add($DoxyParam)
        }
    }

    $Return.ToArray()
}

function Max($val1, $val2)
{
    if($val1 -lt $val2) {
        $val2
    } else {
        $val1
    }
}

function GetLastTimestamp([System.Array]$InputDirsOrFiles)
{
    [System.DateTime]$InputTimestamp = 0
    foreach($InputDirOrFile in $InputDirsOrFiles)
    {
        $InputDirOrFile = $InputDirOrFile.Trim('"')
        if($InputDirOrFile.Length -ne 0) {
            $InputDirOrFile = [System.IO.Path]::GetFullPath($InputDirOrFile)
            if((Get-Item $InputDirOrFile) -is [System.IO.DirectoryInfo])
            {
                $InputDirOrFile = [System.IO.Path]::Combine($InputDirOrFile, '*')
                $files = Get-ChildItem -Path $InputDirOrFile -Include $DoxFilePatterns -Recurse:$DoxRecursive
                foreach($file in $files){
                    $InputTimestamp = Max $InputTimestamp $file.LastWriteTimeUtc
                }
            } else {
                $InputTimestamp = Max $InputTimestamp (Get-Item $InputDirOrFile).LastWriteTimeUtc
            }
        }
    }
    $InputTimestamp
}

[System.IO.Directory]::SetCurrentDirectory($PWD);

if($Doxyfile -eq $null)
{
    $Doxyfiles = Get-ChildItem .\*.dox
} else {
    Set-Location $Doxyfile.Directory.FullName;
    [System.IO.Directory]::SetCurrentDirectory($PWD);
    $Doxyfiles = @($Doxyfile)
}

foreach($Doxyfile in $Doxyfiles) {
    # Récupère la liste des fichier "INPUT"

    $DoxyParams = Get-Content $Doxyfile
    $DoxyParams = CleanUnusefullLines $DoxyParams

    $DoxInputs = GetParam -DoxyParams $DoxyParams -ParamName 'INPUT'
    $DoxImagePath = GetParam -DoxyParams $DoxyParams -ParamName 'IMAGE_PATH'
    $DoxRecursive = (GetParam -DoxyParams $DoxyParams -ParamName 'RECURSIVE') -eq 'YES'
    $DoxFilePatterns = GetParam -DoxyParams $DoxyParams -ParamName 'FILE_PATTERNS' | ForEach-Object {$_.Trim()}
    $DoxOutputDir = GetParam -DoxyParams $DoxyParams -ParamName 'OUTPUT_DIRECTORY'

    # trouve le timestamp le plus récent des fichiers d'entrée
    $InputTimestamp = $Doxyfile.LastWriteTimeUtc
    $temp = GetLastTimestamp $DoxInputs
    $InputTimestamp = Max $temp $InputTimestamp
    $temp = GetLastTimestamp $DoxImagePath
    $InputTimestamp = Max $temp $InputTimestamp

    # Trouve le timestamp du fichier de sortie
    if(Test-Path ([System.IO.Path]::Combine($DoxOutputDir, 'html\index.html'))) {
        $OutputTimestamp = (Get-Item ([System.IO.Path]::Combine($DoxOutputDir, 'html\index.html'))).LastWriteTimeUtc
    } else {
        $OutputTimestamp = [System.DateTime]0
    }

    if($InputTimestamp -gt $OutputTimestamp)
    {
        #Recherche doxygen.exe
        if(!(Test-Path ([System.IO.Path]::Combine($Env:DOXYGENDIR, 'bin\doxygen.exe')).ToString()))
        {
            Write-Warning "La variable d'environement DOXYGENDIR n'est pas définie ou définie à un mauvais emplacement."
            progress "Recherche de doxygen.exe"

            $doxygen = Get-ChildItem $env:ProgramW6432 -Name doxygen.exe -Recurse | ForEach-Object {if($_ -imatch 'bin\\doxygen\.exe$') {$_}}
        
            end_progress

            if($doxygen -eq $null) {
                Throw "Doxygen n'est pas installé !"
            }
            if($doxygen -is [array]) {
                $doxygen = $doxygen[0]
            }
            $doxygendir = [System.IO.Path]::Combine($env:ProgramW6432, ($doxygen -ireplace 'bin\\doxygen\.exe$',''))
            $doxygendir = $doxygendir.TrimEnd([System.IO.Path]::DirectorySeparatorChar)
            [System.Environment]::SetEnvironmentVariable('DOXYGENDIR', $doxygendir, 1)
            $env:DOXYGENDIR = $doxygendir
        }

        # Exécution de doxygen
        $out = & ([System.IO.Path]::Combine($Env:DOXYGENDIR, 'bin\doxygen.exe')).ToString() $Doxyfile 2>&1

        $DoVerbose = $VerbosePreference -ne [System.Management.Automation.ActionPreference]::SilentlyContinue

        [System.Collections.ArrayList]$Warnings = New-Object -TypeName System.Collections.ArrayList

        if($out -is [Array]) {
            foreach($outline in $out){
                if(($outline -is [String] -and $DoVerbose) -or ($outline -isnot [String] -and $WarningToStdOut)) {
                    Write-Host $outline.ToString()
                } elseif($outline -isnot [String]) {
                    [void]$Warnings.Add($outline.ToString())
                }
            }
        } else {
            if(($out -is [String] -and $DoVerbose) -or ($out -isnot [String] -and $WarningToStdOut)) {
                Write-Host $outline.ToString()
            } elseif($outline -isnot [String]) {
                [void]$Warnings.Add($out.ToString())
            }
        }
        if($Warnings.Count -ne 0) {
            $WarningsCct = -join $Warnings
            $WarningsArr = $WarningsCct -split "`n"
            foreach($Warning in $WarningsArr) {
                if($Warning.Trim().Length -ne 0) {
                    Write-Warning $Warning
                }
            }
        }
    }
}