#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
//#include "TxLib.h"

struct str
{
    char* str_ = nullptr;
    int   len_ =       0;
};


uint64_t len_of_file(FILE* in)
{
    assert(in != NULL);

    fseek(in, 0, SEEK_END);
    uint64_t pos = ftell(in);
    fseek(in, 0, SEEK_SET);

    return pos;
}


int isletter(char letter)
{
    if (((letter >= 'А') && ('п' >= letter)) || ((letter >= 'A') && ('z' >= letter)) || (('р' >= letter) && ('я' <= letter))) return 1;
    return 0;
}


int num_lines(char* start, uint64_t num_symbols)
{
    assert(start != NULL);
    int j = 1;
    for (uint64_t i = 0; i < num_symbols; ++i)
        if (start[i] == '\n') j++;
    return j;
}


void read_file(FILE* in, uint64_t num_symbols, char* start)
{
    assert(in != NULL);

    fread(start, sizeof(char), num_symbols, in);
    #if _WIN32
    for (int i = 0, j = 0; i < num_symbols; ++i)
    {
        if (start[i] != '\r') start[j++] = start[i];
    }
    #endif
}


void make_lines(char* start, str* lines, uint64_t num_symbols)
{
    assert(start != NULL);
    assert(lines != NULL);

    int lastI = 0;
    int j     = 0;

    lines[j++].str_ = start;

    for (uint64_t i = 0; i < num_symbols; ++i)
    {
        if (start[i] == '\n')
        {
            start[i] = '\0';
            lines[j - 1].len_ = i - lastI;
            lastI = i + 1;
            lines[j++].str_ = &start[i+1];
        }
    }
    lines[j - 1].len_ = num_symbols - lastI - 4;
}


void print_lines(struct str* lines, int num, FILE* const out)
{
    assert(lines != NULL);
    assert(out   != NULL);

    for (int j = 0; j < num; j++)
        fprintf(out, "%s\n", lines[j].str_);
}


int str_cmp_with_begin(const void* arg1, const void* arg2)
{
    int i = 0,
        j = 0;

    if ((*(str*)arg1).len_ == 0) return  1;
    if ((*(str*)arg2).len_ == 0) return -1;


    while ((!(isletter((*((str*)arg1)).str_[i]))) && (i < (*(str*)arg1).len_)) i++;
    while ((!(isletter((*((str*)arg2)).str_[j]))) && (j < (*(str*)arg2).len_)) j++;

    while (tolower((*(str*)arg1).str_[i]) == tolower((*(str*)arg2).str_[j]))
    {
        i++;
        j++;
    }
    return (tolower((*(str*)arg1).str_[i]) - tolower((*(str*)arg2).str_[j]));
}


int str_cmp_with_end(const void* arg1, const void* arg2)
{
    int i = (*(str*)arg1).len_,
        j = (*(str*)arg2).len_;

    if (i == 0) return  1;
    if (j == 0) return -1;

    while ((!(isletter((*(str*)arg1).str_[i]))) && (i > 0)) i--;
    while ((!(isletter((*(str*)arg2).str_[j]))) && (j > 0)) j--;

    while (tolower((*(str*)arg1).str_[i]) == tolower((*(str*)arg2).str_[j]))
    {
        i--;
        j--;
    }

    return tolower((*(str*)arg1).str_[i]) - tolower((*(str*)arg2).str_[j]);
}


void Test_all();
void Test_isletter();
void Test_str_cmp_with_begin();
void Test_str_cmp_with_end();
void Test_len_of_file();
void Test_num_lines();


int main()
{
    Test_all();
    return 0;

    FILE* const in  = fopen("input.txt",  "r");
    FILE* const out = fopen("output.txt", "w");

    uint64_t num_symbols = len_of_file(in);

    char* start  = (char*)calloc(num_symbols + 1, sizeof(char));
    read_file(in, num_symbols, start);
    int num_str = num_lines(start, num_symbols);

    struct str* lines = (str*)calloc(num_str + 1, sizeof(str));

    make_lines(start, lines, num_symbols);

    qsort(lines, num_str, sizeof(str), str_cmp_with_end);

    print_lines(lines, num_str, out);

    fclose(in );
    fclose(out);

    free(start);
    free(lines);
    return 0;
}
void Test_all()
{
Test_isletter();
Test_str_cmp_with_begin();
Test_str_cmp_with_end();
Test_len_of_file();
Test_num_lines();
}


void Test_isletter()
{
    printf("Test \"isletter\"\n");

    if (isletter('a') == 1) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    if (isletter('г') == 1) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    if (isletter('G') == 1) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    if (isletter('Ы') == 1) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    if (isletter('?') == 0) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    if (isletter('6') == 0) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

}

void Test_str_cmp_with_begin()
{
    printf("\nTest \"str_cmp_with_begin\"\n");
    str test1;
    str test2;


    test1.str_ =    "aabcdefg";
    test1.len_ =             8;
    test2.str_ = "abcdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_begin(&test1, &test2) < 0)    printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    test1.str_ = "().aabcdefg";
    test1.len_ =            11;
    test2.str_ = "abcdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_begin(&test1, &test2) < 0)    printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    test1.str_ =    "zzbcdefg";
    test1.len_ =             8;
    test2.str_ = "!_cdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_begin(&test1, &test2) > 0)    printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);
}

void Test_str_cmp_with_end()
{
    printf("\nTest \"str_cmp_with_end\"\n");
    str test1;
    str test2;


    test1.str_ =    "aabcdefg";
    test1.len_ =             8;
    test2.str_ = "abcdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_end(&test1, &test2) < 0)    printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    test1.str_ = "().aabcdefg";
    test1.len_ =            11;
    test2.str_ = "absfvcfew..";
    test2.len_ =            11;

    if (str_cmp_with_end(&test1, &test2) < 0)    printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

    test1.str_ =    "zzbcdefg";
    test1.len_ =             8;
    test2.str_ = "!_cdsfvcaa(";
    test2.len_ =            11;

    if (str_cmp_with_end(&test1, &test2) > 0)    printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);
}

void Test_len_of_file()
{
    printf("\nTest \"len_of_file\"\n");
    FILE* test = fopen("test.txt", "w");
    fprintf(test, "%s\n", "ewfwecvwev vdf vdf vdf\nsdvsd dsv");
    fclose(test);
    FILE* test_ = fopen("test.txt", "r");

    if (len_of_file(test_) == 35) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);

}

void Test_num_lines()
{
    printf("\nTest \"num_lines\"\n");
    char* str = "avada\n kedavra\n";
    if (num_lines(str, 17) == 3) printf("Test in line %d OK\n", __LINE__);
    else printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__);
}











