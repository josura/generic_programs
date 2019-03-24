//programmer: Dio aka ahahahahahahahh aka ciao aka comemihachiamatolavita aka Locicero Giorgio
//program:  matrix classes
//reference : quantstart.com, myself, my life force
#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include<iomanip>

using namespace std;
template <typename T> class Matrix;
template <typename T> ostream& operator<<(ostream& os,const Matrix<T>& rhs);

template <typename T> class Matrix {
	private:
 		vector<vector<T> > mat;     //the > > for the compiler, it's not the >> operator
  		unsigned rows;
  		unsigned cols;

	public:
		Matrix(unsigned n, const T& _initial);
  		Matrix(unsigned _rows, unsigned _cols, const T& _initial);
  		Matrix(const Matrix<T>& rhs);
 		virtual ~Matrix();

  // Operator overloading, for "standard" mathematical matrix operations                                                                                                                                                          
  		Matrix<T>& operator=(const Matrix<T>& rhs);

  // Matrix mathematical operations                                                                                                                                                                                               
  		Matrix<T> operator+(const Matrix<T>& rhs);
  		Matrix<T>& operator+=(const Matrix<T>& rhs);
  		Matrix<T> operator-(const Matrix<T>& rhs);
  		Matrix<T>& operator-=(const Matrix<T>& rhs);
  		Matrix<T> operator*(const Matrix<T>& rhs);
  		Matrix<T>& operator*=(const Matrix<T>& rhs);

  // Matrix/scalar operations                                                                                                                                                                                                     
  		Matrix<T> operator+(const T& rhs);
  		Matrix<T> operator-(const T& rhs);
  		Matrix<T> operator*(const T& rhs);
  		Matrix<T> operator/(const T& rhs);

  // Matrix/vector operations
  		Matrix<T> transpose();
  		Matrix<T> getMinor(Matrix<T> A,unsigned p, unsigned q,unsigned n);
  		T determinant(Matrix<T> A,unsigned n);
		T determinant();    		
  		Matrix<T> Adjugate();   
		Matrix<T> inverse();                                                                                                                                                                                                    
  		vector<T> operator*(const vector<T>& rhs);
  		vector<T> diag_vec();
  		Matrix<T> swapperino(Matrix<T>& matri, unsigned row1, unsigned row2, unsigned col);
		/*unsigned rank(Matrix<T> minore, unsigned ordine); */  		
  		unsigned rank(); 	

  // Access the individual elements                                                                                                                                                                                               
  		T& operator()(const unsigned& row, const unsigned& col);
  		const T& operator()(const unsigned& row, const unsigned& col) const;

  // Access the row and column sizes                                                                                                                                                                                              
  		unsigned get_rows() const;
  		unsigned get_cols() const;
  		
  //printing the matrix with overloading the << operator
  		friend ostream& operator<< <> (ostream& os,const Matrix<T>& rhs);		//the <> is to declare a template function  :D

};

#include "MatrixMat.cpp"

#endif
