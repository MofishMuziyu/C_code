#include<iostream>
using namespace std;
struct Surface;
struct Vertex;
struct Half_edge;

struct Half_edge
{
    int edge_id;
    Half_edge *next_edge;
    Half_edge *op_edge;
    Vertex *vertex;
    Surface *surface;
};

struct Surface
{
    int surface_id;
    Half_edge *edge;
};


struct Vertex{
    int vertex_id;
    float x;
    float y;
    float z;
    Half_edge *egde;
};
class  HE{
    private:
        Vertex  *vertex;
        Surface  *surface;
        Half_edge  *half_edge;
    public:
        HE(Vertex *v, Surface *s ,Half_edge  *edge);
        ~HE();
        void traverse_edge_surface(Half_edge *edge);
        void traverse_vertex_surface(Vertex *vertex);
        void traverse_vertex_edge(Vertex *vertex);
        void face_edge(Surface *surface);
        void face_face(Surface *surface);
};


HE::HE(Vertex *v, Surface *s ,Half_edge  *edge){  //HE初始化
    vertex = new Vertex;
    if (vertex==NULL){cout<<"点内存分配失败"<<endl;}
    vertex = v;
    surface = new  Surface;
    if (surface==NULL){cout<<"面内存分配失败"<<endl;}
    surface = s;
    half_edge = new Half_edge;
    if (half_edge==NULL){cout<<"边内存分配失败"<<endl;}
    half_edge = edge;
}
HE::~HE(){  //HE析构
    if(vertex!=NULL){
        delete vertex;
    }
    if(surface!=NULL){
        delete surface;
    }
    if(half_edge!=NULL){
        delete half_edge;
    }
}
void HE::traverse_edge_surface(Half_edge *edge){     //遍历并输出一个半边的所有邻接面
    Half_edge *start_edge = new Half_edge;//确定初始半边
    start_edge = edge;
    do
    {
        cout<<"The surface_id around the edge is\t"<<edge->surface->surface_id<<endl;

        edge = edge->op_edge;
    } while (edge!=start_edge);
    
}

void HE::traverse_vertex_surface(Vertex *vertex){//遍历一个点周围的所有面
    Half_edge *start_edge = new Half_edge;
    start_edge = vertex->egde;//确定初始点所对应的半边
    Half_edge *edge = vertex->egde;
    do
    {
        cout<<"The id of surface around the vertex is:\t"<<edge->surface->surface_id<<endl;
        
        edge = edge->op_edge->next_edge;
    } while (edge != start_edge);
    
}

void   HE::traverse_vertex_edge(Vertex *vertex){  //遍历由一个点出发的所有的半边的id
    Half_edge *start_edge = new Half_edge;
    start_edge = vertex->egde;
    Half_edge *edge = vertex->egde;
    do
    {
        cout<<"The id of half_edge from the vertex is:\t"<<edge->edge_id<<endl;

        edge = edge->op_edge->next_edge;
        
    } while (edge!=start_edge);
    
}

void  HE::face_edge(Surface *surface){//遍历一个面内的所有半边
    Half_edge *start_edge = new Half_edge;
    start_edge = surface->edge;
    Half_edge * edge = surface->edge;
    do
    {
        cout<<"The half_edge of the surface is:\t"<<edge->edge_id<<endl;
        edge = edge->next_edge;
    } while (edge != start_edge);
    

}

void  HE::face_face(Surface *surface){//遍历一个面周围的所有面
    Half_edge *start_edge = new Half_edge;
    start_edge = surface->edge;
    Half_edge * edge = surface->edge;
    do
    {
        cout<<"The surface around the surface is:\t"<<edge->op_edge->surface->surface_id<<endl;
        edge = edge->next_edge;
    } while (edge != start_edge);
}


int main(){



}