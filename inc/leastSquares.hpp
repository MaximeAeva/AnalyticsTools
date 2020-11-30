#ifndef LS_H
#define LS_H

#include <vector>
#include <cmath>
#include <iostream>

#include "struct.hpp"
#include "signal.hpp"
#include "matrix.hpp"

Matrix<float> lstSqr(std::vector<Point> f, int deg);

#endif