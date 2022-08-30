#ifndef CALCULATE_H
#define CALCULATE_H

#pragma once
#include "matix.h"
#include <map>
Matix expression_value(string, int &);
Matix term_value(string, int &);
Matix factor_value(string, int &);
extern map<string, int> order;
extern int PM;
extern Matix LM[400];

#endif // CALCULATE_H
