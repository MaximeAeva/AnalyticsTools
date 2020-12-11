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

    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);
    coeff.push_back(rand()%100/50);

    x.range[0] = -5;
    x.range[1] = 5;
    y.color = 'b';
    x.color = 'g';
    y.range[0] = -21;
    y.range[1] = 20;

    float wdw[2] = {-5, 5};
    float wdww[2] = {-5, 5};
    int deg = 10;
    polyn = gaussianNoise(polynomial(coeff, 100, wdw), 0, 0.5, false);
    f2.values = periodic(freq, 500, wdw);
    f3.values = PSD(f2.values);
    f3.style = '\0';
    f1.values = polyn;
    f2.legend = "Lagrange interpolation";
    f1.legend = "Original Signal";
    f3.legend = "A Simple Fourier Transform";
    f3.color = 'g';
    std::vector<data> dclust;
    dclust.push_back(f1);
    //dclust.push_back(f3);
    //dclust.push_back(f2);
    plot(x, y, dclust, "Fourier transform of a 2 harmonic signal", true);
    return 0;
}