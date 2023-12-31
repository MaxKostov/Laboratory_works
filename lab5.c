#include <stdio.h>
#include <stdlib.h>

void selsort2(int **arr, int m, int n);
void piece_of_cake(void);
void piece_of_cake2(int *a, int *b);
void easy1(int *arr, int n);
void easy2(int *arr, int n);
void medium1(int *arr, int n);

int main(void)
{
    int n, m;
    int **matrix = NULL;
    int g = 1;
    while (g == 1)
    {
        int operation;
        printf("1. Dynamic memory allocation for arrays two-dimensional\n");
        printf("2. Entering the elements of the keyboard array\n");
        printf("3. Filling the array with random values\n");
        printf("4. Sorting the elements of the array (according to variants)\n");
        printf("5. Display the board elements to the screen\n");
        printf("6. Release the memory allocated for the array\n");
        printf("0. Exit from the program\n");
        do 
        {
            scanf("%d", &operation);
        }
        while(operation < 0 || operation > 6);
        printf("\n");

        switch (operation)
        {
        case 1:
            printf("n, m: ");
            scanf("%d %d", &n, &m);
            matrix = malloc((n * sizeof(int*)));
            for (int i = 0; i < n; i++)
            {
                *(matrix + i) = malloc(m*sizeof(int));
            }
            break;

        case 3:
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    int x = (rand() % 10);
                    *(*(matrix + i) + j) = x;
                }
            }
            break;
        case 2:
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    int x;
                    scanf("%d", &x);
                    *(*(matrix + i) + j) = x;
                }
            }
            break;
        case 4:
            selsort2(matrix, m, n);
            selsort2(matrix, 1, n);
            break;
        case 5:
            for (int i = 0; i < n; i++)
            {
                for (int j = 0; j < m; j++)
                {
                    printf("%i ", matrix[i][j]);
                }
                printf("\n");
            }
            break;
        case 6:
            for (int i = 0; i < n; i++)
            {
                free(*(matrix + i));
            }
            free(matrix);
            matrix = NULL;
            break;
        case 0:
            g = 0;
            break;
        }
    }
    printf("\n");
    printf("Piece of cake 1: \n");
    piece_of_cake();

    printf("\n");
    printf("Piece of cake 2: \n");
    int a = 5;
    int b = 6;
    piece_of_cake2(&a, &b);

    printf("\n");
    printf("Enter the size of the array for the following tasks: ");
    int n1;
    scanf("%d", &n1);
    int *arr = malloc(sizeof(int) * n1);
    for (int i = 0; i < n1; i++)
    {
        int z;
        scanf("%d", &z);

        *(arr+i) = z;
    }
    for (int i = 0; i < n1; i++)
    {
        printf("%d ", *(arr+i));
    }
    printf("\n");
    printf("\n");
    printf("Easy task 1: \n");
    easy1(arr, n1);

    printf("\n");
    printf("Easy task 2: \n");
    easy2(arr, n1);

    printf("\n");
    printf("Medium task 1: \n");
    medium1(arr, n1);

    free(arr);
    return 0;
}

void selsort2(int **arr, int m, int n)
{
    int l = m-1;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n-i-1; j++)
        {
            if (*(*(arr+j)+l) > *(*(arr+(j+1))+l))
            {
                int temp = *(*(arr+j)+l);
                *(*(arr+j)+l) = *(*(arr+(j+1))+l);
                *(*(arr+(j+1))+l) = temp;             
            }
        }

    }
}

void piece_of_cake(void)
{
    int a;
    int *p = &a;
    *p = 5;
    printf("%i \n", *p); 
}

void piece_of_cake2(int *a, int *b)
{
    printf("a = %i, b = %i \n", *a, *b);
    int *temp = a;
    a = b;
    b = temp;
    printf("a = %i, b = %i \n", *a, *b);
}

void easy1(int *arr, int n)
{
    int *smallest = (arr + 0);
    int *largest = (arr + (n-1));
    for (int i = 0; i < n; i++)
    {
        if (*(arr + i) < *smallest)
        {
            smallest = (arr + i);
        }
        else if (*(arr + i) > *largest)
        {
            largest = (arr + i);
        }
    }
    printf("smallest = %i \n", *smallest);
    printf("largeest = %i \n", *largest);
}

void easy2(int *arr, int n)
{
    int sum;
    int *ps = &sum;
    for (int i = 0; i < n; i++)
    {
        if (*(arr + i) < 0)
        {
            *ps += *(arr+i);
        }
    }
    printf("sum of all negative numbers = %i \n", *ps);
}

void medium1(int *arr, int n)
{
    int m;
    int *pm = &m;
    int p;
    int *pp = &p;
    *pp = -1;
    printf("Enter the number you want to find: ");
    scanf("%i", pm);
    for (int i = 0; i < n; i++)
    {
        if (*(arr+i) == *pm)
        {
            *pp = i;
            printf("Index: %i \n", *pp);
            break;
        }
    }
    if (*pp == -1)
    {
        printf("There is no such number :(\n");
    }
}