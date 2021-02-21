#include <iostream>
#include <ctime>
#include "plot.hpp"
#include "leastSquares.hpp"
#include "signal.hpp"
#include "matrix.hpp"
#include "interpolation.hpp"

int main()
{
    srand(time(NULL));

    
    data f1;
    data f2;
    data f3;
    data f4;
    data f5;
    data f6;
    data f7;
    data f8;
    std::vector<Point> polyn;
    std::vector<Point> itrpp;
    std::vector<float> coeff;

    std::vector<Point> testInterp;
    testInterp.push_back({0, 0});
    testInterp.push_back({1, 6});
    testInterp.push_back({2, 3});
    testInterp.push_back({3, 5});
    testInterp.push_back({5, 0});

    std::vector<Point> sinVal;
    sinVal.push_back({0, sin(0)});
    sinVal.push_back({0.01, sin(0.01)});

    std::vector<Point> sinsng;
    sinsng.push_back({0, sin(0)});

    std::vector<Point> expVal;
    expVal.push_back({0, 10*exp(0)});
    expVal.push_back({0.01, 10*exp(0.01)});

    std::vector<Point> expsng;
    expsng.push_back({0, 10*exp(0)});
    

    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);


    Axis xsin;
    Axis ysin;
    xsin.color = 'b';
    ysin.color = 'b';
    xsin.range[0] = -0.5;
    xsin.range[1] = PI/2; 

    Axis xexp;
    Axis yexp;
    xexp.color = 'g';
    yexp.color = 'g';

    Axis xspl;
    Axis yspl;
    yspl.color = 'r';
    xspl.color = 'r'; 
    yspl.range[0] = -0.5;
    yspl.range[1] = 8;
    

    Axis xitp;
    Axis yitp;
    yitp.color = 'y';
    xitp.color = 'y'; 
    xitp.range[0] = -8;
    xitp.range[1] = 8;
    

    float wdw[2] = {0.01, 5};
    float wdww[2] = {-10, 10};

    polyn = gaussianNoise(polynomial(coeff, 20, wdww), 0, 1, false);
    
    f1.legend = "Original Signal";
    f2.legend = "Smooth spline";
    f3.legend = "Sin values";
    f4.legend = "Last value";
    f5.legend = "Exp values";
    f6.legend = "Last value";
    f7.legend = "deg 3 noisy func";
    f8.legend = "Least square";
    f1.style = 'O';
    f2.color = 'b';
    f4.style = '\0';
    f4.color = 'p';
    f6.style = '\0';
    f6.color = 'p'; 
    f8.color = 'c';


    for(int i = 0; i<100; i+=2)
    {
    //Matrix<float> lsCoeff = lstSqr(polyn, i/2);
    //std::vector<float> cofcof;
    /*for(int b = 0; b<(i/2)+1; b++) cofcof.push_back(b);//lsCoeff[w]);
    itrpp = polynomial(cofcof, 20, wdww);*/
    sinVal.push_back({i*(PI/200), sin(i*(PI/200))});
    sinsng[0] = {i*(PI/200), sin(i*(PI/200))};
    expVal.push_back({tan(-(PI/2)*sin(i*(PI/200))), 10*exp(tan(-(PI/2)*sin(i*(PI/200))))});
    expsng[0] = {tan(-(PI/2)*sin(i*(PI/200))), 10*exp(tan(-(PI/2)*sin(i*(PI/200))))};
    float lbd =  10*exp(tan(-(PI/2)*sin(i*(PI/200))));
    char t[5];
    sprintf(t, "%f", lbd);
    std::vector<Point> OSF = smoothSplineInterp(testInterp, linspace(wdw, 100), lbd);

    f2.values = OSF;
    f1.values = testInterp;
    f3.values = sinVal;
    f4.values = sinsng;
    f5.values = expVal;
    f6.values = expsng;
    f7.values = polyn;
    //f8.values = itrpp;

    std::vector<data> dclust;
    std::vector<data> dcSin;
    std::vector<data> dcExp;
    std::vector<data> dcLs;

    
    dclust.push_back(f1);
    dclust.push_back(f2);
    dcSin.push_back(f4);
    dcSin.push_back(f3);
    dcExp.push_back(f6);
    dcExp.push_back(f5);
    //dcLs.push_back(f8);
    dcLs.push_back(f7);
    char str[50];
    strcpy(str, "Smooth Spline Interpolation. Lambda: ");
    strcat(str, t);
    char t1[5];
    sprintf(t1, "%d", i/2);
    char str1[50];
    strcpy(str1, "Least squares fit. Degree: ");
    strcat(str1, t1);
    clearScreen();
    subplot(xexp, yexp, dcExp, "Exp function", true, 1, 2, 2);
    subplot(xsin, ysin, dcSin, "Sinus function", true, 0, 2, 2);
    subplot(xspl, yspl, dclust, str, true, 3, 2, 2);
    subplot(xitp, yitp, dcLs, str1, true, 2, 2, 2);
    int a;
    std::cin >> a;
    }
    return 0;
}