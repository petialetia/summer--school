#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int N = 1000;

int partition(int* begin, int size);

void swap(void* pointer1, void* pointer2, int size)
{
    char* tmp = (char*)calloc(size, sizeof(char));
    for(int i = 0; i < size; ++i)
    {
        tmp[i] = ((char*)pointer1)[i];
        ((char*)pointer1)[i] = ((char*)pointer2)[i];
        ((char*)pointer2)[i] = tmp[i];
    }
}


void quickSort(int* start, int size)
{
    assert(start != 0);
    //assert(size != 0);

    if (size <= 1)
    {
        return;
    }
    if (size == 2)
    {
        if (start[0] <= start[1])
        {
            return;
        }
        else
        {
            swap(start, start + 1, sizeof(int));
            return;
        }
    }
    int pos = partition(start, size);

    quickSort(start, pos);
    quickSort(start + pos + 1, size - pos - 1);
}

int partition(int* begin, int size)
{
    assert(begin != 0);
    int i = 1;

    for(int j = 1; j < size; ++j)
    {
        if (begin[j] < begin[0])
        {
            swap(begin + j, begin + i, sizeof(int));
            ++i;
        }
    }
    swap(begin, begin + i - 1, sizeof(int));
    return i - 1;
}

int int_cmp(void* arg1, void* arg2)
{
    return (int*)arg1 - (int*)arg2;
}


int main()
{
    int array[N] = {0};

    for (int i = 0; i < N; ++i)
    {
        array[i] = rand()%213;
    }
    quickSort(array, N);
    for (int i = 0; i < N; ++i)
    {
        printf("%d  ", array[i]);
    }


    return 0;
}
