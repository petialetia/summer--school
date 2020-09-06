#include <stdlib.h>
#include <stdio.h>
#inclide <stdint.h>

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
while ((c = start[z++]) != EOF)
    if (c == '\n')
        {
        A[i][j] = '\0';
        i = 0;
        j++;
        }
    else 
        A[i++][j] = c;
}


int main()
{
    FILE* in = fopen("input.txt","r");
    char* start = read_file(in);

    char A[N][N] = {0};

    //read_in_2D(start, A);
    free(start);

    return 0;
}
