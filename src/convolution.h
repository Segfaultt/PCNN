#include <vector>
#include <algorithm>
#include "maths.h"

class convolution {
	public:
		convolution(int n_kernels, int w_kernel, int h_kernel, double max_value, double min_value);
		friend std::ostream& operator<< (std::ostream& os, convolution& M);

	private:
		int depth;
		std::vector< matrix<double> > kernel;
		std::vector<double> bias;
};
