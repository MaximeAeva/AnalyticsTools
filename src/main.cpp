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
    std::vector<Point> polyn;
    std::vector<Point> fit;
    std::vector<Point> sorted;
    f1.color = 'r';
    std::vector<float> coeff;

    coeff.push_back(0);
    coeff.push_back(-0.5);
    coeff.push_back(0.4);
    coeff.push_back(0.05);
    coeff.push_back(0.1);
    coeff.push_back(0.05);

    x.range[0] = -8;
    x.range[1] = 8;
    x.step = 0.1;
    y.color = x.color = 'b';
    y.step = 0.5;
    y.range[0] = -5;
    y.range[1] = 15;

    float wdw[2] = {-4, 4};
    int deg = 3;
    polyn = polynomial(coeff, 100, wdw);
    Matrix coef(lstSqr(polyn, deg));
    std::vector<float> coefff;
    for(int i = 0; i<deg+1; i++) coefff.push_back(coef[i][0]);
    fit = polynomial(coefff, 200, wdw);
    float wd[2] = {-1, 1};
    sorted = sample(polyn, 100, "linear", wd);
    for(int i = 0; i<polyn.size(); i++)
        f1.values.push_back(polyn[i]);
    for(int i = 0; i<fit.size(); i++)
        f2.values.push_back(fit[i]);

    f1.legend = "Degree 5 polynomial";
    f2.legend = "Degree 3 fit";
    std::vector<data> dclust;
    dclust.push_back(f2);
    dclust.push_back(f1);
    plot(x, y, dclust, "Degree 3 fit of a degree 5 polynomial", true);
    return 0;
}