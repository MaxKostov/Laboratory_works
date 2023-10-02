#include <stdio.h>
#include <stdlib.h>

int partition(int arr[], int low, int high);
void swich(int *a, int *b);
void quicksort(int arr[], int low, int high);


int main(void)
{
    int n, m;
    printf("n, m: ");
    scanf("%d %d", &n, &m);
    int matrix[n][m];
    int length = n*m;
    int array[length];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int x = (rand() % 10);
            matrix[i][j] = x;
        }
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
    printf(" \n");

    int num = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            array[num] = matrix[i][j];
            num++;
        }
    }

    quicksort(array, 0, length-1);

    for (int i = 0; i < length; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
    printf(" \n");


    int count = 0;
    int piv = 0;
    int cc = n*m;
    int top = 0;
    int left = 0;
    int bottom = n - 1;
    int right = m - 1;
    while (left <= right && top <= bottom)
    {
        for (int i = left; i <= right; i++)
        {
            matrix[top][i] = array[count];
            count++;
        }
        top++;

        for (int i = top; i <= bottom; i++)
        {
            matrix[i][right] = array[count];
            count++;
        }
        right--;

        for (int i = right; i >= left; i--)
        {
            matrix[bottom][i] = array[count];
            count++;
        }
        bottom--;

        for (int i = bottom; i >= top; i--)
        {
            matrix[i][left] = array[count];
            count++;
        }
        left++;


    }
    

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;

}

void quicksort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quicksort(arr, pi + 1, high);
        quicksort(arr, low, pi - 1);
    }
}

void swich(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b =t;
}

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swich(&arr[j], &arr[i]);
        }
    }
    swich(&arr[i+1], &arr[high]);
    return i+1;
}