//
//  Matrix.h
//  markov
//
//  Created by Alex Lowen on 3/29/15.
//  Copyright (c) 2015 Alex Lowen. All rights reserved.
//

#ifndef __markov__Matrix__
#define __markov__Matrix__

#include <stdio.h>

template<class T>
class Matrix{
    T** matrix;
    size_t n;
    size_t m;
public:
    void copy(const Matrix<T>&);
    Matrix() {matrix=NULL; return;}
    Matrix(size_t, size_t);
    Matrix(const Matrix<T>&);
    ~Matrix();
    size_t row() const{return n;}
    size_t collumn()const {return m;}
    bool visited(size_t, size_t) const;
    void change(size_t, size_t, T val);
    T* manipulate(size_t, size_t);
    T entry(size_t, size_t) const;
    void display();
    Matrix<T> operator *=(const Matrix<T>&);
    Matrix<T> operator *=(double);
    Matrix<T> operator +=(const Matrix<T>&);
    
};

#include "Matrix.inl"
#endif /* defined(__markov__Matrix__) */
