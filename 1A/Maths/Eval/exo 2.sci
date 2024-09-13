for n=1:10
U=0
for i=1:1:n
    U=U+1./(n+i-1)
end
plot(n,U,'Or')  
end
