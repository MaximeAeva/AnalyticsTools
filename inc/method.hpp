#ifndef METHOD_H
#define METHOD_H

#include <vector>
#include <cmath>
#include <complex>
#include <iostream>

#include "struct.hpp"
#include "matrix.hpp"

float boxMuller(float mu, float sigma);

std::vector<Point> polynomial(std::vector<float> coefficients, int n_pts, float wdw[2], float xShift=0);

std::vector<float> linspace(float wdw[2], int n_pts);

std::vector<Point> mergeSort(std::vector<Point> f);

void clearScreen();

float wHann(Point p, float t);

float wHamming(Point p, float t);

float wBlackman(Point p, float t);

Matrix<float> kmeans(std::vector<Point> p, std::vector<Point> *clas, int iterations);

#endif