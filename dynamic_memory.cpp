#include <stdlib.h>
#include <stdio.h>

const int N = 100;

int len_of_file(FILE* in)
{
    fseek(in, 0, SEEK_END);
    int pos = ftell(in);
    fseek(in, 0, SEEK_SET);
    return pos;
}


char* read_file(FILE* in)
{
    int len = len_of_file(in);
    char* start = (char*)calloc(len, sizeof(char));
    fread(start, sizeof(char), len, in);
    return start;
}


void read_in_2D(char* start, char* A[][N])
{
A[0][0] = start[0];

}


int main()
{
    FILE* in = fopen("input.txt","r");
    char* start = read_file(in);
    char A[N][N] = {0};
    read_in_2D(start, A[][N]);

    printf("%s", A);

    free(start);

    return 0;
}
