#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <cstdlib>

#include "bdd.h"
#include "kernel.h"
#include <core.h>

const int INITBDDNODES       = 50000;
const int INITBDDCACHE       = 10000000;
const int INITBDDMAXINCREASE = 30000;

double timeval_diff(struct timeval *a, struct timeval *b);
void show_results(int num_dead, int num_core);
void show_elapsed_time(struct timeval *a, struct timeval *b);
