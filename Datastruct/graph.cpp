#include <bits/stdc++.h>

using namespace std;

#define MAX_VERTEX_NUM  20                              //图的最大顶点
#define INF             10000                           //最大权值
typedef enum{ DG, DN, UDG, UDN } GraphKind;             //图的种类
int num_1, num_2;                                                //判断是否是连通图
int sum;                                                //连通分量的个数

class GraphMat
{

public:

    GraphMat(GraphKind k);
    void CreateGraph();                                 //构造一个图
    void BFSTraverse();                                 //广度优先遍历
    void BFSTraverse_queue();
    void DFSTraverse();                                 //深度优先遍历
    void DFSTraverse_norecursive();                     //深搜非递归

private:

    GraphKind kind;             //图的种类。枚举类型:有向图DG，有向网DN，无向图UDG，无向网UDN。
    int vex_num;                //图的顶点个数
    int vexs[MAX_VERTEX_NUM];  //顶点的数据值数组GraphMat(GraphKind k) :kind(k), vex_num(0);
    int arc_num;                //图的边（弧）个数
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];  //邻接矩阵。对图：用1或0表示两顶点是否相邻；对网：表示两顶点之间的权值。
    bool is_trav[MAX_VERTEX_NUM];  //遍历标志
    void BFSFunction(int);                              //广度优先
    void DFSFunction(int);                              //深度优先

};

GraphMat::GraphMat (GraphKind k = UDG) : kind(k), vex_num(0), arc_num(0)
{
    //清空矩阵
    for ( int i = 0; i < MAX_VERTEX_NUM; ++i )
        for ( int j = 0; j < MAX_VERTEX_NUM; ++j )
            arcs[i][j] = INF;                           //设置矩阵中各元素的值为最大值  
    
    //清空遍历标志
    for ( int i = 0; i < MAX_VERTEX_NUM; ++i )
        is_trav[i] = 0;
}

void GraphMat::CreateGraph ()
{
    cout << "输入顶点元素的个数:" << endl;
    cin >> vex_num;
    cout << "输入顶点元素的类型值:" << endl;
    for (int i = 0; i < vex_num; ++i){
        cin >> vexs[i];
    }

    cout << "输入邻接矩阵的边的个数:" << endl;
    cin >> arc_num;
    cout << "输入邻接矩阵:" << endl;
    for ( int i = 0; i < vex_num; ++i )
        for (int j = 0; j < vex_num; ++j)
            cin >> arcs[i][j];

}

//广度优先遍历
void GraphMat::BFSTraverse ()
{
    //将标记清0   bool类型,true为1，false为0
    for ( int i = 0; i < vex_num; ++i )
        is_trav[i] = 0;
    
    //对顶点遍历
    for ( int i = 0; i < vex_num; ++i )
        BFSFunction(i);
    
    cout << endl;

}

void GraphMat::BFSFunction (int i)
{

    if ( !is_trav[i] ) {
        is_trav[i] = 1;                                     //标记顶点
        cout << vexs[i] << " ";
    }

    for ( int j = 0; j < vex_num; ++j ) {
        if ( arcs[i][j] != 0 && !is_trav[j] ) {
            cout << vexs[j] << " ";
            is_trav[j] = 1;
        }
    }

}

void GraphMat::DFSTraverse ()
{
    //将标记清0   bool类型,true为1，false为0
    for ( int i = 0; i < vex_num; ++i )
        is_trav[i] = 0;

    //对顶点遍历
    for ( int i = 0; i < vex_num; ++i ) {
        if ( !is_trav[i] ) {
            ++sum;
            num_1 = 0;
            DFSFunction(i);
            
            if ( num_1 > num_2 )
                num_2 = num_1;
       
        }
    }

    cout << endl;
        
    if ( num_2 == vex_num ) 
        cout << "此图是连通图" << endl;
    else 
        cout << "此图不是连通图" << endl;

}

void GraphMat::DFSFunction ( int i )
{
    is_trav[i] = 1;
    cout << vexs[i] << " ";
    ++num_1;

    for ( int j = 0; j < vex_num; ++j ) 
        if ( arcs[i][j] != 0 && !is_trav[j] ) 
            DFSFunction(j);

}

void GraphMat::DFSTraverse_norecursive () 
{
    stack <int> s;
    
    //将标记清0   bool类型,true为1，false为0
    for ( int i = 0; i < vex_num; ++i )
        is_trav[i] = 0;

    for ( int i = 0; i < vex_num; ++i ) {
        if ( !is_trav[i] ) {
    
            s.push(vexs[i]);
            is_trav[i] = 1;

            while ( !s.empty() ) {
                int value = s.top();
                cout << value << " ";
                s.pop();
                for ( int j = 0; j < vex_num; ++j ) {
                    if ( arcs[value-1][j] != 0 && !is_trav[j] ) {
                        s.push(vexs[j]);
                        is_trav[j] = 1;
                    }
                }
            }
        }
    }

    cout << endl;

}

void GraphMat::BFSTraverse_queue () 
{
    queue <int> q;
    
    //将标记清0   bool类型,true为1，false为0
    for ( int i = 0; i < vex_num; ++i )
        is_trav[i] = 0;

    for ( int i = 0; i < vex_num; ++i ) {
        if ( !is_trav[i] ) {
    
            q.push(vexs[i]);
            is_trav[i] = 1;

            while ( !q.empty() ) {
                int value = q.front();
                cout << value << " ";
                q.pop();
                for ( int j = 0; j < vex_num; ++j ) {
                    if ( arcs[value-1][j] != 0 && !is_trav[j] ) {
                        q.push(vexs[j]);
                        is_trav[j] = 1;
                    }
                }
            }
        }
    }

    cout << endl;

}


int main ()
{
    GraphMat graph(UDG);
    graph.CreateGraph();

    cout << "广度遍历:" << endl;
    graph.BFSTraverse_queue();
    cout << "深度遍历非递归:" <<endl;
    graph.DFSTraverse_norecursive();
    cout << "深度遍历:" << endl;
    graph.DFSTraverse();
    cout << "连通分量的个数为:" << sum << endl;

    return 0;
}
