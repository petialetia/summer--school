#include <stdio.h>
#include <stdlib.h>

const int N = 10;

int* merge(int* arr1, int* arr2, int size1, int size2);

int* mergeSort(int* array, int size)
{
    if (size == 1) return array;
    int* A = mergeSort(array, size/2);
    int* B = mergeSort(array + size - size/2, size - size/2);

    return merge(A, B, size/2, size - size/2);
}

int* merge(int* arr1, int* arr2, int size1, int size2)
{
    int i = 0;
    int j = 0;
    int* arr3 = (int*)calloc(size1 + size2, sizeof(int));

    while(i < size1 && j < size2)
    {
        if (arr1[i] <= arr2[j])
        {
            arr3[i + j] = arr1[i++];
        }
        else
        {
            arr3[i + j] = arr2[j++];
        }

    }

    while(i < size1)
    {
        arr3[i + j] = arr1[i++];
    }
    while(j < size2)
    {
        arr3[i + j] = arr2[j++];
    }
    return arr3;

}


int main()
{
    int array[N] = {1, 25, 5, 3, 9, 3, 1, 7, 5, 2};

    int* newarray = mergeSort(array, N);
    for (int i = 0; i < N; ++i)
    {
        printf("%d  ", newarray[i]);
    }

    return 0;
}
