#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

const int N = 100;


int32_t len_of_file(FILE* in)
{
    fseek(in, 0, SEEK_END);
    int32_t pos = ftell(in);
    fseek(in, 0, SEEK_SET);
    return pos;
}


char* read_file(FILE* in)
{
    int32_t len = len_of_file(in);
    char* start = (char*)calloc(len, sizeof(char));
    fread(start, sizeof(char), len, in);
    return start;
}


void read_in_2D(char* start, char A[][N])
{
    int32_t i = 0,
            j = 0,
            z = 0;
    char c = 0;
    while ((c = start[z++]) != EOF)
    {
        if (c == '\n')
            {
            A[i][j] = '\0';
            i = 0;
            j++;
            }
        else
            {
            A[i][j] = c;
            ++i;
            }
    }
}


void print_2D(char A[][N], FILE* out)
{
    int i = 0,
        j = 0;
    while (A[i][j] != EOF)
        if (A[i][j] != '\0')
            putchar(A[i++][j]);
        else
            {
            putchar('\n');
            i = 0;
            ++j;
            }
}

int main()
{
    FILE* in  = fopen("input.txt", "r");
    FILE* out = fopen("output.txt","w");
    char* start = read_file(in);

    char A[N][N] = {0};

    read_in_2D(start, A);
    free(start);

    print_2D(A, out);

    return 0;
}

