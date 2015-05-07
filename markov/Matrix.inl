//
//  Matrix.inl
//  markov
//
//  Created by Alex Lowen on 3/29/15.
//  Copyright (c) 2015 Alex Lowen. All rights reserved.
//

#include "Matrix.h"
#include <stdio.h>
#include <iostream>

template<typename T>
inline Matrix<T>::Matrix(size_t x, size_t y){
    n=x;
    m=y;
    matrix=new T*[n];
    for (size_t i=0; i!=n; i++) matrix[i]=new T[m];
    return;
}

template<typename T>
inline Matrix<T>::Matrix(const Matrix<T>& mat){
    if(mat.matrix==NULL) return;
    n=mat.n;
    m=mat.m;
    matrix=new T*[n];
    for (size_t i=0; i!=n; i++) matrix[i]=new T[m];
    for(size_t i=0; i!=n; i++) {
        for(size_t j=0; j!=m; j++) {
            matrix[i][j]=mat.matrix[i][j];
        }
    }
    return;
}

template<typename T>
inline void Matrix<T>::display(){
    for(size_t j=0; j!=m; j++){
        for (size_t i=0; i!=n; i++) {
            std::cout<<' '<<matrix[i][j];
        }
        std::cout<<std::endl;
    }
    return;
}

template<typename T>
inline Matrix<T>::~Matrix(){
    for(size_t i=0; i!=n; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    return;
}

template<typename T>
inline Matrix<T> Matrix<T>::operator *=(const Matrix<T>& mat) {
    T** ret=new T*[n];
    for(size_t i=0; i!=n; i++) ret[i]=new T[m];
    T running=NULL;
    for(size_t j=0; j!=m; j++){
        for(size_t k=0; k!=mat.m; k++) {
            for(size_t i=0; i!=n; i++) {
                running+=matrix[i][j]*mat.matrix[k][i];
            }
            ret[k][j]=running;
            running=NULL;
        }
    }
    this->~Matrix();
    this->matrix=ret;
    return *this;
}
template<typename T>
inline void Matrix<T>::change(size_t i, size_t j, T val){
    this->matrix[i][j]=val;
    return;
}

template<typename T>
inline T Matrix<T>::entry(size_t i, size_t j) const{
    return matrix[i][j];
}

template<typename T>
inline bool Matrix<T>::visited(size_t i, size_t j) const{
    return matrix[i][j].visited;
}

template<typename T>
inline T* Matrix<T>::manipulate(size_t i, size_t j){
    T* ret=&matrix[i][j];
    return ret;
}

template<typename T>
inline void Matrix<T>::copy(const Matrix<T>& mat){
    if(n<mat.row() || m<mat.collumn()) return;
    for(size_t i=0; i!=n; i++) {
        for(size_t j=0; j!=m; j++) {
            matrix[i][j]=mat.entry(i,j);
        }
    }
    return;
}



