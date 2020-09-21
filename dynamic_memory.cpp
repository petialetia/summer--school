#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define ok   printf("Test in line %d OK\n",                                           __LINE__)
#define fail printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__)

struct str
{
    const char* str_ = nullptr;
    int         len_ =       0;
};

//-----------------------------------------------
//!  calculates file length
//!
//!  @param [in]   in  file
//!
//!  @return lenght of file
//-----------------------------------------------
uint64_t len_of_file(FILE* in)
{
    assert(in != nullptr);

    fseek(in, 0, SEEK_END);
    uint64_t pos = ftell(in);
    fseek(in, 0, SEEK_SET);

    return pos;
}

//-----------------------------------------------
//!  checking if the letter
//!
//!  @param [in] letter  letter
//!
//!  @return 1 if letter is     a letter
//!  @return 0 if letter is not a letter
//-----------------------------------------------
int isletter(char letter)
{
    if (((letter >= 'А') && ('п' >= letter)) || ((letter >= 'A') && ('z' >= letter)) || (('р' >= letter) && ('я' <= letter))) return 1;
    else return 0;
}

//-----------------------------------------------
//!  calculating number of lines
//!
//!  @param [in] start        pointer on start of text
//!  @param [in] num_symbols  number of symbols in the text
//!
//!  @return number of lines
//-----------------------------------------------
int num_lines(char* start, uint64_t num_symbols)
{
    assert(start != nullptr);

    int j = 1;
    for (uint64_t i = 0; i < num_symbols; ++i)
        if (start[i] == '\n') j++;
    return j;
}

//-----------------------------------------------
//!  calculating number of lines
//!
//!  @param [in] in           file read from
//!  @param [in] num_symbols  number of symbols in the text
//!  @param [in] start        pointer on start of text
//!
//!  @note if you have windows, function will clear text from '\r'
//-----------------------------------------------
int read_file(FILE* in, uint64_t num_symbols, char* start)
{
    assert(in != nullptr);

    int real_num_symbols = fread(start, sizeof(char), num_symbols, in);
    #if _WIN32
        start[real_num_symbols + 1] = '\0';
    #endif
    return real_num_symbols;
}

//-----------------------------------------------
//!  making lines from the text
//!
//!  @param [in] lines        pointer to struct where kept string and lenght
//!  @param [in] num_symbols  number of symbols in the text
//!  @param [in] start        pointer on start of text
//!
//!  @note also calculates lenght of each string
//-----------------------------------------------
void make_lines(char* start, str* lines, uint64_t num_symbols)
{
    assert(start != nullptr);
    assert(lines != nullptr);

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

//-----------------------------------------------
//!  printing lines
//!
//!  @param [in] lines  pointer to struct where kept string and lenght
//!  @param [in] num    number of strings in the text
//!  @param [in] out    file where we printing
//!
//-----------------------------------------------
void print_lines(struct str* lines, int num, FILE* const out)
{
    assert(lines != nullptr);
    assert(out   != nullptr);

    for (int j = 0; j < num; j++)
        fprintf(out, "%s\n", lines[j].str_);
}


//-----------------------------------------------
//!  comparator for qsort to compare strings with begin
//!
//!  @param [in] arg1 first  string
//!  @param [in] arg2 second string
//!
//!  @return 1 if arg1 >  arg2
//!  @return -1 if arg2 <= arg2
//-----------------------------------------------

int str_cmp_with_begin(const void* arg1, const void* arg2)
{
    int i = 0,
        j = 0;

    assert(arg1 != nullptr);
    assert(arg2 != nullptr);

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

//-----------------------------------------------
//!  comparator for qsort to compare strings with end
//!
//!  @param [in] arg1 first  string
//!  @param [in] arg2 second string
//!
//!  @return 1 if arg1 >  arg2
//!  @return -1 if arg2 <= arg2
//-----------------------------------------------

int str_cmp_with_end(const void* arg1, const void* arg2)
{
    int i = (*(str*)arg1).len_,
        j = (*(str*)arg2).len_;

    assert(arg1 != nullptr);
    assert(arg2 != nullptr);

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

void free_all(char** start, str** lines)
{
    assert((start) && (*start));
    assert((lines) && (*lines));

    free(*start);
        *start = nullptr;
    free(*lines);
        *lines = nullptr;
}

void Test_all();
void Test_isletter();
void Test_str_cmp_with_begin();
void Test_str_cmp_with_end();
void Test_len_of_file();
void Test_num_lines();


int main()
{
    //Test_all();
    //return 0;

    FILE* const in  = fopen("input.txt",  "r");
    FILE* const out = fopen("output.txt", "w");

    uint64_t num_symbols = len_of_file(in);

    char* start  = (char*)calloc(num_symbols + 1, sizeof(char));
    num_symbols = read_file(in, num_symbols, start);
    int num_str = num_lines(start, num_symbols);

    struct str* lines = (str*)calloc(num_str + 1, sizeof(str));

    make_lines(start, lines, num_symbols);

    qsort(lines, num_str, sizeof(str), str_cmp_with_begin);

    print_lines(lines, num_str, out);

    fclose(in );
    fclose(out);

    free_all(&start, &lines);

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

    if (isletter('a') == 1) ok;
    else fail;

    if (isletter('г') == 1) ok;
    else fail;

    if (isletter('G') == 1) ok;
    else fail;

    if (isletter('Ы') == 1) ok;
    else fail;

    if (isletter('?') == 0) ok;
    else fail;

    if (isletter('6') == 0) ok;
    else fail;

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

    if (str_cmp_with_begin(&test1, &test2) < 0) ok;
    else fail;

    test1.str_ = "().aabcdefg";
    test1.len_ =            11;
    test2.str_ = "abcdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_begin(&test1, &test2) < 0) ok;
    else fail;

    test1.str_ =    "zzbcdefg";
    test1.len_ =             8;
    test2.str_ = "!_cdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_begin(&test1, &test2) > 0) ok;
    else fail;
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

    if (str_cmp_with_end(&test1, &test2) < 0) ok;
    else fail;

    test1.str_ = "().aabcdefg";
    test1.len_ =            11;
    test2.str_ = "absfvcfew..";
    test2.len_ =            11;

    if (str_cmp_with_end(&test1, &test2) < 0) ok;
    else fail;

    test1.str_ =    "zzbcdefg";
    test1.len_ =             8;
    test2.str_ = "!_cdsfvcaa(";
    test2.len_ =            11;

    if (str_cmp_with_end(&test1, &test2) > 0) ok;
    else fail;
}

void Test_len_of_file()
{
    printf("\nTest \"len_of_file\"\n");
    FILE* test = fopen("test.txt", "w");
    fprintf(test, "%s\n", "ewfwecvwev vdf vdf vdf\nsdvsd dsv");
    fclose(test);
    FILE* test_ = fopen("test.txt", "r");

    if (len_of_file(test_) == 35) ok;
    else fail;

}

void Test_num_lines()
{
    printf("\nTest \"num_lines\"\n");
    char* str = "avada\n kedavra\n";

    if (num_lines(str, 17) == 3) ok;
    else fail;
}




