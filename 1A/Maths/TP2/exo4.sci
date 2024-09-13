for n=1:130
U=0
for i=1:1:n
    U=U+1./(n+i)
end
plot(n,U,'Or')  
end

