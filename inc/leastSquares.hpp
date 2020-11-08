#ifndef LS_H
#define LS_H

#include <vector>
#include <cmath>
#include <iostream>

#include "struct.hpp"

std::vector<Point> mergeSort(std::vector<Point> f);

std::vector<Point> sample(std::vector<Point> f, float freq, char* method, float wdw[2]);

#endif