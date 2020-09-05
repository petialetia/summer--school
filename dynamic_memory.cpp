#include <stdlib.h>
#include <stdio.h>

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
    char* start = calloc(len, sizeof(char))
    fread(start, sizeof(char), len, in);
    return start;
}

int main()
{
    FILE* in = fopen("input.txt","w");
    char* start = read_file(in);


    return 0;
}
