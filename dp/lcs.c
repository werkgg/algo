#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void lcs_length(char *x, char *y, int m, int n, int **c, char **b);
void print_lcs(char *b, char *x, int m, int n, int i, int j);

int main(int argc, const char *argv[])
{
    if(argc == 1)
    {
        printf("No input file\n");
        return 1;
    }
    FILE *f;
    if((f=fopen(argv[1],"r"))==NULL){
        printf("File %s can't be opened.\n", argv[1]);
        return 1;
    }
    int m,n;
    fscanf(f,"%d%d",&m,&n);
    char x[m],y[n];
    for(int i=0;i<m;i++)
    {
        char temp;
        while((temp=getc(f))==' '|| temp == '\n' || temp == '\r');
        //fscanf(f,"%c",&x[i]);
        x[i] = temp;
        printf("%c ",x[i]);
    }
    printf("\n");
    for(int i=0;i<n;i++)
    {
        char temp;
        while((temp=getc(f))==' '|| temp == '\n' || temp == '\r');
        //fscanf(f,"%c",&y[i]);
        y[i] = temp;
        printf("%c ",y[i]);
    }
    printf("\n");

    size_t nanosec;
    struct timespec time_before, time_after;
    clock_gettime(CLOCK_REALTIME,&time_before);

    int ** c = (int **)malloc(sizeof(int *));
    char ** b = (char **)malloc(sizeof(char *));

    lcs_length(x, y, m, n, c, b);
    print_lcs(*b,x, m, n, m, n);
    printf("\n");

    clock_gettime(CLOCK_REALTIME,&time_after);
    nanosec = time_after.tv_sec*1e9 + time_after.tv_nsec
        - time_before.tv_sec*1e9 - time_before.tv_nsec;
    printf("time spend (nanosec): %ld\n", nanosec);

    /*
    for(int i=1; i<=m; i++)
    {
        for(int j=1; j<=n; j++)
            printf("%c ", (*b)[i*n+j]);
        printf("\n");
    }
    */
    return 0;
}

void lcs_length(char *x, char *y, int m, int n, int **c, char **b)
{
    int * _c = (int *)malloc(sizeof(int)*(m+1)*(n+1));
    char * _b = (char *)malloc(sizeof(char)*(m+1)*(n+1));
    for(int i=1; i<=m; i++) _c[i*n] = 0;
    for(int i=0; i<=n; i++) _c[i] = 0;
    for(int i=0; i<m; i++)
        for(int j=0; j<n; j++)
        {
            if(x[i]==y[j])
            {
                _c[(i+1)*n+(j+1)] = _c[i*n+j] + 1;
                _b[(i+1)*n+(j+1)] = '\\';
            }
            else if(_c[i*n+(j+1)] >= _c[(i+1)*n+j])
            {
                _c[(i+1)*n+(j+1)] = _c[i*n+(j+1)];
                _b[(i+1)*n+(j+1)] = '|';
            }
            else
            {
                _c[(i+1)*n+(j+1)] = _c[(i+1)*n+j];
                _b[(i+1)*n+(j+1)] = '-';
            }
        }
    *c = _c;
    *b = _b;
}

void print_lcs(char *b, char *x, int m, int n, int i, int j)
{
    if(i==0 || j==0) return;
    if(b[i*n+j] == '\\')
    {
        print_lcs(b, x, m, n, i-1, j-1);
        printf("%c ", x[i-1]);
    }
    else if (b[i*n+j]=='|')
    {
        print_lcs(b, x, m, n, i-1, j);
    }
    else
    {
        print_lcs(b, x, m, n, i, j-1);
    }
}
