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

    coeff.push_back(0.1);
    coeff.push_back(0.3);
    coeff.push_back(0.2);
    coeff.push_back(0.05);
    coeff.push_back(0.15);
    coeff.push_back(0.1);

    x.range[0] = -8;
    x.range[1] = 8;
    x.step = 0.1;
    y.color = x.color = 'b';
    y.step = 0.25;
    y.range[0] = -5;
    y.range[1] = 5;

    float wdw[2] = {-3, 3};
    int deg = 3;
    polyn = polynomial(coeff, 1000, wdw);
    Matrix coef(lstSqr(polyn, deg));
    for(int i = 0; i<deg+1; i++) coefff.push_back(coef[i]);

    f1.values = polyn;
    f3.values = polynomial(coefff, 1000, wdw);
    
    f2.values = polynomial(tangent(f3.values, 0.3), 200, wdw, 0.3);
    f2.legend = "derivative";
    f1.legend = "Original Signal";
    f3.legend = "fit";
    f3.color = 'g';
    std::vector<data> dclust;
    dclust.push_back(f3);
    dclust.push_back(f1);
    dclust.push_back(f2);
    plot(x, y, dclust, "fit and tangent", true);


    return 0;
}