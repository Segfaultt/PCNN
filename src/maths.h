#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <functional>
#include <cstring>
#include <cmath>

template<class T>
class matrix {
	public:
		//constructors
		matrix(int starting_rows, int starting_cols, std::vector<T> args);
		matrix(int starting_rows, int starting_cols);

		template<class R>
			matrix<R> apply(std::function<R(T)> function);//for non-mutating fns. Must specify return type with <type>
			void for_each(std::function<void(T&)> function);//for mutating fns

		//getters
		int get_rows();
		int get_cols();

		//memory related functions
		T* begin();
		T* end();

		//submatrices
		matrix<T> r(int row_number);
		matrix<T> c(int col_number);
		matrix<T> submatrix(int starting_r, int starting_c, int sm_rows, int sm_cols);

		//matrix properties
		T& operator () (unsigned int x, unsigned int y);
		T& operator () (unsigned int i);
		matrix<T> operator + (matrix B);
		matrix<T> operator - (matrix B);
		matrix<T> operator * (matrix B);

		//vector properties
		template<class U, class V>
			friend U dot (matrix<U> A, matrix<V> B);
		T norm_squared();

		//other operators
		template<class U>
			friend std::ostream& operator<< (std::ostream& os, matrix<U>& M);
		matrix<T> operator * (T B);

	private:
		int rows, cols; 
		T *data;
};

#include "maths.cpp"
