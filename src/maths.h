#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>
#include <cstring>

template<class T>
class matrix {
	public:
		matrix(int starting_rows, int starting_cols, std::vector<T> args);
		matrix(int starting_rows, int starting_cols);
		template<class R>
			matrix<R> apply(R (* function)(T));
		int get_rows();
		int get_cols();
		T* begin();
		T* end();
		matrix<T> r(int row_number);
		matrix<T> c(int col_number);

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
