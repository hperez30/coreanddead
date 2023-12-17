#include "bdd.h"

int get_dependencies_conflicts(const bdd r, int *vars_low, int *vars_high, int *marks, int *res_node);
int* dead_features(int *var_high, int *var_low, int num_var);

