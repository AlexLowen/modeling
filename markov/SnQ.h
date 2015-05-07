//
//  SnQ.h
//  markov
//
//  Created by Alex Lowen on 3/28/15.
//  Copyright (c) 2015 Alex Lowen. All rights reserved.
//

#ifndef __markov__SnQ__
#define __markov__SnQ__

#include <stdio.h>


template <class T>
class stack {
    T* array;
    size_t sz;
    size_t lim;
    size_t tp;
    void grow();
    void copy(const T*);
public:
    size_t size(){return sz;}
    T index(size_t val){return array[val];}
    stack();
    ~stack();
    void push_back(const T&);
    T pop();
};

template<class T>
class queue {
    T* array;
    size_t sz;
    size_t lim;
    size_t head;
    size_t tail;
    void copy(const T*);
    void grow();
public:
    queue();
    ~queue();
    void enqueue(const T&);
    void dequeue();
    size_t size(){return sz;}
    size_t next(){return array[head];}
    
    
};


#include "SnQ.inl"
#endif /* defined(__markov__SnQ__) */
