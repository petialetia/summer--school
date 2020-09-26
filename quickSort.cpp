#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

const int N = 1000;

int partition(int* begin, int size, int size_elem, int(*cmp)(const void*, const void*));

void swap(void* pointer1, void* pointer2, int size)
{
    char tmp = '\0';
    for(int i = 0; i < size; ++i)
    {
        tmp = ((char*)pointer1)[i];
        ((char*)pointer1)[i] = ((char*)pointer2)[i];
        ((char*)pointer2)[i] = tmp;
    }
}


void quickSort(int* start, int size, int size_elem, int(*cmp)(const void*, const void*))
{
    assert(start != 0);

    if (size <= 1)
    {
        return;
    }
    if (size == 2)
    {
        if (cmp(start, start + 1) <= 0)
        {
            return;
        }
        else
        {
            swap(start, start + 1, size_elem);
            return;
        }
    }
    int pos = partition(start, size, size_elem, cmp);

    quickSort(start, pos, size_elem, cmp);
    quickSort(start + pos + 1, size - pos - 1, size_elem, cmp);
}

int partition(int* begin, int size, int size_elem, int(*cmp)(const void*, const void*))
{
    assert(begin != 0);
    int i = 1;

    for(int j = 1; j < size; ++j)
    {
        if (cmp(begin, begin + j) > 0)     //>=
        {
            swap(begin + j, begin + i, size_elem);
            ++i;
        }
    }
    swap(begin, begin + i - 1, size_elem);
    return i - 1;
}

int int_cmp(const void* arg1, const void* arg2)
{
    return *(const int*)arg1 - *(const int*)arg2;
}


int main()
{
    int array[N] = {0};

    for (int i = 1; i < N; ++i)
    {
        array[i] = rand()%213;
    }
    quickSort(array, N, sizeof(int), int_cmp);
    for (int i = 0; i < N; ++i)
    {
        printf("%d  ", array[i]);
    }

    return 0;
}
