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

    Axis x;
    Axis y; 
    data f1;
    data f2;
    data f3;
    std::vector<Point> polyn;
    std::vector<Point> itrp;
    std::vector<Point> itrpp;
    f1.color = 'r';
    std::vector<float> coeff;
    std::vector<float> coefff;
    std::vector<float> coefT;

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
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);

    x.range[0] = -5;
    x.range[1] = 5;
    y.color = 'b';
    x.color = 'b';
    y.range[0] = -41;
    y.range[1] = 40;

    float wdw[2] = {-4, 4};
    float wdww[2] = {-5, 5};
    int deg = 10;
    polyn = gaussianNoise(polynomial(coeff, 100, wdww), 0, 3, false);
    itrp = lagrangeInterp(chebychevNodes(polyn, 99), linspace(wdw, 1000));
    itrpp = lagrangeInterp(polyn, linspace(wdw, 2000));
    Matrix<float> M = lstSqr(polyn, 3);
    for(int i = 0; i<4; i++) coefff.push_back(M[i]),
    f2.values = itrpp;
    f1.values = polyn;
    f3.values = itrp;
    f3.legend = "Lagrange Interpolation with ChebychevNodes";
    f1.legend = "Original Signal";
    f2.legend = "Lagrangian interpolation";
    f1.color = 'w';
    f2.color = 'p';
    f3.color = 'g';
    std::vector<data> dclust;
    
    dclust.push_back(f3);
    
    dclust.push_back(f1);
    dclust.push_back(f2);
    plot(x, y, dclust, "Runge Kutta phenomenon", true);
    return 0;
}