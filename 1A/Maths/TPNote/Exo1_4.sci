X = grand(1, 10000, 'nor', 25, 3);
val_median = median(X);
val_mean = mean(X);
nb_classes = 40;
figure();
histplot(nb_classes, X);


X2 = grand(1, 10000, 'nor', 13, sqrt(5));
val_median2 = median(X2);
val_mean2 = mean(X2);
nb_classes2 = 15;
figure(); 
histplot(nb_classes2,X2)
