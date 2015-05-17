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
#include <fstream>

std::vector<std::string> vec_of_words::strip(std::string& str) {
    size_t current=0;
    size_t change=current;
    int num;
    while(current!=str.size()) {
        num=int(str[current]);
        if(num==32 && str[change-1]!=' '){
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

vec_of_words::vec_of_words(std::string& str, char s) {
    std::ifstream myfile;
    myfile.open(str);
    if(myfile.is_open()) {
        std::ifstream in(str);
        std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        document=strip(s);
        myfile.close();
    }
    else {
        std::cout<<"Unable to open file"<<std::endl;
    }
}

void vec_of_words::display() {
    for(size_t i=0; i!=document.size(); i++) {
        std::cout<<document[i]<<std::endl;;
    }
    std::cout<<std::endl;
    return;
}

void vec_of_words::next_file(const std::string& str, char c) {
    document.clear();
    std::ifstream myfile;
    myfile.open(str);
    if(myfile.is_open()) {
        std::ifstream in(str);
        std::string s((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        document=strip(s);
        myfile.close();
    }
    else {
        std::cout<<"Unable to open file"<<std::endl;
    }
}

int hashST::hash(std::string str) const
{
    
    std::hash<std::string> hasher;
    auto hashed=hasher(str);
    return int(hashed%lim);
}

hashST::hashST() {
    lim=1000;
    hash_table=new bag*[lim];
    for(size_t i=0; i!=lim; i++) {
        hash_table[i]=NULL;
    }
    return;
}

hashST::hashST(int l) {
    lim=l;
    hash_table=new bag*[lim];
    for(size_t i=0; i!=l; i++) {
        hash_table[i]=NULL;
    }
    return;
}

void hashST::contain(const vec_of_words& doc, int l) {
    symbol_table.clear();
    for (int i=0; i!=lim; i++) {
        clear(i);
    }
    delete[] hash_table;
    lim=l;
    hash_table=new bag*[lim];
    for(size_t i=0; i!=l; i++) {
        hash_table[i]=NULL;
    }
    for(size_t i=0; i!= doc.size(); i++) {
        put(doc.document[i], 1);
    }
    return;
}

void hashST::clear(int index){
    bag* iter=hash_table[index];
    bag* iter2=iter;
    while(iter){
        iter=iter->next;
        iter2->next=NULL;
        delete iter2;
        iter2=iter;
    }
    return;
}

hashST::~hashST() {
    //for(size_t i=0; i!=symbol_table.size(); i++) {
      //  clear(hash(symbol_table[i]));
    //}
    delete[] hash_table;
}

int hashST::get (const std::string& k) const{
    bag* iter=hash_table[hash(k)];
    while(iter) {
        if(iter->key==k) break;
        iter=iter->next;
    }
    if (iter) {
        return iter->multiplicity;
    }
    return 0;
}

void hashST::put(const std::string& k, int val) {
    bag* temp;
    if(get(k)==0) {
        symbol_table.push_back(k);
        if(hash_table[hash(k)]) {
            temp=hash_table[hash(k)]->next;
            hash_table[hash(k)]->next=new bag;
            hash_table[hash(k)]->next->next=temp;
            hash_table[hash(k)]->next->key=k;
            hash_table[hash(k)]->next->multiplicity=val;
        }
        else {
            hash_table[hash(k)]=new bag;
            hash_table[hash(k)]->key=k;
            hash_table[hash(k)]->multiplicity=val;
        }
    }
    else {
        bag* iter=hash_table[hash(k)];
        while(iter->key!=k) {
            iter=iter->next;
        }
        iter->multiplicity+=val;
    }
}

void hashST::put(const std::string& k) {
    bag* temp;
    if(get(k)==0) {
        symbol_table.push_back(k);
        if(hash_table[hash(k)]) {
            temp=hash_table[hash(k)]->next;
            hash_table[hash(k)]->next=new bag;
            hash_table[hash(k)]->next->next=temp;
            hash_table[hash(k)]->next->key=k;
            hash_table[hash(k)]->next->multiplicity=1;
        }
        else {
            hash_table[hash(k)]=new bag;
            hash_table[hash(k)]->key=k;
            hash_table[hash(k)]->multiplicity=1;
        }
    }
    return;
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
    symbol_table=that.symbol_table;
    lim=that.lim;
    hash_table=new bag*[this->lim];
    for(int i=0; i!=that.size(); i++) {
        put(that.symbol_table[i], 1);
    }
    return;
}

void hashST::display() {
    std::vector<std::string> ans=keys();
    for(size_t i=0; i!=ans.size(); i++) {
        std::cout<<ans[i]<<": "<<get(ans[i])<<std::endl;
    }
    std::cout<<std::endl;
    return;
}

int bag_of_holding::operator *(const bag_of_holding& that) {
    int ret=0;
    
    for(int i=0; i!=this->size(); i++) {
        ret+=this->get(this->symbol_table[i])*that.get(this->symbol_table[i]);
    }
    return ret;
}

bag_of_holding::bag_of_holding(const vec_of_words& doc, int l) {
    
    lim=l;
    for(size_t i=0; i!= doc.size(); i++) {
        put(doc.document[i],1);
    }
    return;
}

bag_of_holding::bag_of_holding(const bag_of_holding& that) {
    
    lim=that.lim;
    for(size_t i=0; i!=that.symbol_table.size(); i++) {
        put(that.symbol_table[i],1);
    }
    
    return;
}

double bag_of_holding::mag() const{
    int ret=0;
    int temp;
    for(int i=0; i!=this->symbol_table.size(); i++) {
        temp=this->get(this->symbol_table[i]);
        ret+=temp*temp;
    }
    return sqrt(ret);
}

double bag_of_holding::cos(const bag_of_holding& that) {
    //double cosine=double(*this*that);
    double cosine=double(*this*that)/(double(this->mag())*double(that.mag()));
    return cosine;
}

bag_of_holding::bag_of_holding(const vec_of_words& doc, int l, char) {
    
    lim=l;
    for(size_t i=0; i!= doc.size(); i++) {
        put(doc.document[i]);
    }
    return;
}
