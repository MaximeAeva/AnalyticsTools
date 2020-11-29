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

    coeff.push_back(0);

    x.range[0] = -8;
    x.range[1] = 8;
    x.step = 0.1;
    y.color = x.color = 'b';
    y.step = 0.25;
    y.range[0] = -5;
    y.range[1] = 5;

    float wdw[2] = {-8, 8};
    float wdww[2] = {-5, 5};
    int deg = 10;
    polyn = gaussianNoise(polynomial(coeff, 40, wdw), 0, 1, false);
    f2.values = lagrangeInterp(polyn, linspace(wdw, 10000));
    f3.values = lagrangeInterp(chebychevNodes(polyn, 40), linspace(wdw, 1000));

    f1.values = polyn;
    f2.legend = "Lagrange interpolation";
    f1.legend = "Original Signal";
    f3.legend = "Chebychev Nodes";
    f3.color = 'g';
    std::vector<data> dclust;
    dclust.push_back(f1);
    dclust.push_back(f3);
    dclust.push_back(f2);
    plot(x, y, dclust, "Runge Kutta phenomenon", true);

    return 0;
}