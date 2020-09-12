#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

uint64_t len_of_file(FILE* in)
{
    assert(in != NULL);
    fseek(in, 0, SEEK_END);
    uint64_t pos = ftell(in);
    fseek(in, 0, SEEK_SET);
    return pos;
}


int num_lines(char* start)
{
    assert(start != NULL);
    int j = 1;
    for (int i = 0; start[i] != EOF; ++i)
        if (start[i] == '\n') j++;
    return j;
}


char* read_file(FILE* in)
{
    assert(in != NULL);
    uint64_t len = len_of_file(in);
    char* start = (char*)calloc(len + 1, sizeof(char));
    fread(start, sizeof(char), len, in);
    return start;
}


void make_lines(char* start, char** lines)
{
    assert(start != NULL);
    assert(lines != NULL);
    
    int j = 1;
    for (int i = 0; start[i] != EOF; ++i)
    {
        if (start[i] == '\n')
        {
            start[i] = '\0';
            lines[j++] = &start[i+1];
        }
    }
}


void print_lines(const char* const* const lines, int num, FILE* out)
{
    assert(lines != NULL);
    assert(out   != NULL);
    
    for (int j = 0; j < num; j++)
        fprintf(out, "%s\n", lines[j]);
}


int strcmp_void(const void* line1, const void* line2)
{
    assert(line1 != NULL);
    assert(line2 != NULL);
    
    return strcmp(*(const char**)line1, *(const char**)line2);
}


int SortFromEnd_cmp(const void* line1, const void* line2)
{
    assert(line1 != NULL);
    assert(line2 != NULL);
    
    char* oldLine1 = *(char**)line1;
    char* oldLine2 = *(char**)line2;
    int k = strcmp(strrev(*(char**)line1), strrev(*(char**)line2));
    line1 = oldLine1;
    line2 = oldLine2;
    return k;
}


int main()
{
    FILE* in  = fopen("input.txt", "r");
    FILE* out = fopen("output.txt","w");
    char* start = read_file(in);

    int num = num_lines(start);
    char** lines = (char**)calloc(num + 1, sizeof(char**));

    lines[0] = start;
    make_lines(start, lines);

    qsort(lines, num, sizeof(char*), SortFromEnd_cmp);

    print_lines(lines, num, out);

    fclose(in );
    fclose(out);

    free(start);
    free(lines);
    return 0;
}
