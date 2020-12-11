#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <cmath>
#include <cstdlib>
#include <complex>

#include "struct.hpp"
#include "matrix.hpp"
#include "method.hpp"

std::vector<Point> mergeSort(std::vector<Point> f);

std::vector<Point> cut(std::vector<Point> g, float wdw[2]);

std::vector<Point> sample(std::vector<Point> f, int n_pts, char* method, float wdw[2]);

std::vector<Point> polynomial(std::vector<float> coefficients, int n_pts, float wdw[2], float xShift=0);

std::vector<float> linspace(float wdw[2], int n_pts);

std::vector<Point> periodic(std::vector<fdata> harmonic, int n_pts, float wdw[2]);

float mean(std::vector<Point> f);

float var(std::vector<Point> f);

float aCFn(int tau, std::vector<Point> f);

Matrix<float> AR(int deg, std::vector<Point> f);

std::vector<Point> buildAR(std::vector<Point> f, 
                            std::vector<float> coefficients, int n_pts);

std::vector<Point> differentiation(std::vector<Point> f);

std::vector<float> tangent(std::vector<Point> f, float abscissa);

std::vector<Point> centralMovingAverage(std::vector<Point> f, int deg);

std::vector<Point> gaussianNoise(std::vector<Point> f, float mu, float sigma, bool yNoise = false);

Matrix<std::complex<float> > DFT(std::vector<Point> f);

std::vector<Point> PSD(std::vector<Point> f);

#endif