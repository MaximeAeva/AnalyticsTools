#include <iostream>
#include <ctime>
#include "plot.hpp"
#include "leastSquares.hpp"
#include "signal.hpp"
#include "matrix.hpp"

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
    coeff.push_back(0.5);

    x.range[0] = -8;
    x.range[1] = 8;
    x.step = 0.1;
    y.color = x.color = 'b';
    y.step = 0.25;
    y.range[0] = -5;
    y.range[1] = 5;

    float wdw[2] = {-8, 8};
    int deg = 10;
    polyn = gaussianNoise(polynomial(coeff, 200, wdw), 0, 1, false);
    Matrix coef(lstSqr(polyn, deg));
    Matrix coeffT(lstSqr(chebychevNodes(polyn, deg), deg));
    for(int i = 0; i<deg+1; i++) coefff.push_back(coef[i]);
    for(int i = 0; i<deg+1; i++) coefT.push_back(coeffT[i]);

    f1.values = polyn;
    f3.values = polynomial(coefff, 200, wdw);
    
    f2.values = centralMovingAverage(polyn, 10);
    f2.legend = "derivative";
    f1.legend = "Original Signal";
    f3.legend = "fit";
    f3.color = 'g';
    std::vector<data> dclust;
    dclust.push_back(f2);
    dclust.push_back(f1);
    //dclust.push_back(f3);
    plot(x, y, dclust, "fit and tangent", true);

    return 0;
}