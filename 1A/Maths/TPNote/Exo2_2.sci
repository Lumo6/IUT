A = [1950 1960 1965 1973 1985 1990 2000 2005 2006 2008 2010 2012]
W = [63 90 115 180 202 229 269 277 276 273 263 259]
G = [30 50 66 100 132 154 188 203 208 213 210 214]
P = [41.6 45.5 48.7 51.9 55.2 56.6 58.9 61 61.4 62.1 62.8 63.4]

scf(1);
plot2d(W,G,style=-1)
plot2d(W,G,style=5)
cor = corr(W,G,1)/stdev(W)/stdev(G)
title('Evolution du PIB en fonction de la consommation energetique')

scf(2);
plot2d(A,G./W,style=-3)
plot2d(A,G./W,style=5)
title('Evolution de l`efficacite energetique par annee')

scf(3);
plot2d(A,G,style=-3)
plot2d(A,G,style=5)
title('Evolution du PIB par annee')
