#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void swap(void* pointer1, void* pointer2, int size);


void insertionSort(void* begin, int size, int size_elem, int(*cmp)(const void*, const void*))
{
    assert(begin != 0);
    for(int i = 1; i < size; ++i)
    {
        int j = i - 1;
        while(j >= 0 && cmp((char*)begin + (j + 1)*size_elem, (char*)begin + j*size_elem) < 0)
        {
            swap((char*)begin + (j + 1)*size_elem, (char*)begin + j*size_elem, size_elem);
            j--;
        }
    }
}

void swap(void* pointer1, void* pointer2, int size)
{
    assert(pointer1 != 0);
    assert(pointer2 != 0);

    char tmp = '\0';
    for(int i = 0; i < size; ++i)
    {
        tmp = ((char*)pointer1)[i];
        ((char*)pointer1)[i] = ((char*)pointer2)[i];
        ((char*)pointer2)[i] = tmp;
    }
}


int partition(void* begin, int size, int size_elem, int(*cmp)(const void*, const void*))
{
    assert(begin != 0);
    int i = 1;

    swap((char*)begin, (char*)begin + (size/2)*size_elem, size_elem);

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


int int_cmp(const void* arg1, const void* arg2)
{
    return *(const int*)arg1 - *(const int*)arg2;
}


int main()
{
    int N = 0;
    scanf("%d", &N);
    int* array = (int*)calloc(N, sizeof(int));

    for (int i = 0; i < N; ++i)
    {
        scanf("%d", array + i);
    }

    quickSort(array, N, sizeof(int), int_cmp);

    for (int i = 0; i < N; ++i)
    {
        printf("%d ", array[i]);
    }

    return 0;
}
