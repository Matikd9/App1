#ifndef METRICS_H
#define METRICS_H
#include "orders.h"
#include <stdio.h>

char *apd(int size, order *orders);
char *apo(int size, order *orders);
char *dmsp(int size, order *orders);
char *dlsp(int size, order *orders);

#endif