

#ifndef __markov__graph__
#define __markov__graph__

#include <stdio.h>
#include "Matrix.h"
#include <fstream>


struct edge {
    size_t v;
    edge* next_edge;
    edge(){v=0; next_edge=NULL;}
    ~edge(){next_edge=NULL;}
};

struct vertex {
    size_t u;
    bool visited;
    edge* first_edge;
};

class adj_list {
protected:
    vertex* array;
    size_t sz;
    size_t lim;
public:
    adj_list();
    ~adj_list();
    void clear_vertex(size_t);
    void add_edge(size_t, size_t);
    void add_vertex();
    vertex index(size_t u) const{return array[u];}
    size_t size() const{return sz;}
    void reset();
    void DFT(size_t);
    vertex* DFS(size_t,size_t);
    void BFT(size_t);
    vertex* BFS(size_t,size_t);
    
};

struct wedge : edge {
    double weight;
    wedge* next_edge;
};

struct wertex : vertex {
    wedge* first_edge;
};

class w_adj_list : public adj_list {
    wertex* array;
public:
    w_adj_list();
    void add_edge(size_t, size_t, double);
    double** matrix();
};

struct mertex {
    double u;
    bool visited;
};

class adj_matrix {
protected:
    Matrix<mertex> matrix;
    size_t sz;
    size_t lim;
public:
    void display();
    void file_display(std::string);
    adj_matrix(size_t); //destructor will come from my matrix module
    adj_matrix(const Matrix<mertex>&);
    void change_visited(size_t, size_t, bool);
    void change_edge(size_t, size_t, double);
    void add_vertex(){sz++; return;}
    mertex entry(size_t i, size_t j) const {return matrix.entry(i,j);}
    size_t size() const {return sz;}
    void reset();
    void DFT(size_t);
    mertex* DFS(size_t,size_t);
    void BFT(size_t);
    mertex* BFS(size_t,size_t);
    adj_matrix operator*=(const Matrix<mertex>& mat);
    adj_matrix operator*=(const adj_matrix&);
    void power_entry(size_t);
    void normalize();
    void normalize(size_t,size_t,double);
    void normalize(size_t, double);
};





#endif /* defined(__markov__graph__) */
