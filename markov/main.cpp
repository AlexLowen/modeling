//
//  main.cpp
//  markov
//
//  Created by Alex Lowen on 3/28/15.
//  Copyright (c) 2015 Alex Lowen. All rights reserved.
//

#include <iostream>
#include "graph.h"
#include "Matrix.h"
#include "bag_of_holding.h"
#include <fstream>
#include <cstdlib>
#include <time.h>


int main(int argc, const char * argv[]) {
//    srand(time(NULL));
    
    double SS=double(1)/double(3);
    double SC=double(1)/double(3);
    double CC=double(1)/double(3);
    double SY=.5;
    double CY=.5;
    
    size_t tot=5;
    adj_matrix mat=*new adj_matrix(tot);
    
    adj_matrix mat3=*new adj_matrix(tot);
    for(size_t i=0; i!=tot; i++) {
        for(size_t j=0; j!=tot; j++) {
            mat3.change_edge(i+1,j+1, 0.0);
        }
    }
    mat3.change_edge(1,1,0.125);
    mat3.change_edge(2,1,0.25);
    mat3.change_edge(3,1,0.125);
    mat3.change_edge(4,1,0.25);
    mat3.change_edge(5,1,0.25);
    
    mat.change_edge(1,1,SS*0.25);
    mat.change_edge(1,2,SS*0.125);
    mat.change_edge(1,3,SS*0);
    mat.change_edge(1,4,SS*0.25);
    mat.change_edge(1,5,SS*0);
    mat.change_edge(2,1,SC*0.25);
    mat.change_edge(2,2,SC*0.25);
    mat.change_edge(2,3,SC*0.25);
    mat.change_edge(2,4,SC*0.25);
    mat.change_edge(2,5,SS*0.25);
    mat.change_edge(3,1,CC*0);
    mat.change_edge(3,2,CC*0.125);
    mat.change_edge(3,3,CC*0.25);
    mat.change_edge(3,4,CC*0);
    mat.change_edge(3,5,SS*0.25);
    mat.change_edge(4,1,SY*0.5);
    mat.change_edge(4,2,SY*0.25);
    mat.change_edge(4,3,SY*0);
    mat.change_edge(4,4,SY*0.25);
    mat.change_edge(4,5,SY*0.25);
    mat.change_edge(5,1,CY*0);
    mat.change_edge(5,2,CY*0.25);
    mat.change_edge(5,3,CY*0.5);
    mat.change_edge(5,4,CY*0.25);
    mat.change_edge(5,5,CY*0.25);
    
    mat.normalize(3,0.5);
    mat.normalize(3,5,0.5);
    adj_matrix mat2=mat;
    adj_matrix mat4=mat3;
    for(size_t i=0; i!=100; i++) {
        mat*=mat2;
    }
    mat3*=mat2;
    mat4*=mat;
    mat3.display();
    std::cout<<std::endl;
    mat4.display();
//    mat.change_edge(1,1,0.25);
//    mat.change_edge(1,2,.333333333333);
//    mat.change_edge(1,3,0.5);
//    mat.change_edge(1,4,.333333333333);
//    mat.change_edge(2,1,0.25);
//    mat.change_edge(2,2,.333333333333);
//    mat.change_edge(2,3,0.0);
//    mat.change_edge(2,4,.333333333333);
//    mat.change_edge(3,1,0.25);
//    mat.change_edge(3,2,0);
//    mat.change_edge(3,3,0.5);
//    mat.change_edge(3,4,0.0);
//    mat.change_edge(4,1,0.25);
//    mat.change_edge(4,2,.333333333333);
//    mat.change_edge(4,3,0.0);
//    mat.change_edge(4,4,.333333333333);
    
//    mat.change_edge(1,1,0.9);
//    mat.change_edge(2,1,0.1);
//    mat.change_edge(1,2,0.2);
//    mat.change_edge(2,2,0.8);
    /////////////
//    double randnum;
//    for(size_t j=1; j!=tot+1; j++) {
//        for(size_t i=1; i!=tot+1; i++) {
//            randnum=double(rand())/double(RAND_MAX);
//            mat.change_edge(i,j,randnum);
//        }
//    }
//    mat.normalize();
//    mat.display();
//    for(size_t i=1; i!=tot/2+1; i++) {
//        for(size_t j=1; j!=tot/2+1; j++) {
//            mat.change_edge(i,j,double(4)/double(3*tot));
//        }
//    }
//    for(size_t i=tot/2+1; i!=tot+1; i++) {
//        for(size_t j=1; j!=tot/2+1; j++) {
//            mat.change_edge(i,j,double(2)/double(3*tot));
//        }
//    }
//    for(size_t i=1; i!=tot/2+1; i++) {
//        for(size_t j=tot/2+1; j!=tot+1; j++) {
//            mat.change_edge(i,j,double(2)/double(tot));
//        }
//    }
//    for(size_t i=tot/2+1; i!=tot+1; i++) {
//        for(size_t j=tot/2+1; j!=tot+1; j++) {
//            mat.change_edge(i,j,0.0);
//        }
//    }
    
//    std::cout<<std::endl;
//    adj_matrix mat2=mat;
//    for(size_t i=0; i!=100; i++) {
//        mat.display();
//        mat.power_entry(2);
//        mat.power_entry(2);
//        mat.display();
//        mat.normalize();
//        mat.display();
//        mat*=mat2;
//        std::cout<<std::endl;
//        std::cout<<std::endl;
//    }
//    std::cout<<std::endl;
//    mat.display();
//    mat.file_display("text.txt");
//    std::string test="Kie3 o4c12 hi!dad... yaarKC.2.4 . ";
//    vec_of_words testvec=test;
//    testvec.display();
    
    
    return 0;
}
