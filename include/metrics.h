#ifndef METRICS_H
#define METRICS_H
#include "orders.h"
#include <stdio.h>
char *pms(int size, order *orders);
char *pls(int size, order *orders);
char *apd(int size, order *orders);
char *apo(int size, order *orders);
char *dmsp(int size, order *orders);
char *dlsp(int size, order *orders);
char *dms(int size, order *orders);
char *dls(int size, order *orders);
#endif