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
    std::vector<Point> polyn;
    std::vector<Point> itrp;
    std::vector<Point> itrpp;
    std::vector<Point> itrppp;
    f1.color = 'r';
    std::vector<float> coeff;
    std::vector<float> coefff;
    std::vector<float> coefT;

    std::vector<Point> testInterp;
    testInterp.push_back({0, 0});
    testInterp.push_back({1, 6});
    testInterp.push_back({2, 3});
    testInterp.push_back({3, 5});
    testInterp.push_back({5, 0});

    std::vector<Point> testInterpp;
    testInterpp.push_back({0, 0});
    testInterpp.push_back({0.5, 0.4794});
    testInterpp.push_back({1, 0.8415});
    testInterpp.push_back({1.5, 0.9975});
    testInterpp.push_back({2, 0.9093});
    

    std::vector<fdata> freq;
    fdata ff = {0.5, 8, 0};
    fdata fff = {0.2, 1, 0};
    fdata ffff = {0.1, 0.5, 0};
    fdata fffff = {0.005, 0.7, 0};
    //freq.push_back(ff);
    freq.push_back(fff);
    freq.push_back(ffff);
    //freq.push_back(fffff);

    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    //coeff.push_back(rand()%100/50);
    //coeff.push_back(rand()%100/50);
    //coeff.push_back(rand()%100/50);

    Axis x;
    Axis y;
    y.color = 'g';
    x.color = 'g'; 

    float wdw[2] = {0.01, 5};
    float wdww[2] = {-5, 5};
    int deg = 10;

    polyn = gaussianNoise(polynomial(coeff, 5, wdww), 0, 1, false);
    itrp = lagrangeInterp(chebychevNodes(polyn, 99), linspace(wdw, 1000));
    itrpp = lagrangeInterp(polyn, linspace(wdw, 2000));
    //itrppp = splineInterp(polyn, linspace(wdw, 200), true);
    for(int i = 0; i<100; i+=2)
    {
    
    char t[5];
    float p = float(i)/100;
    float lbd = (1-p)/(p+1e-10);
    sprintf(t, "%f", lbd);
    std::vector<Point> OSF = smoothSplineInterp(testInterp, linspace(wdw, 200), lbd);

    //Matrix<float> M = lstSqr(polyn, 3);
    //for(int i = 0; i<4; i++) coefff.push_back(M[i]),
    f2.values = OSF;
    f1.values = testInterp;
    //f3.values = itrp;
    //f3.legend = "Lagrange Interpolation with ChebychevNodes";
    f1.legend = "Original Signal";
    f2.legend = "Smooth spline";
    f1.color = 'r';
    f1.style = 'O';
    f2.color = 'b';
    //f3.color = 'g';
    std::vector<data> dclust;
    
    //dclust.push_back(f3);
    
    dclust.push_back(f1);
    dclust.push_back(f2);
    char str[50];
    strcpy(str, "Smooth Spline Interpolation. Lambda: ");
    strcat(str, t);
    plot(x, y, dclust, str, true, floor(165/2), 10);
    int a;
    std::cin >> a;
    }
    return 0;
}