#include <stdlib.h>
#include <stdio.h>

int len_of_file(FILE* in)
{
    fseek(in, 0, SEEK_END);
    int pos = ftell(in);
    fseek(in, 0, SEEK_SET);
    return pos;
}


int* read_file(FILE* in)
{
    int len = len_of_file(in);
    int* start = calloc(len, sizeof(char))
    fread(start, len * sizeof(char), len, in);
    return start;
}

int main()
{
    FILE* in = fopen("input.txt","w");
    int* start = read_file(in);


    return 0;
}
