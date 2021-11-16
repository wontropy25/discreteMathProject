#pragma once
#include <iostream>
#include <string>
#include <map>
#include <istream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <cstdio>
#include <algorithm>

#include "Node.h"

void readFile_1(std::istream& in);
void readFile_2(std::istream& in);

size_t index(int row, int col, unsigned int numOfNodes);
