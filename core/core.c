#include <core.h>

int* dead_features(int *var_high, int *var_low, int num_var)
{
	int *num_dead_core = (int *)malloc(2*sizeof(int));
	for (int i = 0; i < 2; ++i)
		num_dead_core[i] = 0;

	for (int i = 0; i < num_var; ++i)
	{
		if (var_high[i] != var_low[i])
		{
			if (var_high[i] && !var_low[i])
			{
#ifdef DEBUG
				/* compile with debug flag */				
				std::cout << "var " << i "is core" << endl;
#endif
				num_dead_core[1]++;
			}
			else
			{
				if (!var_high[i] && var_low[i])
				{
#ifdef DEBUG
					/* compile with debug flag */
					std::cout << "var " << i "is dead" << endl;
#endif
					num_dead_core[0]++;
				}
			}
		}			
	}

	return num_dead_core;
} // end dead_features

int get_dependencies_conflicts(const bdd r, int *vars_low, int *vars_high, int *marks, int *res_node)
{	
	int root = r.id();
	if (!marks[root])
	{
		marks[root] = !marks[root];
		int level = bdd_var2level(bdd_var(r));
		if (bdd_high(r).id() == 1)
		{
			vars_high[level] = 1;
			for (int i = level + 1; i < bdd_varnum(); ++i)
			{
				vars_high[i] = 1;
				vars_low[i] = 1;
			}
			res_node[root] = 1;
		}
		else
		{
			if (bdd_high(r).id() != 0)
			{
				res_node[root] = get_dependencies_conflicts(bdd_high(r), vars_low, vars_high, marks, res_node);

				if (res_node[root])
				{
					vars_high[level] = 1;
					int level_high = bdd_var2level(bdd_var(bdd_high(r)));
					for (int i = level + 1; i < level_high; ++i)
					{
						vars_high[i] = 1;
						vars_low[i] = 1;
					}
				}
			}
		}

		if (bdd_low(r).id() == 1)
		{
			vars_low[level] = 1;
			for (int i = level + 1; i < bdd_varnum(); ++i)
			{
				vars_high[i] = 1;
				vars_low[i] = 1;
			}
			res_node[root] = 1;
		}
		else
		{
			if (bdd_low(r).id() != 0)
			{
				res_node[root] = get_dependencies_conflicts(bdd_low(r), vars_low, vars_high, marks, res_node);

				if (res_node[root])
				{
					vars_low[level] = 1;
					int level_low = bdd_var2level(bdd_var(bdd_low(r)));

					for (int i = level + 1; i < level_low; ++i)
					{
						vars_high[i] = 1;
						vars_low[i] = 1;
					}
				}
			}
		}
	}

	return res_node[root];
} // end get_dependencies_conflicts
