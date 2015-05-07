//
//  bag_of_holding.cpp
//  markov
//
//  Created by Alex Lowen on 4/3/15.
//  Copyright (c) 2015 Alex Lowen. All rights reserved.
//

#include "bag_of_holding.h"
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

std::vector<std::string> vec_of_words::strip(std::string& str) {
    size_t current=0;
    size_t change=current;
    int num;
    while(current!=str.size()) {
        num=int(str[current]);
        if(num==32){
            str[change]=' ';
            change++;
        }
        else if(num>96 && num<123){
            str[change]=char(num);
            change++;
        }
        else if(num>64 && num<91) {
            str[change]=char(num+32);
            change++;
        }
        else;
        current++;
        
    }
    size_t ret_sz=change;
    std::vector<std::string> ret;
    change=current=0;
    while(current<ret_sz){
        while(int(str[current])!=32) if(++current>=ret_sz) break;
        ret.push_back(str.substr(change,current-change));
        current++;
        change=current;
    }
    return ret;
}

vec_of_words::vec_of_words(std::string& str) {
    document=strip(str);
    return;
}

void vec_of_words::display() {
    for(size_t i=0; i!=document.size(); i++) {
        std::cout<<document[i]<<' ';
    }
    std::cout<<std::endl;
    return;
}

int hashST::hash(std::string str)
{
    
    std::hash<std::string> hasher;
    auto hashed=hasher(str);
    return int(hashed%lim);
}

hashST::hashST(int l) {
    lim=l;
    hash_table=new bag*[lim];
}

void hashST::clear(int index){
    bag* iter=hash_table[index];
    bag* iter2=iter;
    while(iter){
        iter=iter->next;
        delete iter2;
        iter2=iter;
    }
    return;
}

hashST::~hashST() {
    for(size_t i=0; i!=symbol_table.size(); i++) {
        clear(hash(symbol_table[i]));
    }
    delete[] hash_table;
}

int hashST::get(const std::string& k) {
    bag* iter=hash_table[hash(k)];
    while(iter) {
        if(iter->key==k) return iter->multiplicity;
    }
    return 0;
}

void hashST::put(const std::string& k, int val) {
    bag* iter=hash_table[hash(k)]; bag* temp;
    bag* put_there = new bag;
    if(get(k)==0) {
        if(iter) {
            temp=iter->next;
            iter->next=put_there;
            put_there->next=temp;
            put_there->key=k;
            put_there->multiplicity=val;
        }
    }
    else {
        while(iter->key!=k) {
            iter=iter->next;
        }
        iter->multiplicity=+val;
    }
}

void hashST::del(const std::string& k) {
    bag* temp;
    bag* iter=hash_table[hash(k)];
    if (iter==NULL) return;
    while(iter->next && iter->next->key!=k) {
        iter=iter->next;
    }
    if(iter->next) {
        temp=iter->next;
        iter->next=temp->next;
        delete temp;
        iter=NULL;
    }
    return;
}

std::vector<std::string> hashST::keys() {
    return symbol_table;
}

int hashST::size() const{
    return int(symbol_table.size());
}

hashST::hashST(const hashST& that) {
    this->symbol_table=that.symbol_table;
    this->lim=that.lim;
    this->hash_table=new bag*[this->lim];
    for(int i=0; i!=that.size(); i++) {
        this->put(that.symbol_table[i], 1);
    }
    return;
}

int bag_of_holding::operator *(const bag_of_holding& that) {
    if(this->bag->size()!=that.bag->size()) return NULL;
    int ret=0;
    hashST* this_bag=this->bag;
    hashST* that_bag=that.bag;
    
    for(int i=0; i!=this_bag->size(); i++) {
        ret+=this_bag->get(this_bag->symbol_table[i])*that_bag->get(that_bag->symbol_table[i]);
    }
    return ret;
}

bag_of_holding::bag_of_holding(const bag_of_holding& that) {
    
    this->bag=that.bag;
    
    return;
}

double bag_of_holding::mag() const{
    int ret=0;
    int temp;
    hashST* this_bag=this->bag;
    for(int i=0; i!=this_bag->symbol_table.size(); i++) {
        temp=this_bag->get(this_bag->symbol_table[i]);
        ret+=temp*temp;
    }
    return sqrt(ret);
}

double bag_of_holding::cos(const bag_of_holding& that) {
    double cosine=double(*this*that)/double(this->mag()*that.mag());
    return cosine;
}

