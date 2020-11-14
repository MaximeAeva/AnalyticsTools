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
    std::vector<Point> fit;
    std::vector<Point> sorted;
    f1.color = 'r';
    std::vector<fdata> coeff;

    fdata freq;
    freq.amp = 2; freq.f = 0.01; freq.phi = -2;
    fdata freqq;
    freqq.amp = 1.5; freqq.f = 0.015; freqq.phi = 4;
    coeff.push_back(freqq);
    coeff.push_back(freq);

    x.range[0] = -8;
    x.range[1] = 8;
    x.step = 0.1;
    y.color = x.color = 'b';
    y.step = 0.25;
    y.range[0] = -5;
    y.range[1] = 5;

    float wdw[2] = {-8, 0};
    float wdww[2] = {-5, 5};
    int deg = 200;
    polyn = periodic(coeff, 500, wdw);
    Matrix k(AR(deg, polyn));
    Matrix coef(lstSqr(polyn, deg));
    std::vector<float> coefff;
    std::vector<float> coeffar;
    for(int i = 0; i<deg; i++) coeffar.push_back(k[i]);
    for(int i = 0; i<deg+1; i++) coefff.push_back(coef[i]);
    f3.values = buildAR(polyn, coeffar, 500);
    fit = polynomial(coefff, 200, wdw);
    float wd[2] = {-1, 1};
    sorted = sample(polyn, 100, "linear", wd);
    for(int i = 0; i<polyn.size(); i++)
        f1.values.push_back(polyn[i]);
    for(int i = 0; i<fit.size(); i++)
        f2.values.push_back(fit[i]);

    f1.legend = "Original Signal";
    //f2.legend = "Degree 3 fit";
    f3.legend = "AR prediction";
    f3.color = 'g';
    std::vector<data> dclust;
    dclust.push_back(f1);
    dclust.push_back(f3);
    plot(x, y, dclust, "AR prediction of a WSS signal", true);

    
    //k.display();
    //std::cout << f3.values.size();
    return 0;
}