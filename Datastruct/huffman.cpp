#include<bits/stdc++.h>

using namespace std;

typedef struct node
{
	int pos = -1;
    bool isVisited = false;//访问位遍历用
	char ch = ' ';
	double weigiht = 0;
	bool Existed = true;//判断是否计算过
	node*LChild = NULL;
	node*RChild = NULL;
	node*Parent = NULL;
}Node;
int str[50][21];
int M,N;
void Traverse(Node*);
void Print(Node*, int);
void Show(string &a);

void Huffman()
{
	int charNum;
	cout << "请输入字符数目：";
	cin >> charNum;
	if (charNum <= 0)
    {
		cout << "输入错误！"<<endl;
		return;
	}
	
    Node *array = new Node[2 * charNum - 1];
	cout << "请输入各个字符和其权重：" << endl;
	
    //输入字符及权值
	for (int i = 0;i < charNum;i++)
	{
		cin >> array[i].ch >> array[i].weigiht;
	}
	
    //合并子节点，生成新节点
	for (int i = 0;i < charNum - 1;i++)
	{
		int minNum_1 , minNum_2 ;
		//给minNum_1赋初值
		for (int j = 0;j <= charNum - 1 + i;j++)
		{
			if (array[j].Existed) { minNum_1 = j;break; }
		}
		//cout << "minNum_1初始值=" << minNum_1 << endl;
		
        //寻找两个权值最小节点
		for (int j = 0;j <=charNum - 1 + i;j++)
		{
			if (array[j].weigiht <= array[minNum_1].weigiht && array[j].Existed){
                if (array[j].weigiht == array[minNum_1].weigiht){
                    if (array[j].ch < array[minNum_1].ch)
                        minNum_1 = j;
                    else
                        continue;
                }
                minNum_1 = j;
		    }
        }
		//给minNum_2赋初值
		for (int j = 0;j <= charNum - 1 + i;j++)
		{
			if (array[j].Existed&&j != minNum_1) { minNum_2 = j;break; }
		}
		//cout << "minNum_2初始值=" << minNum_2 << endl;
		for (int j = 0;j <= charNum - 1 + i;j++)
		{
            if (array[j].weigiht <= array[minNum_2].weigiht && array[j].Existed&&j != minNum_1){
                if (array[j].weigiht == array[minNum_2].weigiht){
                    if (array[j].ch < array[minNum_2].ch)
                        minNum_2 = j;
                    else
                        continue;
                }
                minNum_2 = j;
            };
		}
		
        if (minNum_1 == minNum_2) {
            cout << "minNum_1==minNum_2==" << minNum_1 << endl;
            return;
        }//只剩最后一个节点，即根节点
		
        if (minNum_1 > charNum - 1 + i || minNum_2 > charNum - 1 + i) {
            cout << "越界错误!" << endl;
            return;
        }//数组越界检查
	    
        //合并子节点，生成新节点
        array[charNum + i].weigiht = array[minNum_1].weigiht + array[minNum_2].weigiht;
		array[charNum + i].ch = '#';
		array[minNum_1].Parent = &array[charNum + i];
		array[minNum_2].Parent = &array[charNum + i];
		array[minNum_1].Existed = false;//存在标志置false
		array[minNum_2].Existed = false;
		array[minNum_1].pos = 0;
		array[minNum_2].pos = 1;
	}

	//Traverse(&array[2 * charNum - 2]);
	Print(array, charNum);
}

void Traverse(Node*node)//递归遍历二叉树
{
	cout << node->ch << ":" << node->weigiht << endl;
    node->isVisited = true;
	if (node->LChild != NULL && !node->LChild->isVisited)
        Traverse(node->LChild);
	if (node->RChild != NULL && !node->RChild->isVisited)
        Traverse(node->RChild);
}

void Print(Node*array, int num)//打印字符及哈夫曼编码
{
	stack<int>path;
	for (int i = 0;i < num;i++)
	{
		M = 0;
        Node*p = &array[i];
		while (p->Parent)
		{
			path.push(p->pos);
			p = p->Parent;
		}
		cout << "字符" << array[i].ch << "的哈夫曼编码是：";
        str[N][M++] = (int)array[i].ch;
		while (!path.empty())
		{
			cout << path.top();//取栈顶元素
		    str[N][M++] = path.top();
			path.pop();//删除栈顶元素
        }
        str[N++][M] = -1;
		cout << endl;
	}
}

void Show( string &a ) 
{
    for ( decltype(a.size()) i = 0; i < a.size(); ++i ) {
        for ( int j = 0; j < N-1; ++j ) {
            int m = 1;
            if ( (a[i] - str[j][0] ) == 0 ) {
                while ( str[j][m] != -1 ) {
                    cout << str[j][m++] ;
                }
            }
        }
    }
    cout << endl;
}

int main()
{
	Huffman();
    
    string s;
    cout << "请输入想要编码的字符串：" << endl;
    cin >> s;
    Show(s);

    return 0;
}
 

