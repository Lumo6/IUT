function SN = sommeNaive(N)
    SN = 1;
    for i = 1:N
        SN = SN + i;
    end
endfunction
N = 3; 
resultat = sommeNaive(N);
disp(resultat);

