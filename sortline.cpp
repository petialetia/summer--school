#include <stdio.h>
#include <string.h>
const int N = 100;


void getline(char* s, FILE* in)
{
    int i = 0;
    char c;
    while (((c = getc(in)) != EOF) && c != '\n')
        s[i++] = c;
    s[i] = '\0';
}


void putline(char* s, FILE* out)
{
    int i = 0;
    while (s[i] != '\0')
        putc(s[i++], out);
    putc('\n', out);
}


// AnyOf проверяет встречается ли символ с в строке s
int AnyOf(char c, char* s)
{
    int i = 0;
    while (s[i] != '\0')
        if (c == s[i++])
            return 0;
    return 1;
}


void sortline(char* s1, char* s2)
{
    int i, j;
    for (i = j = 0; s1[i] != '\0'; ++i)
        {
        if (AnyOf(s1[i], s2))
            s1[j++] = s1[i];
        }
        s1[j] = '\0';
}


int main()
{
    char s1[N], s2[N];

    FILE* in  = fopen("input.txt", "r");
    FILE* out = fopen("output.txt","w");


    getline(s1, in );
    getline(s2, in );

    sortline(s1, s2);
    putline(s1, out);

    fclose(in );
    fclose(out);
    return 0;
}
