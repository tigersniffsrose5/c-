#include <stdio.h>

struct note{
    int x;
    int y;
    int f;
};

int next[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
int a[5][5], b[5][5], c[26][2];

int main()
{
    struct note q[26];
    int head, tail, i, j, k, tx, ty, flag;

    for ( i = 0; i < 5; i++ ) 
        for ( j = 0; j < 5; j++ ) 
            scanf("%d", &a[i][j]);
    
    head = tail = 0;
    q[tail].x = q[tail].y = 0;
    q[tail].f = 0;
    tail++;
    b[0][0] = 1;

    while ( head < tail ) {
        for ( k = 0; k <= 3; k++ ) {
            tx = q[head].x+next[k][0];
            ty = q[head].y+next[k][1];
            if ( tx < 0 || ty < 0 || tx > 4 || ty > 4 )
                continue;
            if ( a[tx][ty] == 0 && b[tx][ty] == 0 ) {
                q[tail].x = tx;
                q[tail].y = ty;
                q[tail].f = head;
                b[tx][ty] = 1;
                tail++;
            }
            if ( tx == 4 && ty == 4 ) {
                flag = 1;
                break;
            }
        }
        
        if  ( flag == 1 )
            break;

        head++;
    }
   
    tail--;
    for ( i = 0; i <= 25; i++ ) {
        if ( tail == 0 )
            break;
        c[i][0] = q[tail].x;
        c[i][1] = q[tail].y;
        tail = q[tail].f;
    }
    c[i][0] = c[i][1] = 0;

    for ( j = i; j >= 0; j-- ) {
        printf("(%d, %d)\n", c[j][0], c[j][1]);
    }

    return 0;
}
  
