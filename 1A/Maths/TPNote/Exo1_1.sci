n=input('entrez la valeur de n :'), X=floor(grand(1,n,'nor',5,1))
bar(X)

c=linspace(1,10,10)
[ind,occ]=dsearch(X,c)
histplot(c,X,normalization=%f, style=5)

quartile=quart(X)
etendue=max(X)-min(X)
disp(etendue)
disp(quartile)
