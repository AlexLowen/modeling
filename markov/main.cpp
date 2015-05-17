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
    
    //int tot_file=2;
    std::string yaar="test1.txt";
    vec_of_words vec(yaar, 'r');
    std::vector<bag_of_holding*> bg;
    bag_of_holding goodies(vec, 1000);
    bag_of_holding* pnt;
    pnt=&goodies;
    bg.push_back(pnt);

    yaar="test0.txt";
    vec_of_words vec1(yaar, 'r');
    bag_of_holding goodies1(vec1, 1000);
    pnt=&goodies1;
    bg.push_back(pnt);
    
    yaar="test2.txt";
    vec_of_words vec2(yaar, 'r');
    bag_of_holding goodies2(vec2, 1000);
    pnt=&goodies2;
    bg.push_back(pnt);
    
    yaar="test3.txt";
    vec_of_words vec3(yaar, 'r');
    bag_of_holding goodies3(vec3, 1000);
    pnt=&goodies3;
    bg.push_back(pnt);
    
    adj_matrix Tmatrix=4;
    Tmatrix.change_edge(1, 1, 1.0);
    Tmatrix.change_edge(1, 2, bg[0]->cos(*bg[1]));
    Tmatrix.change_edge(1, 3, bg[0]->cos(*bg[2]));
    Tmatrix.change_edge(1, 4, bg[0]->cos(*bg[3]));
    
    Tmatrix.change_edge(2, 1, bg[1]->cos(*bg[0]));
    Tmatrix.change_edge(2, 2, 1.0);
    Tmatrix.change_edge(2, 3, bg[1]->cos(*bg[2]));
    Tmatrix.change_edge(2, 4, bg[1]->cos(*bg[3]));
    
    Tmatrix.change_edge(3, 1, bg[2]->cos(*bg[0]));
    Tmatrix.change_edge(3, 2, bg[1]->cos(*bg[2]));
    Tmatrix.change_edge(3, 3, 1.0);
    Tmatrix.change_edge(3, 4, bg[3]->cos(*bg[2]));
    
    Tmatrix.change_edge(4, 1, bg[0]->cos(*bg[3]));
    Tmatrix.change_edge(4, 2, bg[1]->cos(*bg[3]));
    Tmatrix.change_edge(4, 3, bg[2]->cos(*bg[3]));
    Tmatrix.change_edge(4, 4, 1.0);
    
    Tmatrix.normalize();
    adj_matrix Longterm_matrix=Tmatrix;
    
    for(size_t i=0; i!=100; i++) {
        Longterm_matrix*=Tmatrix;
        Longterm_matrix.power_entry(2);
        Longterm_matrix.normalize();
        
    }
    
    Longterm_matrix.display();
    
    return 0;
}
