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
    vec_of_words(std::string&, char);
    std::vector<std::string> strip(std::string&);
    void next_file(const std::string&, char);
    void display();
    size_t size() const {return document.size();}
};

struct bag{
    std::string key;
    int multiplicity;
    bag* next;
    //~bag(){next=NULL;}
};

class hashST{
public:
    bag** hash_table;
    std::vector<std::string> symbol_table;
    int lim;
    
    hashST();
    hashST(int);
    hashST(const hashST&);
    ~hashST();
    
    void clear(int);
    int hash(std::string) const;

    int get (const std::string&) const;
    void put(const std::string&, int);
    
    //for sets
    void put(const std::string&);
    void del(const std::string&);
    int size() const;
    std::vector<std::string> keys();
    void display();
    void contain(const vec_of_words&, int);
    
};


class bag_of_holding: public hashST{
public:
    bag_of_holding();
    bag_of_holding(const vec_of_words&, int);
    bag_of_holding(const vec_of_words&, int, char);
    bag_of_holding(const bag_of_holding&);
    double cos(const bag_of_holding&);
    int operator *(const bag_of_holding&);
    double mag() const;
};
#endif /* defined(__markov__bag_of_holding__) */
