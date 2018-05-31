#include "convolution.h"

convolution::convolution(int n_kernels, int w_kernel, int h_kernel, double max_value, double min_value) : depth(n_kernels)
{
	int seed = time(NULL) + 0xFA11;
	kernel.reserve(n_kernels);
	std::generate_n(kernel.begin(), n_kernels, [&seed, w_kernel, h_kernel, min_value, max_value] () 
			{
			srand(seed++);
			std::vector<double> init_data(w_kernel*h_kernel);
			std::generate_n(init_data.begin(), w_kernel*h_kernel, [&seed, min_value, max_value] () {
					srand(seed++);
					return (double)rand()/RAND_MAX * abs(min_value - max_value) + std::min(min_value, max_value);
					});
			matrix<double> M(h_kernel, w_kernel, init_data);
			return M;
			});

	bias.reserve(n_kernels);
	std::generate_n(bias.begin(), n_kernels, [&seed, min_value, max_value] () {
			srand(seed++);
			return (double)rand()/RAND_MAX * abs(min_value - max_value) + std::min(min_value, max_value);
			});
}

std::ostream& operator<< (std::ostream& os, convolution& conv)
{
	for (int i = 0; i < conv.depth; i++) {
		os << std::endl << i << ":\n";
		os << conv.kernel[i];
		os << conv.bias[i] << std::endl;
	}
}
