#include <stdio.h>
#include <iso646.h>

const int N = 100;

void getline(char* s, FILE* fp, int NumS, int* flag);

void putline(char* s, FILE* fa, int NumS, int* flag);

int main()
{
    FILE* fp;
    FILE* fa;
    fp = fopen("test.txt","r");
    fa = fopen("output.txt","w");
    char  s[N][N] = {0},{0};
    int NumS = 0,
        flag = 1;

    while (flag)
        {
        getline(s, fp, NumS, &flag);
        ++NumS;
        }
    flag = 1;
    NumS = 0;

    while (flag)
        {
        putline(s, fa, NumS, &flag);
        ++NumS;
        }
    return 0;
}

void getline(char* s, FILE* fp, int NumS, int* flag)
{

    int  i = 0;
    char c = 0;

    for (i = 0; (((s[i][NumS] = getc(fp)) != EOF) and (s[i] != '\n'));++i)
        if (s[i][NumS] = EOF)
            *flag = 0;
    if (s[i-1][NumS] != EOF)
        s[i][NumS] = '\0';
}

void putline(char* s, FILE* fa, int NumS, int* flag)
{
    int i = 0;
    for (i = 0; ((s[i] != '\0') and (s[i] != '\n'));++i)
        putc(s[i], fa);
}









