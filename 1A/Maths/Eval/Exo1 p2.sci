for n=1:10
U=2
for i=1:1:n
    U=(1+0.5.*U)./(0.5+U)
end
plot(n,U,'Or')  
end
