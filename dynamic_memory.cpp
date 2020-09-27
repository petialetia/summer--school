//#include "include.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#define OK   printf("Test in line %d OK\n",                                           __LINE__)
#define FAIL printf("Test in line %d failed!!!!!!!!!!!!!!!!!!DDEEEBBAAAGGGG!!!!!!\n", __LINE__)

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

int num_lines(const char* start, uint64_t num_symbols)
{
    assert(start != nullptr);

    int num = 1;
    for (uint64_t i = 0; i < num_symbols; ++i)
        if (start[i] == '\n') num++;
    return num;
}

//-----------------------------------------------
//!  reading from file to buffer
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

    int lastI    = 0;
    int Num_line = 0;

    lines[Num_line++].str_ = start;

    for (uint64_t i = 0; i < num_symbols; ++i)
    {
        if (start[i] == '\n')
        {
            start[i] = '\0';
            lines[Num_line - 1].len_ = i - lastI;
            lastI = i + 1;
            lines[Num_line++].str_ = &start[i+1];
        }
    }
    lines[Num_line - 1].len_ = num_symbols - lastI;
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
//!  swapping two values
//!
//!  @param [in] pointer1   pointer to first value
//!  @param [in] pointer1   pointer to first value
//!  @param [in] size_elem  size of values
//!
//!  @note 3rd argument usually is sizeof(value)
//-----------------------------------------------

void swap(void* pointer1, void* pointer2, int size_elem)
{
    assert(pointer1 != 0);
    assert(pointer2 != 0);
    char tmp =  '\0';
    for(int i = 0; i < size_elem; ++i)
    {
        tmp = ((char*)pointer1)[i];
        ((char*)pointer1)[i] = ((char*)pointer2)[i];
        ((char*)pointer2)[i] = tmp;
    }
}

//-----------------------------------------------
//!  insertion sorting algorithm
//!
//!  @param [in] begin       pointer to start of array
//!  @param [in] size        number of elements in array
//!  @param [in] size_elem   size of elements
//!  @param [in] cmp         comparator to sort
//!
//-----------------------------------------------

void insertionSort(void* begin, int size, int size_elem, int(*cmp)(const void*, const void*))
{
    assert(begin != 0);

    for(int i = 1; i < size; ++i)
    {
        int j = i - 1;
        while(cmp((char*)begin + (j + 1)*size_elem, (char*)begin + j*size_elem) < 0)
        {
            swap((char*)begin + (j + 1)*size_elem, (char*)begin + j*size_elem, size_elem);
            printf("%p  %p\n", (char*)begin + (j + 1)*size_elem, (char*)begin + j*size_elem);
            j--;

        }
    }
}

//-----------------------------------------------
//!  partition - separation array into two parts(below and more than pivot)
//!
//!  @param [in] begin       pointer to start of array
//!  @param [in] size        number of elements in array
//!  @param [in] size_elem   size of elements
//!  @param [in] cmp         comparator to sort
//!
//!  @return position of pivot
//-----------------------------------------------

int partition(void* begin, int size, int size_elem, int(*cmp)(const void*, const void*))
{
    assert(begin != 0);
    int i = 1;

    for(int j = 1; j < size; ++j)
    {
        if (cmp((char*)begin, (char*)begin + j*size_elem) > 0)
        {
            swap((char*)begin + j*size_elem, (char*)begin + i*size_elem, size_elem);
            ++i;
        }
    }
    swap((char*)begin, (char*)begin + (i - 1)*size_elem, size_elem);
    return i - 1;
}

//-----------------------------------------------
//!  quick sort - recursive sorting algorithm
//!
//!  @param [in] begin       pointer to start of array
//!  @param [in] size        number of elements in array
//!  @param [in] size_elem   size of elements
//!  @param [in] cmp         comparator to sort
//!
//-----------------------------------------------

void quickSort(void* begin, int size, int size_elem, int(*cmp)(const void*, const void*))
{
    assert(begin != 0);

    if (size <= 1)
    {
        return;
    }
    if (size == 2)
    {
        if (cmp((char*)begin, (char*)begin + 1*size_elem) <= 0)
        {
            return;
        }
        else
        {
            swap((char*)begin, (char*)begin + 1*size_elem, size_elem);
            return;
        }
    }
    if (size < 15)
    {
        insertionSort(begin, size, size_elem, cmp);
        return;
    }

    int pos = partition(begin, size, size_elem, cmp);

    quickSort((char*)begin, pos, size_elem, cmp);
    quickSort((char*)begin + (pos + 1)*size_elem, size - pos - 1, size_elem, cmp);
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

    str argg1 = *(str*)arg1;
    str argg2 = *(str*)arg2;

    if (argg1.len_ == 0) return  1;
    if (argg1.len_ == 0) return -1;


    while ((!(isletter(argg1.str_[i]))) && (i < argg1.len_)) i++;
    while ((!(isletter(argg2.str_[j]))) && (j < argg2.len_)) j++;

    while (tolower(argg1.str_[i]) == tolower(argg2.str_[j]))
    {
        i++;
        j++;
    }
    return (tolower(argg1.str_[i]) - tolower(argg2.str_[j]));
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

    str argg1 = *(str*)arg1;
    str argg2 = *(str*)arg2;

    assert(arg1 != nullptr);
    assert(arg2 != nullptr);

    if (i == 0) return  1;
    if (j == 0) return -1;

    while ((!(isletter(argg1.str_[i]))) && (i > 0)) i--;
    while ((!(isletter(argg2.str_[j]))) && (j > 0)) j--;

    while (tolower(argg1.str_[i]) == tolower(argg2.str_[j]))
    {
        i--;
        j--;
    }

    return tolower(argg1.str_[i]) - tolower(argg2.str_[j]);
}

//-----------------------------------------------
//!  sorting array and printing it
//!
//!  @param [in] lines        pointer to array of structs
//!  @param [in] num_str      number of lines in the text
//!  @param [in] out          file to print
//!  @param [in] num_symbols  number of symbols in the text
//!
//-----------------------------------------------

void sort_and_print(str* lines, int num_str, FILE* out, int num_symbols, char* start)
{
    quickSort(lines, num_str, sizeof(str), str_cmp_with_begin);
    print_lines(lines, num_str, out);

    fprintf(out, "\n\n----------------------------------------------------------\n\n");

    quickSort(lines, num_str, sizeof(str), str_cmp_with_end);
    print_lines(lines, num_str, out);

    fprintf(out, "\n\n----------------------------------------------------------\n\n");

    for (int i = 0; i < num_symbols; ++i)
        if (start[i] == '\0')
        {
            putc('\n', out);
            i++;
        }
        else putc(start[i], out);
}

//-----------------------------------------------
//!  free all dynamic memory
//!
//!  @param [in] start   first pointer to free
//!  @param [in] lines   second pointer to free
//!
//-----------------------------------------------

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


int main(int argc, const char* argv[])
{
    //Test_all();
    //return 0;

    FILE* in = (argc - 1 > 0)? fopen(argv[1], "r") : fopen("inputbl.txt",  "r");

    uint64_t num_symbols = len_of_file(in);

    char* start  = (char*)calloc(num_symbols + 1, sizeof(char));
    num_symbols = read_file(in, num_symbols, start);
    int num_str = num_lines(start, num_symbols);

    str* lines = (str*)calloc(num_str + 1, sizeof(str));

    make_lines(start, lines, num_symbols);

	FILE* const out = fopen("output.txt", "w");
    sort_and_print(lines, num_str, out, num_symbols, start);  //менкопи копирует элементы

    fclose(in );
    fclose(out);

    free_all(&start, &lines);

    return 0;
}

void Test_all()
{
Test_isletter          ();
Test_str_cmp_with_begin();
Test_str_cmp_with_end  ();
Test_len_of_file       ();
Test_num_lines         ();
}

void Test_isletter()
{
    printf("Test \"isletter\"\n");

    if (isletter('a') == 1) OK;
    else FAIL;

    if (isletter('г') == 1) OK;
    else FAIL;

    if (isletter('G') == 1) OK;
    else FAIL;

    if (isletter('Ы') == 1) OK;
    else FAIL;

    if (isletter('?') == 0) OK;
    else FAIL;

    if (isletter('6') == 0) OK;
    else FAIL;

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

    if (str_cmp_with_begin(&test1, &test2) < 0) OK;
    else FAIL;

    test1.str_ = "().aabcdefg";
    test1.len_ =            11;
    test2.str_ = "abcdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_begin(&test1, &test2) < 0) OK;
    else FAIL;

    test1.str_ =    "zzbcdefg";
    test1.len_ =             8;
    test2.str_ = "!_cdsfvcfew";
    test2.len_ =            11;

    if (str_cmp_with_begin(&test1, &test2) > 0) OK;
    else FAIL;
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

    if (str_cmp_with_end(&test1, &test2) < 0) OK;
    else FAIL;

    test1.str_ = "().aabcdefg";
    test1.len_ =            11;
    test2.str_ = "absfvcfew..";
    test2.len_ =            11;

    if (str_cmp_with_end(&test1, &test2) < 0) OK;
    else FAIL;

    test1.str_ =    "zzbcdefg";
    test1.len_ =             8;
    test2.str_ = "!_cdsfvcaa(";
    test2.len_ =            11;

    if (str_cmp_with_end(&test1, &test2) > 0) OK;
    else FAIL;
}

void Test_len_of_file()
{
    printf("\nTest \"len_of_file\"\n");
    FILE* test = fopen("test.txt", "w");
    fprintf(test, "%s\n", "ewfwecvwev vdf vdf vdf\nsdvsd dsv");
    fclose(test);
    FILE* test_ = fopen("test.txt", "r");

    if (len_of_file(test_) == 35) OK;
    else FAIL;

}

void Test_num_lines()
{
    printf("\nTest \"num_lines\"\n");
    const char* str = "avada\n kedavra\n";

    if (num_lines(str, 17) == 3) OK;
    else FAIL;
}
