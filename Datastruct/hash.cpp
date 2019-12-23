#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

const int N=30;
const int M=50;

struct name///名字结构体
{
    char s[30];
    int v;///ascll码值之和
} NAME[N];

struct hashs///哈希表结构体
{
    char name[30];///名字
    int key;///关键字
    int sum;///哈希表中含有的元素个数
} HASH[M];

void init()///初始化
{
    int i,j,sum;
    for(i=0; i<N; i++)
    {
        NAME[i].v=0;
    }
    strcpy(NAME[0].s,"jingqi");
    strcpy(NAME[1].s,"quanshijia");
    strcpy(NAME[2].s,"chengjinghua");
    strcpy(NAME[3].s,"dinglei");
    strcpy(NAME[4].s,"zaozige");
    strcpy(NAME[5].s,"fuzongkai");
    strcpy(NAME[6].s,"hujingbin");
    strcpy(NAME[7].s,"huangjianwu");
    strcpy(NAME[8].s,"lailaifa");
    strcpy(NAME[9].s,"lijiahao");
    strcpy(NAME[10].s,"liangxiaocong");
    strcpy(NAME[11].s,"linchunhua");
    strcpy(NAME[12].s,"liujianhui");
    strcpy(NAME[13].s,"luzhijian");
    strcpy(NAME[14].s,"luonan");
    strcpy(NAME[15].s,"quegaoxiang");
    strcpy(NAME[16].s,"sugan");
    strcpy(NAME[17].s,"suzhiqiang");
    strcpy(NAME[18].s,"taojiayang");
    strcpy(NAME[19].s,"wujiawen");
    strcpy(NAME[20].s,"xiaozhuomin");
    strcpy(NAME[21].s,"xujinfeng"); 
    strcpy(NAME[22].s,"yanghaichun");
    strcpy(NAME[23].s,"yeweixiong");
    strcpy(NAME[24].s,"zengwei");
    strcpy(NAME[25].s,"zhengyongbin");
    strcpy(NAME[26].s,"zhongminghua");
    strcpy(NAME[27].s,"chenliyan");
    strcpy(NAME[28].s,"liuxiaohui");
    strcpy(NAME[29].s,"panjinmei");
    for(i=0; i<N; i++)
    {
        sum=0;
        for(j=0; j<strlen(NAME[i].s); j++)
        {
            sum=sum+(NAME[i].s[j]-'a');
        }
        NAME[i].v=sum;///名字字母ascll码之和
    }
}
void creathash()///构造哈希表
{
    int i;
    int n,m,counts;
    for(i=0; i<M; i++)
    {
        strcpy(HASH[i].name,"0");
        HASH[i].key=0;
        HASH[i].sum=0;
    }
    for(i=0; i<N; i++)
    {
        counts=1;
        n=(NAME[i].v)%47;
        m=n;
        if(HASH[n].sum==0)///不冲突
        {
            strcpy(HASH[n].name,NAME[i].s);
            HASH[n].key=NAME[i].v;
            HASH[n].sum=1;
        }
        else///如果发生了冲突
        {
            while(1)
            {
                m=(m+(NAME[i].v%10)+1)%47;
                counts++;
                if(HASH[m].key==0)
                {
                    break;
                }
            }
            strcpy(HASH[m].name,NAME[i].s);
            HASH[m].key=NAME[i].v;
            HASH[m].sum=counts;
        }
    }
    return ;
}
void searchhash()
{
    char name[30];
    int i,sum,n,m,counts;
    sum=0;
    counts=1;
    printf("请输入要查找人的姓名拼音：\n");
    scanf("%s",&name);
    for(i=0; i<strlen(name); i++)
    {
        sum+=(name[i]-'a');
    }
    n=sum%47;
    m=n;
    if(strcmp(HASH[n].name,name)==0)
    {
        printf("姓名:%s 关键字:%d 查找长度:1\n",HASH[n].name,sum);
    }
    else if(HASH[n].sum==0)
    {
        printf("没有找到这条记录！！！\n");
    }
    else
    {
        while(1)
        {
            m=(m+(sum%10)+1)%47;///哈希函数
            counts++;
            if(strcmp(HASH[m].name,name)==0)
            {
                printf("姓名:%s 关键字:%d 查找长度:%d\n",HASH[m].name,sum,counts);
                break;
            }
            if(HASH[m].key==0)
            {
                printf("没有找到这条记录！！！\n");
                break;
            }
        }
    }
}
void displayhash()///演示哈希表
{
    int i,sum;
    float ave;
    sum=0;
    printf("\n地址\t关键字\t搜索长度\t姓名\n");
    for(i=0; i<M; i++)
    {
        printf("%d",i);
        printf("\t%d",HASH[i].key);
        printf("\t%d",HASH[i].sum);
        printf("\t\t%s",HASH[i].name);
        printf("\n");
    }
    for(i=0; i<M; i++)
    {
        sum+=HASH[i].sum;
    }
    ave=((sum)*1.0)/N;
    printf("\n");
    printf("平均查找长度ASL(%d)=%.3lf\n",N,ave);
    return ;
}
void display()
{
    int i;
    for(i=0; i<30; i++)
    {
        printf("\n\t关键字\t\t姓名\n");
        printf("\t%d",NAME[i].v);
        printf("\t%s",NAME[i].s);
    }
    return ;
}
int menu()
{
    printf("\n\n");
    printf("                *****汉字姓名拼音哈希表展示查找系统*****\n");
    printf("                ***1.展示姓名拼音和关键字            ***\n");
    printf("                ***2.展示哈希表                      ***\n");
    printf("                ***3.查找关键字                      ***\n");
    printf("                ***4.退出                            ***\n");
    printf("                ****************************************\n");
    printf("\n");
    return 0;
}
int main()
{
    int n;
    int flag;
    flag=1;
    while(1)
    {
        menu();

        if(flag==1)
        {
            init();
            creathash();
            flag=0;
        }
        scanf("%d",&n);
        getchar();
        if(n<1||n>4)
        {
            printf("输入有误，请重新输入！！！\n");
            continue;
        }
        else
        {
            if(n==1)
            {
                printf("展示所准备的姓名拼音及其所组成的关键字：\n");
                display();
            }
            else if(n==2)
            {
                displayhash();
            }
            else if(n==3)
            {
                searchhash();
            }
            else if(n==4)
            {
                return 0;
            }
        }

    }
    return 0;
}
