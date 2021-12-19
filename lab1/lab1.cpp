#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <stdio.h>

void printArray(int* arr, int sz)
{
    for (int i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    srand(time(NULL));

    int size;
    int* origArray;

    printf("Enter the size of array: \n");
    scanf_s("%2d", &size);

    origArray = (int*)malloc(size * sizeof(int));

    for (int i = 0; i < size; i++)
    {
        origArray[i] = rand() % 100;
    }

    printf("Original array: \n");
    printArray(origArray, size);

    int index = 0;
    int newSize = size - size / 3; //size of final array
    int* tmp;
    
    tmp = (int*)malloc(newSize * sizeof(int));

    // remove elements and shift array to the left;
    for (int i = 0; i < size; i++)
    {
        if (i % 3 != 2)
        {
            tmp[index++] = origArray[i];
        }
    }

    origArray = (int*)realloc(origArray, newSize * sizeof(int));
    origArray = tmp;

    printf("\nNew array: \n");
    printArray(origArray, newSize);

    free(origArray);

    system("pause");

    return 0;
}
