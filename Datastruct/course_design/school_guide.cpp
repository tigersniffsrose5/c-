#include <bits/stdc++.h>
#include <mysql/mysql.h>
#pragma comment(lib, "libmysql.lib") 

using namespace std;

//定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))  
//清除屏幕 
#define CLEAR() printf("\033[2J") 
//图的最大顶点数
#define MAX_VERTEX_NUM  88 

typedef struct {
    int number;
    string place_name;
    int line;
    int row;
    string place_message;
}place_info; 

MYSQL mysql;
place_info num[MAX_VERTEX_NUM];

class GraphMat
{

public:

    GraphMat();
    void CreateGraph();                                 //构造一个图
    void print();                                       //打印地点名称
    void BFSTraverse();                                 //广度优先遍历
    void BFSTraverse_queue();
    void DFSTraverse();                                 //深度优先遍历
    void DFSTraverse_norecursive();                     //深搜非递归

private:

    int vex_num;                                        //图的顶点个数
    int arc_num;                                        //图的边个数
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];           //邻接矩阵
    place_info vexs[MAX_VERTEX_NUM];                    //顶点集合
    bool is_trav[MAX_VERTEX_NUM];                       //遍历标志，0为未遍历，1为已遍历
    void BFSFunction(int);                              //广度优先
    void DFSFunction(int);                              //深度优先

};

GraphMat::GraphMat(void) 
{
    
    vex_num = 0;
    arc_num = 0;

    //清空矩阵
    for ( int i = 0; i < MAX_VERTEX_NUM; ++i )
        for ( int j = 0; j < MAX_VERTEX_NUM; ++j )
            arcs[i][j] = -1;                           //设置矩阵中各元素的值为-1  
    
    //清空遍历标志
    for ( int i = 0; i < MAX_VERTEX_NUM; ++i )
        is_trav[i] = 0;

}

void GraphMat::CreateGraph()
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i = 1;
    int j = 0;
    int k = 0;
        
    if ( mysql_real_query(&mysql, "select * from place_info", (unsigned long)strlen("select * from place_info")) ) {
        cout << "mysql_real_query select failure!" << endl;
        exit(0);
    }

    res = mysql_store_result(&mysql);
    
    if ( NULL == res ) {
        cout << "mysql_store_result failure!" << endl;
        exit(0);
    }

    while ( (row = mysql_fetch_row(res)) ) {
        vexs[i].number = atoi(row[0]);
        vexs[i].place_name = row[1];
        vexs[i].line = atoi(row[2]);
        vexs[i].row = atoi(row[3]);
        vexs[i++].place_message = row[4];
    }
    mysql_free_result(res);

    if ( mysql_real_query(&mysql, "select * from route_info", (unsigned long)strlen("select * from route_info")) ) {
        cout << "mysql_real_query select failure!" << endl;
        exit(0);
    }

    res = mysql_store_result(&mysql);
    
    if ( NULL == res ) {
        cout << "mysql_store_result failure!" << endl;
        exit(0);
    }
    
    while ( (row = mysql_fetch_row(res)) ) {
        j = atoi(row[0]);
        k = atoi(row[1]);
        arcs[j][k] = atoi(row[2]);
        arcs[k][j] = atoi(row[2]);
    }
    mysql_free_result(res);

}

void mysql_init_t()
{
    if (NULL == mysql_init(&mysql)) {
        cout << "mysql_init():" << mysql_error(&mysql) << endl;
        exit(-1);
    }

    if (!mysql_real_connect(&mysql, "localhost", "root", "qsj122833", "school_guide", 0, NULL, 0)) {
        cout << "mysql_real_connect failure!" << endl;
        exit(-1);
    }

    mysql_set_character_set(&mysql, "utf8");

}

void show()
{

    cout << "\n\n";
    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*----------------------------------------------*|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*     欢迎来到西安邮电大学长安校区！我是世界上 *|\n";
    cout << "\t\t\t\t|* 最机智的导航小you~什么？旭日苑在哪？不知道怎 *|\n";
    cout << "\t\t\t\t|* 么走？最近的路线是啥呀？哈哈~~这些问题都难不 *|\n";
    cout << "\t\t\t\t|* 倒我哦！在这里你可以查看校园平面图，为你展示 *|\n";
    cout << "\t\t\t\t|* 校园地点的总体分布，还可以查询某个地点的相关 *|\n";
    cout << "\t\t\t\t|* 信息，以及两地点间的最短路径、最优路径、最佳 *|\n";
    cout << "\t\t\t\t|* 布网方案，只要你有问题，我都可以即时为你解答 *|\n";
    cout << "\t\t\t\t|* 呢~~有木有崇拜我的感觉>o< 作为管理员，你还可 *|\n";
    cout << "\t\t\t\t|* 以指挥我，比如添加或撤销地点啊、添加路线啊等 *|\n";
    cout << "\t\t\t\t|* 等操作，也可以来注册新的管理员帐号，是不是很 *|\n";
    cout << "\t\t\t\t|* 腻害！！我是小you，我为西邮代言QWQ           *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*==============================================*|\n";
    cout << "\n\n";
    cout << "\n\t\t\t\t\t\t按任意键返回...";
    getchar();
}

int main ()
{
    show();
    return 0;
}
