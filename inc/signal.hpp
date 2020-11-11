#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <cmath>
#include <cstdlib>

#include "struct.hpp"

std::vector<Point> mergeSort(std::vector<Point> f);

std::vector<Point> cut(std::vector<Point> g, float wdw[2]);

std::vector<Point> sample(std::vector<Point> f, int n_pts, char* method, float wdw[2]);

std::vector<Point> polynomial(std::vector<float> coefficients, int n_pts, float wdw[2]);

std::vector<float> linspace(float wdw[2], int n_pts);

#endif