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
    

    coeff.push_back(20+rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);


    Axis xsin;
    Axis ysin;
    xsin.color = 'b';
    ysin.color = 'b';
    xsin.range[0] = -0.5;
    xsin.range[1] = 2.5*PI; 

    Axis xexp;
    Axis yexp;
    xexp.color = 'g';
    yexp.color = 'g';
    xexp.range[0] = -1.5;
    xexp.range[1] = 1.5;
    yexp.range[0] = -1.5;
    yexp.range[1] = 1.5;

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
    yitp.range[0] = 5;
    yitp.range[1] = 50;
    

    float wdw[2] = {0.01, 5};
    float wdww[2] = {-10, 10};

    polyn = gaussianNoise(polynomial(coeff, 150, wdww), 0, 2, false);
    
    f1.legend = "Original Signal";
    f2.legend = "Smooth spline";
    f3.legend = "Sin values";
    f4.legend = "Last value";
    f5.legend = "Sin phase values";
    f6.legend = "Last value";
    f7.legend = "deg 3 noisy func";
    f8.legend = "Lagrangian Chebychev";
    f1.style = 'O';
    f2.color = 'b';
    f4.style = '\0';
    f4.color = 'p';
    f6.style = '\0';
    f6.color = 'p'; 
    f8.color = 'r';

    std::vector<data> dclust;
    std::vector<data> dcSin;
    std::vector<data> dcExp;
    std::vector<data> dcLs;

    std::vector<float> cofcof;

    
    for(int i = 0; i<100; i+=2)
    {
    sinVal.clear();
    
    for(int k = 0; k<100; k++)
        sinVal.push_back({k*(PI/50), (sin(k*(PI/50)+(i*PI/50)-PI/2)/2)+0.5});
    sinsng[0] = {100*(PI/50), (sin(100*(PI/50)+(i*PI/50)-PI/2)/2)+0.5};
    expVal.push_back({cos((i*PI/50)-PI/2), sin((i*PI/50)-PI/2)});
    expsng[0] = {cos((i*PI/50)-PI/2), sin((i*PI/50)-PI/2)};
    float lbd =  10*exp(tan(-(PI/2)*sinsng[0].y));
    char t[5];
    sprintf(t, "%f", lbd);
    std::vector<Point> OSF = smoothSplineInterp(testInterp, linspace(wdw, 100), lbd);
    itrpp = lagrangeInterp(chebychevNodes(polyn, 2+ceil(98*sinsng[0].y)), linspace(xitp.range, 75));

    f2.values = OSF;
    f1.values = testInterp;
    f3.values = sinVal;
    f4.values = sinsng;
    f5.values = expVal;
    f6.values = expsng;
    f7.values = polyn;
    f8.values = itrpp;

    dclust.clear();
    dcSin.clear();
    dcExp.clear();
    dcLs.clear();
    
    dclust.push_back(f1);
    dclust.push_back(f2);
    dcSin.push_back(f4);
    dcSin.push_back(f3);
    dcExp.push_back(f6);
    dcExp.push_back(f5);
    dcLs.push_back(f8);
    dcLs.push_back(f7);
    char str[50];
    strcpy(str, "Smooth Spline Interpolation. Lambda: ");
    strcat(str, t);
    char t1[5];
    int c = 2+ceil(98*sinsng[0].y);
    sprintf(t1, "%d", c);
    char str1[50];
    strcpy(str1, "Lagrangian-Chebychev interpolation. Abscissa used: ");
    strcat(str1, t1);
    clearScreen();
    subplot(xexp, yexp, dcExp, "Phase", true, 1, 2, 2);
    subplot(xsin, ysin, dcSin, "Sinus function", true, 0, 2, 2);
    subplot(xspl, yspl, dclust, str, true, 3, 2, 2);
    subplot(xitp, yitp, dcLs, str1, true, 2, 2, 2);
    int a;
    std::cin >> a;
    }
    return 0;
}