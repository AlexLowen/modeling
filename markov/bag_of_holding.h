//
//  bag_of_holding.h
//  markov
//
//  Created by Alex Lowen on 4/3/15.
//  Copyright (c) 2015 Alex Lowen. All rights reserved.
//

#ifndef __markov__bag_of_holding__
#define __markov__bag_of_holding__

#include <stdio.h>
#include <vector>
#include <string>

class vec_of_words{
public:
    std::vector<std::string> document;
    vec_of_words(std::string&);
    std::vector<std::string> strip(std::string&);
    void display();
};

struct bag{
    std::string key;
    int multiplicity;
    bag* next;
};

class hashST{
public:
    bag** hash_table;
    std::vector<std::string> symbol_table;
    int lim;
    
    hashST(int);
    hashST(const hashST&);
    ~hashST();
    
    void clear(int);
    int hash(std::string);

    int get(const std::string&);
    void put(const std::string&, int);
    void del(const std::string&);
    int size() const;
    std::vector<std::string> keys();
    
};

class bag_of_holding{
public:
    hashST* bag;
    bag_of_holding(const bag_of_holding&);
    double cos(const bag_of_holding&);
    int operator *(const bag_of_holding&);
    double mag() const;
};
#endif /* defined(__markov__bag_of_holding__) */
