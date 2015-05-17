

#include "graph.h"
#include <iostream>
#include "SnQ.h"
#include <iomanip>
#include <string>
#include <fstream>

adj_list::adj_list() {
    lim=1000; sz=0;
    array=new vertex[lim];
}

void adj_list::clear_vertex(size_t v)
{
    if(array[v].first_edge==NULL) return;
    if(array[v].first_edge->next_edge==NULL) {
        delete array[v].first_edge;
        array[v].first_edge=NULL;
        return;
    }
    edge* temp1=array[v].first_edge;
    edge* temp2=array[v].first_edge->next_edge;
    array[v].first_edge=NULL;
    while(temp2->next_edge!=NULL) {
        delete temp1;
        temp1=temp2;
        temp2=temp2->next_edge;
    }
    delete temp1; temp1=NULL;
    delete temp2; temp2=NULL;
    return;
}

adj_list::~adj_list() {
    size_t i=0;
    while(i!=sz) {clear_vertex(i); i++;}
    delete[] array; array=NULL;
    return;
}


void adj_list::add_vertex() {
    vertex* nvert=new vertex;
    nvert->u=sz+1;
    nvert->first_edge=NULL;
    nvert->visited=false;
    array[nvert->u]=*nvert;
    sz++; delete nvert;
    nvert=NULL;
    return;
    
}

void adj_list::add_edge(size_t i, size_t j) {
    if(sz<i || sz<j) return;
    
    edge* npair=new edge;
    npair->v=j;
    
    if(array[i].first_edge==NULL) {
        
        npair->next_edge=NULL;
        array[i].first_edge=npair;
        npair=NULL;
    }
    else {
        edge* temp=&*array[i].first_edge;
        if (npair->v<=temp->v) {
            npair->next_edge=temp;
            array[i].first_edge=npair;
            npair=NULL;
            return;
        }
        while(temp->next_edge!=NULL && npair->v>=temp->next_edge->v) {
            temp=temp->next_edge;
        }
        if(temp->next_edge==NULL) {
            npair->next_edge=NULL;
            temp->next_edge=npair;
        }
        else {
            npair->next_edge=temp->next_edge;
            temp->next_edge=npair;
        }
        npair=NULL;
    }
    return;
}

void adj_list::reset() {
    for(size_t i=0;i!=sz;i++) {
        array[i].visited=false;
    }
    return;
}

void adj_list::DFT(size_t val) {
    if(val>=sz) return;
    array[val].visited=true;
    std::cout<<"visiting "<<val<<std::endl;
    if(array[val].first_edge==NULL) return;
    edge* temp=array[val].first_edge;
    while(temp->next_edge!=NULL) {
        if(!array[temp->v].visited) {
            std::cout<<"visiting "<<temp->v<<std::endl;
            DFT(temp->v);
        }
        temp=temp->next_edge;
    }
    if(!array[temp->v].visited) {
        DFT(temp->v);
    }
}

vertex* adj_list::DFS(size_t start, size_t val) {
    
    std::cout<<"At vertex "<<start<<std::endl;
    
    array[start].visited=1;
    
    if(array[start].u==val) {vertex* ret=&array[start]; return ret;}
    if(array[start].first_edge==NULL) return NULL;
    
    edge* checking=array[start].first_edge;
    vertex* temp;
    
    while(checking->next_edge!=NULL) {
        while(array[checking->v].visited==0) {
            
            
            temp=DFS(checking->v, val);
            if(temp==NULL) checking=checking->next_edge;
            else return temp;
            
        }
        checking=checking->next_edge;

    }
    if(array[checking->v].visited) return NULL;
    temp=DFS(checking->v, val);
    if(temp==NULL) return NULL;
    else return temp;
}

void adj_list::BFT(size_t start) {
    
    queue<size_t> qu;
    qu.enqueue(start);
    while(qu.size()) {
        std::cout<<"visiting vertex "<<qu.next()<<std::endl;
        array[qu.next()].visited=1;
        if(array[qu.next()].first_edge) {
            edge* current=array[qu.next()].first_edge;
            do {
                if(array[current->v].visited==0) qu.enqueue(current->v);
                current=current->next_edge;
            }
            while(current);
        }
        qu.dequeue();
    }
    reset();
    return;
}

vertex* adj_list::BFS(size_t start, size_t finish) {
    vertex* ret=NULL;
    queue<size_t> qu;
    qu.enqueue(start);
    while(qu.size() && qu.next()!=finish) {
        std::cout<<"visiting vertex "<<qu.next()<<std::endl;
        array[qu.next()].visited=1;
        if(array[qu.next()].first_edge) {
            edge* current=array[qu.next()].first_edge;
            do {
                if(array[current->v].visited==0) qu.enqueue(current->v);
                current=current->next_edge;
            }
            while(current);
        }
        qu.dequeue();
    }
    reset();
    if(qu.size())
        std::cout<<"At vertex "<<finish<<std::endl;
    else {
        std::cout<<"I couldn't find it!";
    }
    array[start].visited=1;
    return ret;
}

void w_adj_list::add_edge(size_t i, size_t j, double w) {
    if(sz<i || sz<j) return;
    
    wedge* npair=new wedge;
    npair->v=j;
    npair->weight=w;
    
    if(array[i].first_edge==NULL) {
        
        npair->next_edge=NULL;
        array[i].first_edge=npair;
        npair=NULL;
    }
    else {
        wedge* temp=array[i].first_edge;
        if (npair->v<=temp->v) {
            npair->next_edge=temp;
            array[i].first_edge=npair;
            npair=NULL;
            return;
        }
        while(temp->next_edge!=NULL && npair->v>=temp->next_edge->v) {
            temp=temp->next_edge;
        }
        if(temp->next_edge==NULL) {
            npair->next_edge=NULL;
            temp->next_edge=npair;
        }
        else {
            npair->next_edge=temp->next_edge;
            temp->next_edge=npair;
        }
        npair=NULL;
    }
    return;

}

w_adj_list::w_adj_list(){
    lim=1000; sz=0;
    array=new wertex[lim];
}

double** w_adj_list::matrix(){
    double** ret=new double*[sz];
    for(size_t i=0; i!=sz; i++)
        ret[i]=new double[sz];
    wedge* temp;
    for(size_t i=0; i!=sz; i++) {
        temp=array[i].first_edge;
        for(size_t j=0; j!=sz; j++) {
            ret[i][j]=0.0;
        }
        while(temp) {
            ret[i][temp->v]=temp->weight;
        }
    }
    return ret;
}

void adj_matrix::reset(){
    for(size_t i=0; i!=sz; i++) {
        for(size_t j=0; j!=sz; j++) {
            change_visited(i, j, false);
        }
    }
    return;
}

void adj_matrix::change_edge(size_t i, size_t j, double w) {
    mertex* edge=matrix.manipulate(i-1, j-1);
    edge->u=w;
    return;
}

void adj_matrix::change_visited(size_t i, size_t j, bool b) {
    mertex* edge=matrix.manipulate(i-1, j-1);
    edge->visited=b;
    return;
}

adj_matrix::adj_matrix(size_t s) {
    sz=s;
    lim=1000;
    matrix=*new Matrix<mertex>(lim, lim);
    mertex* temp;
    for(size_t i=0; i!=lim; i++) {
        for(size_t j=0; j!=lim; j++) {
            temp=matrix.manipulate(i,j);
            temp->visited=false;
            temp->u=0.0;
        }
    }
    return;
}

adj_matrix adj_matrix::operator*=(const Matrix<mertex>& mat){
    Matrix<mertex> ret(sz, sz);
    mertex running; running.u=0.0;
    for(size_t j=0; j!=sz; j++){
        for(size_t k=0; k!=mat.row(); k++) {
            for(size_t i=0; i!=sz; i++) {
                running.u+=matrix.entry(i,j).u*mat.entry(k,i).u;
            }
            ret.manipulate(k,j)->u=running.u;
            running.u=0.0;
        }
    }
    this->~adj_matrix();
    this->matrix=ret;
    return *this;
}

adj_matrix adj_matrix::operator*=(const adj_matrix& mat){
    double* change=new double[sz];
    double running=0.0;
    for(size_t j=0; j!=sz; j++){
        for(size_t k=0; k!=mat.size(); k++) {
            for(size_t i=0; i!=sz; i++) {
                running+=matrix.entry(i,j).u*mat.entry(k,i).u;
            }
            change[k]=running;
            running=0.0;
        }
        for(size_t i=0; i!=sz; i++) {
            matrix.manipulate(i,j)->u=change[i];
        }
    }
    return *this;
}

adj_matrix::adj_matrix(const Matrix<mertex>& mat){
    if (mat.collumn()!=mat.row()) return;
    *this=*new adj_matrix(1000);
    sz=mat.row();
    this->matrix.copy(mat);
    return;
}

void adj_matrix::display(){
    for(size_t j=0; j!=sz; j++){
        for (size_t i=0; i!=sz; i++) {
            std::cout<<' '<<std::setprecision(2)<<double(matrix.entry(i,j).u);
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    return;
}

void adj_matrix::file_display(std::string fname) {
    std::ofstream myfile;
    myfile.open (fname);
    if(myfile.is_open()){
        for(size_t j=0; j!=sz; j++){
            for (size_t i=0; i!=sz; i++) {
                myfile <<' '<<std::setprecision(2)<<double(matrix.entry(i,j).u);
            }
            myfile<<"\n";
        }
        myfile<<"\n";
        myfile.close();
    }
    else {
        std::cout<<"unable to open file"<<std::endl;
    }
    return;
}

void adj_matrix::power_entry(size_t power){
    double change;
    size_t cur_power;
    for(size_t i=0; i!=sz; i++) {
        for(size_t j=0; j!=sz; j++) {
            change=matrix.entry(i,j).u;
            cur_power=power;
            while(--cur_power) {
                matrix.manipulate(i,j)->u*=change;
            }
        }
    }
    return;
}

void adj_matrix::normalize(){
    double running_tot;
    double inverse;
    for(size_t j=0; j!=sz; j++) {
        running_tot=0.0;
        for(size_t i=0; i!=sz; i++) {
            running_tot+=matrix.entry(i,j).u;
        }
        inverse=double(1)/double(running_tot);
        for(size_t i=0; i!=sz; i++) {
            matrix.manipulate(i,j)->u*=inverse;
        }
    }
    return;
}

void adj_matrix::normalize(size_t n, size_t m, double scale_down){
    double running_tot;
    double inverse;
    for(size_t j=0; j!=m; j++) {
        running_tot=0.0;
        for(size_t i=0; i!=n; i++) {
            running_tot+=matrix.entry(i,j).u;
        }
        inverse=double(scale_down)*double(1)/double(running_tot);
        for(size_t i=0; i!=n; i++) {
            matrix.manipulate(i,j)->u*=inverse;
        }
    }
}

void adj_matrix::normalize(size_t n, double scale_down){
    double running_tot;
    double inverse;
    size_t size=this->size();
    for(size_t j=0; j!=size; j++) {
        running_tot=0.0;
        for(size_t i=n; i!=size; i++) {
            running_tot+=matrix.entry(i,j).u;
        }
        inverse=double(scale_down)*double(1)/double(running_tot);
        for(size_t i=n; i!=size; i++) {
            matrix.manipulate(i,j)->u*=inverse;
        }
    }
}


