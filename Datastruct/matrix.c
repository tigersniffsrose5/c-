#include<stdio.h>
#define MAXSIZE 20
typedef struct{
	int i,j;
	int e;
}Triple;
typedef struct{
	int mu,nu,tu;
	Triple data[MAXSIZE];
}RLSMatrix;
void Input(RLSMatrix *M)
{                                           //三元组输入函数
	printf("*********************\n");
	printf("请输入矩阵的行数:");
	scanf("%d",&M->mu);
	printf("请输入矩阵列数:");
	scanf("%d",&M->nu);
	printf("请以行为主序，以三元组方式输入矩阵元素，'0 0 0'结束输入:\n");
	for(M->tu=0;;M->tu++){
		printf("%d : ",M->tu+1);
		scanf("%d %d %d",&M->data[M->tu].i,&M->data[M->tu].j,&M->data[M->tu].e);
		if((M->data[M->tu].i==0)&&(M->data[M->tu].j==0)&&(M->data[M->tu].e==0))break;
	}//for
}
void Transfer()
{//矩阵转置运算
	int row,line,col,p,q,k,h;
	RLSMatrix N,T;
	printf("矩阵的转置:\n");
	Input(&N);
	printf("转置后的矩阵为:\n");
	T.mu=N.nu;T.nu=N.mu;T.tu=N.tu;
	if(T.tu){
		q=0;
		for(col=1;col<=N.nu;++col)
			for(p=0;p<=N.tu;++p)
				if(N.data[p].j==col){
					T.data[q].i=N.data[p].j;T.data[q].j=N.data[p].i;
					T.data[q].e=N.data[p].e;++q;
				}//if
	}//for
    for(row=1;row<=T.mu;row++){
		for(line=1;line<=T.nu;line++){
			for(k=0,h=0;k<T.tu;k++){
				if((T.data[k].i==row)&&(T.data[k].j==line)){
					printf("%d ",T.data[k].e);h++;break;}
			}//for
			if(h==0)printf("0 ");
		}//for
		printf("\n");
	}//for
}//Transfer
void Count(int i)
{//矩阵加法和减法的函数
	int row,line,p,q,k,h;
	RLSMatrix M1,M2;
	if(i==2)printf("矩阵的加法:\n");
	else printf("矩阵的减法:\n");
	printf("=================\n");
	printf("请输入第一个矩阵:\n");
	Input(&M1);
	printf("请输入第二个矩阵:\n");
	Input(&M2);
	if(i==2)printf("矩阵加法的结果为:\n");
	else printf("矩阵减法的结果为:\n");
	if(M1.nu!=M2.nu||M1.mu!=M2.mu){printf("ERROR!\n");return;}
	else{
		for(row=1;row<=M1.mu;row++){
			for(line=1;line<=M1.nu;line++){
			    for(k=0,h=0;k<M1.tu;k++){
				    if((M1.data[k].i==row)&&(M1.data[k].j==line)){
				    p=M1.data[k].e;h++;break;}
				}//for
			    if(h==0)p=0;
                for(k=0,h=0;k<M2.tu;k++){
				    if((M2.data[k].i==row)&&(M2.data[k].j==line)){
					    q=M2.data[k].e;h++;break;}
				}//for
				if(h==0)q=0;
				if(i==2)printf("%d ",p+q);
				else printf("%d ",p-q);
			}//for
		printf("\n");
		}//for
	} //else
}//Add
int Find(RLSMatrix M,int i,int j)
{                               //在三元组中找到指定位置上的元素来做运算
	int t;
	for(t=0;t<M.tu;t++){
		if((M.data[t].i==i)&&(M.data[t].j==j))return M.data[t].e;
	}//for
	return 0;
}//Find
void Multiplication()
{
	int row,line,p,q,k,L;
	RLSMatrix M1,M2;
	printf("矩阵乘法:\n");
	printf("======================\n");
	printf("请输入第一个矩阵:\n");
	Input(&M1);
    printf("请输入第二个矩阵:\n");
	Input(&M2);
	printf("矩阵乘法的结果为:\n");
	if(M1.nu!=M2.mu){printf("ERROR!\n");return;}
	else{
		for(row=1;row<=M1.mu;row++){
			for(line=1;line<=M2.nu;line++){
				L=0;
			    for(k=1;k<=M1.nu;k++){
					p=Find(M1,row,k);
					q=Find(M2,k,line);
					L=L+p*q;
				}//for
				printf("%d ",L);
			}//for
		 printf("\n");
		}//for
	}//else
}
int main()
{
    int i;
    do {
        printf("***********************************\n");
        printf("*              菜单                *\n");
        printf("            1-矩阵转置\n");
        printf("            2-矩阵加法\n");
        printf("            3-矩阵减法\n");
        printf("            4-矩阵乘法\n");
        printf("            0-退出\n");
        printf("***********************************\n");
        printf("请输入选项0,1,2,3,4:");
        scanf("%d",&i);
        switch(i){
        case 1:Transfer();break;
        case 2:Count(i);break;
        case 3:Count(i);break;
        case 4:Multiplication();break;
        }
    }while ( i != 0 );

	return 0;
}//main

