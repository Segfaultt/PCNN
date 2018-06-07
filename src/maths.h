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
		matrix(int starting_rows, int starting_cols, std::vector<T> args);
		matrix(int starting_rows, int starting_cols);
		template<class R>
			matrix<R> apply(std::function<R(T)> function);//for non-mutating fns
			void for_each(std::function<void(T&)> function);//for mutating fns
		int get_rows();
		int get_cols();
		T* begin();
		T* end();
		matrix<T> r(int row_number);
		matrix<T> c(int col_number);
		matrix<T> submatrix(int starting_r, int starting_c, int sm_rows, int sm_cols);

		T& operator () (unsigned int x, unsigned int y);
		T& operator () (unsigned int i);
		matrix<T> operator + (matrix B);
		matrix<T> operator * (matrix B);

		template<class U>
			friend std::ostream& operator<< (std::ostream& os, matrix<U>& M);
		template<class U, class V>
			friend U dot (matrix<U> A, matrix<V> B);

	private:
		int rows, cols; 
		T *data;
};

#include "maths.cpp"
