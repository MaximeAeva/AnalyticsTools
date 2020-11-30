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

    coeff.push_back(0);

    x.range[0] = -50;
    x.range[1] = 50;
    x.step = 0.8;
    y.color = x.color = 'b';
    y.step = 0.05;
    y.range[0] = -1;
    y.range[1] = 1;

    float wdw[2] = {-4, 4};
    float wdww[2] = {-5, 5};
    int deg = 10;
    polyn = gaussianNoise(polynomial(coeff, 1000, wdw), 0, 3, false);
    f2.values = periodic(freq, 500, wdw);
    f3.values = PSD(f2.values);

    f1.values = polyn;
    f2.legend = "Lagrange interpolation";
    f1.legend = "Original Signal";
    f3.legend = "Chebychev Nodes";
    f3.color = 'g';
    std::vector<data> dclust;
    //dclust.push_back(f1);
    dclust.push_back(f3);
    dclust.push_back(f2);
    plot(x, y, dclust, "Runge Kutta phenomenon", true);
    return 0;
}