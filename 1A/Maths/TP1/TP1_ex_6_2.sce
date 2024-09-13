function SN = sommeRecursive(N)
    if N == 0
        SN = 0;
    else
        SN = N + sommeRecursive(N - 1);
    end
endfunction

N = 10; 
resultat = sommeRecursive(N);
disp(resultat);

