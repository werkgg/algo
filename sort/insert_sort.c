#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void insert_sort(void *base, size_t nmemb, size_t size,
        int (*compar)(const void *, const void *))
{
    if(nmemb < 2) return;
    size_t j;
    long long int i; // Fix me
    void *key = malloc(size);
    for(j=1; j < nmemb; j++)
    {
        memcpy(key, base+j*size, size);
        i = j - 1;
        while(i>=0 && compar(base+i*size,key) > 0)
        {
            memcpy(base+(i+1)*size, base+i*size, size);
            i--;
        }
        memcpy(base+(i+1)*size, key, size);
    }
    free(key);
}
/*
int compar_str(const void *i, const void *j)
{
    printf("zzzz %s\n",*(const char **)i);
    printf("zzzz %s\n",*(const char **)j);
    int r = strcmp(*(const char **)i, *(const char **)j);
    printf("zzzz %d\n", r);
    return r;
}

*/
/*
int main(){
    int i;
    int num = 5;
    char ** strlist = (char **)malloc(num*sizeof(char*));
    int k;
    for(k=0;k<num;k++)strlist[k]=(char *)malloc(16*sizeof(char));
    strcpy(strlist[0],"aaa");
    strcpy(strlist[1],"baa");
    strcpy(strlist[2],"daa");
    strcpy(strlist[3],"gaa");
    strcpy(strlist[4],"caa");
    for(i=0;i<5;i++)
    {
        printf("%s ",strlist[i]);
    }
    printf("\n");
    insert_sort(strlist,5,sizeof(char*),compar_str);
    for(i=0;i<5;i++)
    {
        printf("%s ",strlist[i]);
    }
    return 0;
}
*/
