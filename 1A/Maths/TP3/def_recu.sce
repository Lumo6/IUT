// Exemple du cours : cas classique 1 : diapo 15 chapitre 2


clf();



x=0:0.05:1;
m=0.4;
y=4*m*x.*(1-x);
x1=0:0.05:0.6
y1=x1;
plot(x,y,x1,y1);
xstring(0.61,0.6,["y = x"]);
u0=0.9;
xstring(u0-0.02,-0.01,["u0"]);

u1=4*m*u0*(1-u0);
plot([u0,u0],[0,u1],"r");
plot([u1,u0],[u1,u1],"r");
plot([u1,u1],[0,u1],":r");
xstring(u1-0.02,-0.01,["u1"]);


u2=4*m*u1*(1-u1);
plot([u1,u1],[u1,u2],"r");
plot([u1,u2],[u2,u2],"r");
plot([u2,u2],[0,u2],":r");
xstring(u2-0.02,-0.01,["u2"]);

u3=4*m*u2*(1-u2);
plot([u2,u2],[u2,u3],"r");
plot([u2,u3],[u3,u3],"r");
plot([u3,u3],[0,u3],":r");
xstring(u3-0.02,-0.01,["u3"]);

u4=4*m*u3*(1-u3);
plot([u3,u3],[u3,u4],"r");
plot([u3,u4],[u4,u4],"r");
plot([u4,u4],[0,u4],":r");
xstring(u4-0.02,-0.01,["u4"]);

u5=4*m*u4*(1-u4);
plot([u4,u4],[u4,u5],"r");
plot([u4,u5],[u5,u5],"r");
plot([u5,u5],[0,u5],":r");
xstring(u5-0.02,-0.01,["u5"]);

u6=4*m*u5*(1-u5);
plot([u5,u5],[u5,u6],"r");
plot([u5,u6],[u6,u6],"r");
plot([u6,u6],[0,u6],":r");
xstring(u6-0.02,-0.01,["u6"]);


xlabel('x');
ylabel('y=f(x)');
title('f(x) = 1,6*x*(1-x)');
