//
//  SnQ.inl
//  markov
//
//  Created by Alex Lowen on 3/28/15.
//  Copyright (c) 2015 Alex Lowen. All rights reserved.
//

#include <stdio.h>
#include "SnQ.h"
template<typename T>
inline stack<T>::stack(){
    lim=1000;
    array=new T[lim];
    sz=0;
    return;
}
template<typename T>
inline stack<T>::~stack(){
    delete[] array;
    return;
}

template<typename T>
inline T stack<T>::pop()
{
    if(tp)
        return tp--;
    else return NULL;
}

template<typename T>
inline void stack<T>::copy(const T* ar)
{
    for(size_t i=0;i!=sz;i++) {
        array[i]=ar[i];
    }
    return;
}

template<typename T>
inline void stack<T>::grow()
{
    T* ret=new T[lim*2];
    lim*=2;
    T* temp=array;
    copy(ret);
    array=ret;
    delete[] temp;
    return;
    
}

template<typename T>
inline void stack<T>::push_back(const T& val)
{
    if(sz==0)
    {
        tp=0;
        array[tp]=val;
        return;
    }
    if(sz==lim-1)
        this->grow();
    tp++;
    array[tp]=val;
    return;
}


template<typename T>
inline queue<T>::queue()
{
    lim=1000;
    array=new T[lim];
    sz=0;
    return;
}

template<typename T>
inline queue<T>::~queue()
{
    delete[] array;
    return;
}

template<typename T>
inline void queue<T>::copy(const T* a)
{
    for(size_t i=tail;i!=sz;i++) {
        array[i]=a[i-tail];
    }
    size_t left_side=sz-tail;
    for(size_t i=0;i!=tail;i++) {
        array[i+left_side]=a[i];
    }
    return;
}

template<typename T>
inline void queue<T>::grow()
{
    T* ret=new T[lim*2];
    lim*=2;
    T* temp=array;
    copy(ret);
    array=ret;
    delete[] temp;
}

template<typename T>
inline void queue<T>::enqueue(const T& val)
{
    if(sz==0) {
        array[0]=val;
        head=0; tail=1;
        sz=1;
    }
    else if(tail==lim && head) {
        tail=1;
        array[0]=val;
        sz++;
    }
    else if(sz==lim) {
        grow();
        head=0;
        tail=sz;
        array[tail]=val;
        tail++;
        sz++;
    }
    else {
        array[tail]=val;
        tail++;
        sz++;
    }
    return;
}

template<typename T>
inline void queue<T>::dequeue()
{
    if(sz==0);
    else if(head==lim-1) {
        head=0; sz--;
    }
    else {
        head++;
        sz--;
    }
    return;
}
