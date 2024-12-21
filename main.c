#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

/////bubble sort/////

void bubble_sort(int *arr, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}

/////improved bubble sort/////

void bubble_improved(int *arr, int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        int swapped = 0;
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                swapped = 1;
            }
        }
        if(!swapped)
            break;
    }
}

/////selection sort/////

void selection_sort(int *arr, int n)
{
    for (int i = 0; i < n - 1; i++) 
    {
        int min_i = i;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_i])
            {
                min_i = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_i];
        arr[min_i] = temp;
    }
}

/////quick sort/////

int partition(int *arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for(int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quick_sort(int *arr, int low, int high)
{
    if(low < high)
    {
        int pivot = partition(arr, low, high);

        quick_sort(arr, low, pivot - 1);
        quick_sort(arr, pivot + 1, high);
    }
}

/////improved quick sort/////

void quick_improved(int *arr, int low, int high)
{
    if (high - low + 1 <= 20)
    {
        selection_sort(arr + low, high - low + 1);
    }
    else
    {
        if (low < high)
        {
            int pivot = partition(arr, low, high);
            quick_improved(arr, low, pivot - 1);
            quick_improved(arr, pivot + 1, high);
        }
    }
}

/////merge sort/////

void merge(int *arr, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}


void merge_sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

/////radix sort/////

void counting_sort(int array[], int size, int place) {
    int *output = malloc(size * sizeof(int));
    int count[10] = {0};

    for (int i = 0; i < size; i++) {
        int index = (array[i] / place) % 10;
        count[index]++;
    }

    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        int index = (array[i] / place) % 10;
        output[count[index] - 1] = array[i];
        count[index]--;
    }

    for (int i = 0; i < size; i++) {
        array[i] = output[i];
    }

    free(output);
}

void radix_sort(int array[], int size) {
    int max = array[0];
    for (int i = 1; i < size; i++) {
        if (array[i] > max) {
            max = array[i];
        }
    }

    for (int place = 1; max / place > 0; place *= 10) {
        counting_sort(array, size, place);
    }
}


int main()
{   
    FILE *file= fopen("input.txt", "r");
    int target = 56500000;
    int *numbers = malloc(target * sizeof(int));
    int *copy = malloc(target * sizeof(int));

    for(int i = 0; i < target; i++)
    {
        fscanf(file, "%d", &numbers[i]);
    }
    
    struct timeval start, end;
    double taken_time;
/*
    memcpy(copy, numbers, target * sizeof(int));
    gettimeofday(&start, NULL);
    bubble_sort(copy, target);
    gettimeofday(&end, NULL);
    taken_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("bubble sort taken time %.6lf sec\n", taken_time);

    memcpy(copy, numbers, target * sizeof(int));
    gettimeofday(&start, NULL);
    bubble_improved(copy, target);
    gettimeofday(&end, NULL);
    taken_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("improved sort bubble taken time %.6lf sec\n", taken_time);

    memcpy(copy, numbers, target * sizeof(int));
    gettimeofday(&start, NULL);
    selection_sort(copy, target);
    gettimeofday(&end, NULL);
    taken_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("selection sort taken time %.6lf sec\n", taken_time);

    memcpy(copy, numbers, target * sizeof(int));
    gettimeofday(&start, NULL);
    quick_sort(copy, 0, target - 1);
    gettimeofday(&end, NULL);
    taken_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("quick sort taken time %.6lf sec\n", taken_time);

    memcpy(copy, numbers, target * sizeof(int));
    gettimeofday(&start, NULL);
    quick_improved(copy, 0, target - 1);
    gettimeofday(&end, NULL);
    taken_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("improved quick sort taken time %.6lf sec\n", taken_time);

    memcpy(copy, numbers, target * sizeof(int));
    gettimeofday(&start, NULL);
    merge_sort(copy, 0, target - 1);
    gettimeofday(&end, NULL);
    taken_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("merge sort taken time %.6lf sec\n", taken_time);
*/
    memcpy(copy, numbers, target * sizeof(int));
    gettimeofday(&start, NULL);
    radix_sort(copy, target);
    gettimeofday(&end, NULL);
    taken_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
    printf("radix sort taken time %.6lf sec\n", taken_time);

    fclose(file);
}
