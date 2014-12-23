#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

void matrix_chain_order(int *p, int n, float **m, int **s);
void print_optimal_parens(int * s, int n, int i, int j);

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
    int n;
    fscanf(f,"%d",&n);
    int p[n+1];
    for(int i=0;i<=n;i++)
    {
        fscanf(f,"%d",&p[i]);
        printf("%d ",p[i]);
    }
    printf("\n");

    size_t nanosec;
    struct timespec time_before, time_after;
    clock_gettime(CLOCK_REALTIME,&time_before);

    float **m = malloc(sizeof(float *));
    int **s = malloc(sizeof(int *));
    matrix_chain_order(p,n,m,s);
    print_optimal_parens(*s,n,0,n-1);
    printf("\n");
    /*
    n--;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            printf("%d ", (*s)[i*n+j]);
        }
        printf("\n");
    }
    */
    free(*m);
    free(*s);
    free(m);
    free(s);

    clock_gettime(CLOCK_REALTIME,&time_after);
    nanosec = time_after.tv_sec*1e9 + time_after.tv_nsec
        - time_before.tv_sec*1e9 - time_before.tv_nsec;
    printf("time spend (nanosec): %ld\n", nanosec);

    return 0;
}

void matrix_chain_order(int *p, int n, float **m, int **s)
{
    // n should be the number of matrixes
    float * _m = (float *)malloc(sizeof(float)*n*n);
    int * _s = (int *)malloc(sizeof(int)*n*n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            _m[i*n+j]=0;
            _s[i*n+j]=0;
        }
    for(int l=2;l<=n;l++)
    {
        for(int i=0;i<=n-l;i++)
        {
            int j=i+l-1;
            _m[i*n+j]=INFINITY;
            for(int k=i;k<j;k++)
            {
                float q=_m[i*n+k]+_m[(k+1)*n+j]+p[i]*p[k+1]*p[j+1];
                if(q<_m[i*n+j])
                {
                    _m[i*n+j]=q;
                    _s[i*n+j]=k;
                }
            }
        }
    }
    *m = _m;
    *s = _s;
}

void print_optimal_parens(int * s, int n, int i, int j)
{
    if(i==j)
        printf(" A%d ", i+1);
    else
    {
        printf("(");
        print_optimal_parens(s, n, i, s[i*n+j]);
        print_optimal_parens(s, n, s[i*n+j]+1, j);
        printf(")");
    }
}
