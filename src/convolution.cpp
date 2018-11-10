#pragma once
#include "convolution.h"


template<class T>
int convolution<T>::seed = time(NULL) + 0xBAB;

	template<class T>
convolution<T>::convolution(int layers, int n_kernels, int l_kernel, T max_value, T min_value, int kern_stride) : depth(n_kernels), stride(kern_stride), kernel_length(l_kernel), in_depth(layers)
{
	//randomly generate kernels
	kernel.reserve(n_kernels);
	std::generate_n(kernel.begin(), n_kernels, [layers, l_kernel, min_value, max_value] () 
			{
			std::vector< matrix<T> > r_value;
			r_value.reserve(layers);
			std::generate_n(r_value.begin(), layers, [l_kernel, min_value, max_value] {
					srand(seed++);
					std::vector<T> init_data(l_kernel*l_kernel);
					std::generate_n(init_data.begin(), l_kernel*l_kernel, [min_value, max_value] () {
							srand(seed++);
							return (double)rand()/RAND_MAX * std::abs(min_value - max_value) + std::min(min_value, max_value);
							});
					matrix<T> M(l_kernel, l_kernel, init_data);
					return M;
					});
			return r_value;
			});


	bias.reserve(n_kernels);
	std::generate_n(bias.begin(), n_kernels, [min_value, max_value] () {
			srand(seed++);
			return (double)rand()/RAND_MAX * std::abs(min_value - max_value) + std::min(min_value, max_value);
			});
}

	template<class U>
std::ostream& operator<< (std::ostream& os, convolution<U>& conv)
{
	os << "input depth: " << conv.in_depth << std::endl;
	os << "output depth: " << conv.depth << std::endl;
	os << "kernel dimensions: " << conv.kernel_length << "x" << conv.kernel_length << std::endl;
	os << "stride: " << conv.stride << std::endl;
	for (int i = 0; i < conv.depth; i++) {
		os << std::endl << i << ":\n";
		for (int j = 0; j < conv.in_depth; j++)
			os << conv.kernel[i][j];
		os << conv.bias[i] << std::endl;
	}
}

	template<class T>
std::vector< matrix<T> > convolution<T>::flow(std::vector< matrix<T> >& img)
{
	const int img_r = (img[0].get_rows() - kernel_length)/stride + 1,
	      img_c = (img[0].get_cols() - kernel_length)/stride + 1;
	std::vector< matrix<T> > convolved;
	{
		matrix<T> M(img_r, img_c);
		for (int i = 0; i < depth; i++)
			convolved.push_back(M);
	}

	for (int r = 0; r < img_r; r++) {
		for (int c = 0; c < img_c; c++) {
			for (int d = 0; d < depth; d++) {
				T sum = bias[d];
				for (int layer = 0; layer < in_depth; layer++) {
					sum += dot(kernel[d][layer], img[layer].submatrix(r*stride, c*stride, kernel_length, kernel_length));

				}
				convolved[d](r, c) = sum;
			}
		}
	}

	return convolved;
}
