for n=1:10
U=2
for i=1:1:n
    U=(1+3.*U)./(3+U)
end
plot(n,U,'Or')  
end
