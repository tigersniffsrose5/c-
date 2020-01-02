#include <bits/stdc++.h>
#include <mysql/mysql.h>
#pragma comment(lib, "libmysql.lib") 

using namespace std;

//定位光标
#define MOVETO(x,y) printf("\033[%d;%dH", (x), (y))  
//清除屏幕 
#define CLEAR() printf("\033[2J") 
//图的最大顶点数
#define MAX_VERTEX_NUM  33 
#define max_dist 999999

typedef struct {
    int number;
    string place_name;
    int line;
    int row;
    string place_message;
}place_info; 

MYSQL mysql;

int get_choice(string choice_t)
{
    int choice = 0;

    for( decltype(choice_t.size()) i = 0; i < choice_t.size(); ++i )
        if( choice_t[i] < '0' || choice_t[i] > '9' )
            return -1;
    
    for( decltype(choice_t.size()) i = 0; i < choice_t.size(); ++i ) {
        
        int t = 1;
        
        for( decltype(choice_t.size()) j = 1; j < choice_t.size() - i; ++j ) {
            t*=10;
        }

        choice += t*(int)(choice_t[i] - 48);
    }

    return choice;
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

class GraphMat
{

public:

    void clean1();                                                  //边初始化为-1
    void clean2();                                                  //边初始化为999999
    void createGraph();                                             //构造一个图
    void display();                                                 //打印地点名称
    void bfs(int start, int end);                                   //广度优先遍历
    void search_less();                                             //中转最少路径
    void dfs(int strat, int end, deque <int> &q);                   //深度优先遍历
    void search_simple();                                           //简单路径
    void search_best();                                             //最优路径
    void dijkstra(int start, vector<int> &dist, vector<int> &pre);
    void getpath(vector <int> &pre, int start, int end);
    void prim(int start);
    void less_tree();
    void add_place();
    void add_route();
    void delete_place();
    void delete_route();

private:

    int vex_num;                                        //图的顶点个数
    int arc_num;                                        //图的边个数
    int vex_max;                                        //最大顶点序号
    int vex_min;                                        //最小顶点序号
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];           //邻接矩阵
    place_info vexs[MAX_VERTEX_NUM];                    //顶点集合
    bool is_trav[MAX_VERTEX_NUM];                       //遍历标志，0为未遍历，1为已遍历

};

void GraphMat::clean1() 
{
    
    vex_num = 0;
    arc_num = 0;

    //清空矩阵
    for ( int i = 1; i <= MAX_VERTEX_NUM; ++i )
        for ( int j = 1; j <= MAX_VERTEX_NUM; ++j )
            arcs[i][j] = -1;                           //设置矩阵中各元素的值为-1  
    
    //清空遍历标志
    for ( int i = 1; i <= MAX_VERTEX_NUM; ++i )
        is_trav[i] = 0;

    memset(vexs, 0, sizeof(place_info)*MAX_VERTEX_NUM);
}

void GraphMat::clean2() 
{
    
    vex_num = 0;
    arc_num = 0;

    //清空矩阵
    for ( int i = 1; i <= MAX_VERTEX_NUM; ++i )
        for ( int j = 1; j < MAX_VERTEX_NUM; ++j )
            arcs[i][j] = 999999;                           //设置矩阵中各元素的值为999999  
    
    //清空遍历标志
    for ( int i = 1; i <= MAX_VERTEX_NUM; ++i )
        is_trav[i] = 0;

    memset(vexs, 0, sizeof(place_info)*MAX_VERTEX_NUM);
}


void GraphMat::createGraph()
{
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    int i = 1;
    int j = 0;
    int k = 0;
    int num;
    vex_max = 0;
    vex_min = 99999;

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
        num = atoi(row[0]);
        vexs[num].number = atoi(row[0]);
        vexs[num].place_name = row[1];
        vexs[num].line = atoi(row[2]);
        vexs[num].row = atoi(row[3]);
        vexs[num].place_message = row[4];
        i++;
        if ( vex_max < atoi(row[0]) )
            vex_max = atoi(row[0]);
        if ( vex_min > atoi(row[0]) )
            vex_min = atoi(row[0]);
    }

    i--;  
    vex_num = i;

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
    
    i = 1;
    while ( (row = mysql_fetch_row(res)) ) {
        j = atoi(row[0]);
        k = atoi(row[1]);
        arcs[j][k] = atoi(row[2]);
        arcs[k][j] = atoi(row[2]);
        i++;
    }

    i--;
    arc_num = i;

    mysql_free_result(res);

}

void GraphMat::display()
{
    string choice_t;
    int choice;
    MYSQL_RES *res;
    MYSQL_ROW row;
 
    while (1) {

        cout << "\t\t\t\t|================================================|\n";
        cout << "\t\t\t\t|*                                              *|\n";
        cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
        cout << "\t\t\t\t|*                                              *|\n";
        cout << "\t\t\t\t|================================================|\n\n\n";

        cout.setf(std::ios::left);  //设置输出左对齐
        cout << "\t\t\t\t";
        for ( int i = 1; i <= vex_max; ++i ) {
            if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
            }
        }
        cout << "\n\n" << endl;

        cout << "\t\t\t\t请输入想要查询的地点（输入0返回菜单）：";
        cin >> choice_t;
        choice = get_choice(choice_t);

        if ( choice == 0 )
            break;

        if ( choice == -1 )
            continue;

        cout << "\t\t\t\t该点信息如下：\n\t\t\t\t\n\t\t\t\t";
        cout << vexs[choice].place_name << ":\n\t\t\t\t" << vexs[choice].place_message << endl;
        cout << "\n\t\t\t\t该点的路线情况如下：\n\t\t\t\t";
        
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
        
            if ( vexs[choice].number == atoi(row[0]) ) 
                cout << row[0] << "   <---->   " << row[1] << ": " << row[2] << "m\n\t\t\t\t";
            else if ( vexs[choice].number == atoi(row[1]) ) 
                cout << row[1] << "   <---->   " << row[0] << ": " << row[2] << "m\n\t\t\t\t";
   
        }

        cout << "\n\t\t\t\t按任意键返回...";
        getchar();
        getchar();

    }

}

void GraphMat::dfs( int start, int end, deque <int> &q )
{
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number == 0 )
            continue;

        int j = vexs[i].number;
        if ( arcs[start][j] != -1 && is_trav[j] == 0 ) {
            
            is_trav[j] = 1;
            
            if ( j == end ) {
                
                cout << "\n\t\t\t\t";
                for ( deque<int>::const_iterator it = q.begin(); it != q.end(); ++it ) {
                    cout << *it << " -----> ";
                }
                cout << j << "\n";

                is_trav[j] = 0;
            }

            else {
                q.push_back(j);
                dfs(j, end, q);
                q.pop_back();
                is_trav[j] = 0;
            }
        }
    }

}

void GraphMat::search_simple()
{
    
    string choice_t1;
    int choice1;
    string choice_t2;
    int choice2;
    deque <int> a;

    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
    cout << "\n\n" << endl;

    cout << "\t\t\t\t请输入起点序号:";
    cin >> choice_t1;
    choice1 = get_choice(choice_t1);
    cout << "\t\t\t\t请输入终点序号:";
    cin >> choice_t2;
    choice2 = get_choice(choice_t2);
    cout << "\n\t\t\t\t两地点间的所有路线情况为:\n\n";

    a.push_back(choice1);
    is_trav[choice1] = 1;
    dfs(choice1, choice2, a);

    cout << "\n\t\t\t\t按任意键返回...";
    getchar();
    getchar();

}

void GraphMat::bfs( int start, int end )
{
    
    queue <int> q;

    memset(is_trav, 0, MAX_VERTEX_NUM);
    
    if ( start == end ) {
        cout << start;
        return ;
    }

    q.push(start);
    is_trav[start] = 1;

    while ( !q.empty() ) {
        
        int value;
        value = q.front();
        q.pop();

        for ( int i = 1; i <= vex_max; ++i ) {
            if ( vexs[i].number == 0 )
                continue;
            int j = vexs[i].number;
            
            if ( arcs[value][j] != -1 && is_trav[j] == 0 ) {
                
                if ( j == end ) {
                    bfs(start, value);
                    cout << " -----> " << j;
                    return ;
                }
                
                q.push(j);
                is_trav[j] = 1;

            }
        }
        
    }
}

void GraphMat::search_less()
{
     
    string choice_t1;
    int choice1;
    string choice_t2;
    int choice2;

    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
 
    cout << "\n\n" << endl;
    
    cout << "\t\t\t\t请输入起点序号:";
    cin >> choice_t1;
    choice1 = get_choice(choice_t1);
    cout << "\t\t\t\t请输入终点序号:";
    cin >> choice_t2;
    choice2 = get_choice(choice_t2);
    cout << "\n\t\t\t\t两地点间的最少中转路线为:\n\n\t\t\t\t";

    bfs(choice1, choice2);

    cout << "\n\t\t\t\t按任意键返回...";
    getchar();
    getchar();

   
}

void GraphMat::dijkstra(int start, vector <int> &dist, vector <int> &pre)
{
    vector <bool> s(vex_num);
    
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number == 0 )
            continue;
        int j = vexs[i].number;
        if ( arcs[start][j] == -1 )
            dist[j] = 999999;
        if (dist[j] < 999999 )
            pre[j] = start;
        else
            pre[j] = 0;
    }

    dist[start] = 0;
    s[start] = true;
    
    for ( int i = 2; i <= vex_num; ++i ) {
        int best = start;
        int temp = 999999;
        for ( int j = 1; j <= vex_max; ++j) {
            if ( vexs[j].number == 0 )
                continue;
            int k = vexs[j].number;
            if ( !s[k] && dist[k] < temp ) {
                temp = dist[k];
                best = k;
            }
        }

        s[best] = true;
        
        for ( int j = 1; j <= vex_max; ++j) {
            if ( vexs[j].number == 0 )
                continue;
            int k = vexs[j].number;
            if ( !s[k] && arcs[best][k] != -1 ) {
                int newdist = dist[best] + arcs[best][k];
                if ( newdist < dist[k] ) {
                    dist[k] = newdist;
                    pre[k] = best;
                }
            }
        }
    }
}

void GraphMat::getpath(vector <int> &pre, int start, int end)
{
    int temp=end;
    vector<int> t;
    
    while (temp != start)
    {
        t.push_back(temp);
        temp = pre[end];
        end = temp;
    }

    t.push_back(start);
    reverse(t.begin(), t.end());
    
    for ( decltype(t.size()) i = 0; i < t.size(); ++i ) {
        if ( i != t.size()-1 )
            cout << t[i] << " -----> ";
        else
            cout << t[i];
    }
    
    cout << endl;

}

void GraphMat::search_best()
{
    string choice_t1;
    int choice1;
    string choice_t2;
    int choice2;
    vector <int> dist(vex_max), pre(vex_max);

    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
 
    cout << "\n\n" << endl;
    
    cout << "\t\t\t\t请输入起点序号:";
    cin >> choice_t1;
    choice1 = get_choice(choice_t1);
    cout << "\t\t\t\t请输入终点序号:";
    cin >> choice_t2;
    choice2 = get_choice(choice_t2);

    for ( int i = 1; i <= vex_max ; ++i)
        dist[i] = max_dist;
    
    dijkstra(choice1, dist, pre); 
    cout << "\n\t\t\t\t两地点间的最短路程距离为：\n\n\t\t\t\t";
    cout << dist[choice2] - dist[choice1];
    cout << "\n\n\t\t\t\t两地点间的路线为:\n\n\t\t\t\t";
    getpath(pre, choice1, choice2);
    cout << "\n\t\t\t\t按任意键返回...";
    getchar();
    getchar();

}

void GraphMat::prim(int start)
{
    struct {
        int adjvex;
        int lowcost;
    }closedge[MAX_VERTEX_NUM];
    int i, e, m, MIN;

    closedge[start].lowcost = 0;

    if ( vexs[start].number == 0 ) {
        cout << "\t\t\t\t没有这个地点！";
        cout << "\n\n\t\t\t\t按任意键返回...";
        getchar();
        getchar();
        return;
    }

    for ( i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number == 0 )
            continue;
        int j = vexs[i].number;
        if ( j != start ) {
            closedge[j].adjvex = start;
            closedge[j].lowcost = arcs[start][j];
        }
    }

    for ( e = 1; e <= vex_num-1; ++e ) {
        
        MIN = 999999;
        for ( int j = 1; j <= vex_max; ++j ) {
            if ( vexs[j].number == 0 )
                continue;
            int n = vexs[j].number;
            if( closedge[n].lowcost != 0 && closedge[n].lowcost < MIN ) {
                m = n;
                MIN = closedge[m].lowcost;
            }
        }

        if ( closedge[m].lowcost == 0 )
            continue;

        cout << "\t\t\t\t" << vexs[closedge[m].adjvex].number  << " <-----> " << vexs[m].number << ": " << closedge[m].lowcost  << 'm' << endl;
        
        closedge[m].lowcost = 0;

        for( int n = 1; n <= vex_max; ++n ) {
            if ( vexs[n].number == 0 )
                continue;
            int j = vexs[n].number;
            if( j != m && arcs[m][j] < closedge[j].lowcost ) {
                closedge[j].lowcost = arcs[m][j];
                closedge[j].adjvex = m;
            }
        }
    }

    cout << "\n\t\t\t\t按任意键返回...";
    getchar();
    getchar();


}

void GraphMat::less_tree()
{
     
    string start_t;
    int start;
    int cnt = 0;

    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
 
    cout << "\n\n" << endl;
    
    cout << "\t\t\t\t请输入起点序号:";
    cin >> start_t;
    start = get_choice(start_t);

    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number == 0 )
            continue;
        int j = vexs[i].number;
        if ( arcs[start][j] != -1 )
            cnt++;
    }

    if ( cnt == 0 ) {
        cout << "\n\t\t\t\t按任意键返回...";
        getchar();
        getchar();
    }

    else {
        cout << "\n\n";
        prim(start);
    }

}
void GraphMat::add_place()
{
    char place[256];
    int num;
    char message[256];
    int flag;
    MYSQL_RES *res;   
    MYSQL_ROW row;

    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
 
    cout << "\n\n" << endl;
    
    cout << "\t\t\t\t请输入要添加的地点名称:";
    cin >> place;
    cout << "\t\t\t\t请输入要添加的地点介绍:";
    cin >> message;

    flag = 0;
    if (mysql_real_query(&mysql, "select * from place_info", (unsigned long)strlen("select * from place_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(place, row[1]) == 0 ) {
            flag = 1;
            break;
        }
    }
    
    mysql_free_result(res);

    if ( flag == 1 ) {
        cout << "\n\t\t\t\t该地点已经存在！";
        cout << "\n\t\t\t\t添加失败按任意键返回...";
        getchar();
        getchar();
        return ;
    }

    for ( int i = 1; i <= MAX_VERTEX_NUM; ++i ) {
        flag = 0;
        
        for ( int j = 1; j <= vex_num; ++j ) {
            int k = vexs[j].number;
            if ( i == k ) {
                flag = 1;
                break;
            }
        }
        
        if ( flag == 0 ) {
            num = i;
            break;
        }
    
    }

    char n[10];
    stringstream ss;
    ss << num;
    ss >> n;

    char s[256];
    sprintf(s,"insert into place_info values ('%s','%s','1','1','%s')", n, place, message);

    if ( mysql_real_query(&mysql,s,strlen(s)) ) {
        cout << "mysql_real_query insert failure!\n";
        exit(0);
    }
    
    cout << "\n\t\t\t\t添加成功按任意键返回...";
    getchar();
    getchar();


}

void GraphMat::add_route()
{
    char place1[256];
    char place2[256];
    char dstance[10];
    MYSQL_RES *res;   
    MYSQL_ROW row;
    int flag1, flag2;

    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
 
    cout << "\n\n" << endl;
    
    cout << "\t\t\t\t请输入要添加路线的地点序号1:";
    cin >> place1;
    cout << "\t\t\t\t请输入要添加路线的地点序号2:";
    cin >> place2;
    cout << "\t\t\t\t请输入要添加的路线距离:";
    cin >> dstance;

    flag1 = 0;
    flag2 = 0;
    if (mysql_real_query(&mysql, "select * from place_info", (unsigned long)strlen("select * from place_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(place1, row[0]) == 0 ) {
            flag1 = 1;
        }
        else if ( strcmp(place2, row[0]) == 0 ) {
            flag2 = 1;
        }
    }
   
    mysql_free_result(res);

    if ( flag1 == 0 || flag2 == 0 ) {
        cout << "\n\t\t\t\t添加路线的地点不存在";
        cout << "\n\t\t\t\t添加失败按任意键返回...";
        getchar();
        getchar();
        return ;
    }

    flag1 = 0;
    if (mysql_real_query(&mysql, "select * from route_info", (unsigned long)strlen("select * from route_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(place1, row[0]) == 0 && strcmp(place2, row[1]) == 0 ) {
            flag1 = 1;
            break;
        }
        else if ( strcmp(place2, row[0]) == 0 && strcmp(place1, row[1]) == 0 ) {
            flag1 = 1;
            break;
        }
    }
 
    mysql_free_result(res);
    
    if ( flag1 == 1 ) {
        cout << "\n\t\t\t\t该路线已经存在！";
        cout << "\n\t\t\t\t添加失败按任意键返回...";
        getchar();
        getchar();
        return ;
    }


    char s[256];
    sprintf(s,"insert into route_info values ('%s','%s','%s')", place1, place2, dstance);

    if ( mysql_real_query(&mysql,s,strlen(s)) ) {
        cout << "mysql_real_query insert failure!\n";
        exit(0);
    }
    
    cout << "\n\t\t\t\t添加成功按任意键返回...";
    getchar();
    getchar();

}

void GraphMat::delete_place()
{
    char place1[256];
    int flag;
    MYSQL_RES *res;   
    MYSQL_ROW row;


    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
    cout << "\n\n" << endl;
    
    cout << "\t\t\t\t请输入要删除的地点序号:";
    cin >> place1;

    flag = 0;
    if (mysql_real_query(&mysql, "select * from place_info", (unsigned long)strlen("select * from place_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(place1, row[0]) == 0 ) {
            flag = 1;
            break;
        }
    }
    
    mysql_free_result(res);

    if ( flag == 0 ) {
        cout << "\n\t\t\t\t该地点不存在！";
        cout << "\n\t\t\t\t删除失败按任意键返回...";
        getchar();
        getchar();
        return ;
    }


    char s[256];
    sprintf(s,"delete from place_info where number = '%s'", place1);

    if ( mysql_real_query(&mysql,s,strlen(s)) ) {
        cout << "mysql_real_query insert failure!\n";
        exit(0);
    }

//删除次地点的相关路线
//    sprintf(s,"delete from route_info where place_1 = '%s'", place1);
//
//    if ( mysql_real_query(&mysql,s,strlen(s)) ) {
//        cout << "mysql_real_query insert failure!\n";
//        exit(0);
//    }
//
//    sprintf(s,"delete from route_info where place_2 = '%s'", place1);
//
//    if ( mysql_real_query(&mysql,s,strlen(s)) ) {
//        cout << "mysql_real_query insert failure!\n";
//        exit(0);
//    }
//


    cout << "\n\t\t\t\t删除成功按任意键返回...";
    getchar();
    getchar();


}

void GraphMat::delete_route()
{
    char place1[256];
    char place2[256];
    MYSQL_RES *res;   
    MYSQL_ROW row;
    int flag1, flag2;


    cout << "\t\t\t\t|================================================|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|================================================|\n\n\n";

    cout.setf(std::ios::left);  //设置输出左对齐
    cout << "\t\t\t\t";
    for ( int i = 1; i <= vex_max; ++i ) {
        if ( vexs[i].number != 0 ) {
            cout <<  vexs[i].number << '.';
            cout.width(15);
            cout << vexs[i].place_name;
            if ( i%5 == 0 )
                cout << "\n\t\t\t\t";
        }
    }
    cout << "\n\n" << endl;
    
    cout << "\t\t\t\t请输入要删除路线的地点序号1:";
    cin >> place1;
    cout << "\t\t\t\t请输入要删除路线的地点序号2:";
    cin >> place2;

    
    flag1 = 0;
    flag2 = 0;
    if (mysql_real_query(&mysql, "select * from place_info", (unsigned long)strlen("select * from place_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(place1, row[0]) == 0 ) {
            flag1 = 1;
        }
        else if ( strcmp(place2, row[0]) == 0 ) {
            flag2 = 1;
        }
    }
   
    mysql_free_result(res);

    if ( flag1 == 0 || flag2 == 0 ) {
        cout << "\n\t\t\t\t删除路线的地点不存在";
        cout << "\n\t\t\t\t删除失败按任意键返回...";
        getchar();
        getchar();
        return ;
    }

    flag1 = 0;
    if (mysql_real_query(&mysql, "select * from route_info", (unsigned long)strlen("select * from route_info"))) {  
        printf("mysql_real_query select failure!\n"); 
        exit(0);  
    }
    res = mysql_store_result(&mysql);
    if (NULL == res) {  
        printf("mysql_store_result failure!\n");  
        exit(0);  
    }
    while ((row = mysql_fetch_row(res))) {
        if ( strcmp(place1, row[0]) == 0 && strcmp(place2, row[1]) == 0 ) {
            flag1 = 1;
            break;
        }
        else if ( strcmp(place2, row[0]) == 0 && strcmp(place1, row[1]) == 0 ) {
            flag1 = 1;
            break;
        }
    }
 
    mysql_free_result(res);
    
    if ( flag1 == 0 ) {
        cout << "\n\t\t\t\t该路线不存在！";
        cout << "\n\t\t\t\t删除失败按任意键返回...";
        getchar();
        getchar();
        return ;
    }


    char s[256];
    sprintf(s,"delete from route_info where place_1 = '%s' and place_2 = '%s'", place1, place2);
    mysql_real_query(&mysql,s,strlen(s));
    sprintf(s,"delete from route_info where place_2 = '%s' and place_1 = '%s'", place1, place2);
    mysql_real_query(&mysql,s,strlen(s));
    
    cout << "\n\t\t\t\t删除成功按任意键返回...";
    getchar();
    getchar();


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
    cout << "\t\t\t\t|* 呢~~有木有崇拜我的感觉>o< 作为使用者，你还可 *|\n";
    cout << "\t\t\t\t|* 以指挥我，比如添加或撤销地点啊、添加路线啊等 *|\n";
    cout << "\t\t\t\t|* 等操作，也可以来注册新的管理员帐号，是不是很 *|\n";
    cout << "\t\t\t\t|* 腻害！！我是小you，我为西邮代言QWQ           *|\n";
    cout << "\t\t\t\t|*                                              *|\n";
    cout << "\t\t\t\t|*==============================================*|\n";
    cout << "\n\n";
    cout << "\n\t\t\t\t按任意键返回...";
    getchar();
    getchar();

}

void work()
{
       cout << "\n\n";
	   cout << "\t\t\t\t|================================================|\n";
	   cout << "\t\t\t\t|*                                              *|\n";
	   cout << "\t\t\t\t|*    ***欢迎使用西安邮电大学长安校区导航***    *|\n";
	   cout << "\t\t\t\t|*                                              *|\n";
	   cout << "\t\t\t\t|*----------------------------------------------*|\n";
	   cout << "\t\t\t\t|*                                              *|\n";
	   cout << "\t\t\t\t|*               0. 退出                        *|\n";
	   cout << "\t\t\t\t|*               1. 导航使用说明                *|\n";
	   cout << "\t\t\t\t|*               2. 查看地点信息                *|\n";
       cout << "\t\t\t\t|*               3. 查询简单路线                *|\n";
	   cout << "\t\t\t\t|*               4. 查询最短路线                *|\n";
	   cout << "\t\t\t\t|*               5. 查询最优路线                *|\n";
	   cout << "\t\t\t\t|*               6. 最佳布网方案                *|\n";
	   cout << "\t\t\t\t|*               7. 添加新地点                  *|\n";
	   cout << "\t\t\t\t|*               8. 添加新路线                  *|\n";
       cout << "\t\t\t\t|*               9. 撤销旧地点                  *|\n";
	   cout << "\t\t\t\t|*               10.撤销旧路线                  *|\n";
	   cout << "\t\t\t\t|*                                              *|\n";
	   cout << "\t\t\t\t|*==============================================*|\n";
}

int main ()
{
    string choice_t;
    int choice;
    GraphMat map;

    mysql_init_t();

    do {
        work();
        cout << "\n\n\t\t\t\t请输入你的操作：";
        cin >> choice_t;
        choice = get_choice(choice_t);

        switch(choice) {
        case 1:
            show();
            break;
        case 2:
            map.clean1();
            map.createGraph();
            map.display();
            break;
        case 3:
            map.clean1();
            map.createGraph();
            map.search_simple();
            break;
        case 4:
            map.clean1();
            map.createGraph();
            map.search_less();
            break;
        case 5:
            map.clean1();
            map.createGraph();
            map.search_best();
            break;
        case 6:
            map.clean2();
            map.createGraph();
            map.less_tree();
            break;
        case 7:
            map.clean1();
            map.createGraph();
            map.add_place();
            break;
        case 8:
            map.clean1();
            map.createGraph();
            map.add_route();
            break;
        case 9:
            map.clean1();
            map.createGraph();
            map.delete_place();
            break;
        case 10:
            map.clean1();
            map.createGraph();
            map.delete_route();
            break;
        }
    }while (choice != 0);
   
    return 0;
}
