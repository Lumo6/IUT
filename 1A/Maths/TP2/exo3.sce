

clf();
x=-0.5:0.1:10
y=log(x+1);
x1=1.5:0.1:10
y1=log(x1-1);
plot(x,y,x1,y1);
legend("ln(x + 1)","ln(x - 1)");
xlabel('n');
title('exo3');

plot(5,log(6),"Xb");
plot(5,log(4),"Xg");
plot([5 5],[log(6) log(4)],"r");
xstring(5,1.8,["A5"]);
xstring(5,1.2,["B5"]);

plot(7,log(8),"Xb");
plot(7,log(6),"Xg");
plot([7 7],[log(8) log(6)],"r");
xstring(6.5,2.05,["An"]);
xstring(7,1.6,["Bn"]);

