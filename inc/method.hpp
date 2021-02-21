#ifndef METHOD_H
#define METHOD_H

#include <vector>
#include <cmath>
#include <iostream>

#include "struct.hpp"

float boxMuller(float mu, float sigma);

std::vector<Point> polynomial(std::vector<float> coefficients, int n_pts, float wdw[2], float xShift=0);

std::vector<float> linspace(float wdw[2], int n_pts);

std::vector<Point> mergeSort(std::vector<Point> f);

void clearScreen();

#endif