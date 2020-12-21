#ifndef INTERPOLATION_H
#define INTERPOLATION_H

#include <vector>
#include <cmath>
#include <iostream>

#include "struct.hpp"
#include "signal.hpp"
#include "matrix.hpp"

std::vector<Point> linearInterp(std::vector<Point> f, std::vector<float> abscissa);

std::vector<Point> lagrangeInterp(std::vector<Point> f, std::vector<float> abscissa);

std::vector<Point> chebychevNodes(std::vector<Point> f, int deg);

std::vector<Point> splineInterp(std::vector<Point> f, std::vector<float> abscissa, bool natural = true);

std::vector<Point> smoothSplineInterp(std::vector<Point> f, std::vector<float> abscissa, float lambda);

#endif