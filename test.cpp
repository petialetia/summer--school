#include <stdio.h>
#include <iso646.h>

const int N = 100;

void getline(char s[N], FILE* fp);

void putline(char s[N], FILE* fa);

int main()
{
    FILE* fp;
    FILE* fa;
    fp = fopen("test.txt","r");
    fa = fopen("output.txt","w");

    char s[N] = {0};
    getline(&s[N], fp);
    putline(&s[N], fa);
    return 0;
}

void getline(char s[N], FILE* fp)
{

    int  i = 0;
    char c = 0;

    for (i = 0; (((s[i] = getc(fp)) != EOF) and (s[i] != '\n'));++i){}

    s[i] = '\0';
}

void putline(char s[N], FILE* fa)
{
    int i = 0;
    for (i = 0; (s[i] != '\0');++i)
        putc(s[i], fa);
}









