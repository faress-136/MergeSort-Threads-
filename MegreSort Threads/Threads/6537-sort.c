// Merge sort in C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
FILE *fpp;
struct Info {
    int size;
    int array[];
};struct Info info;

struct Passed_index {
    int index_left;
    int index_right;
};struct Passed_index passed_index;




void merge(int arr[], int p, int q, int r) {
    
    
    int n1 = q - p + 1;
    int n2 = r - q;
    
    int L[n1], M[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[q + 1 + j];
    
    
    int i, j, k;
    i = 0;
    j = 0;
    k = p;
    
    
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = M[j];
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
        arr[k] = M[j];
        j++;
        k++;
    }
}



void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        fprintf(fpp,"%d ", arr[i]);
    fprintf(fpp,"\n");
}

void *mergeSort_threads(void *arg){
    struct Passed_index passed_index_threads = *(struct Passed_index*) arg;
    struct Passed_index t1,t2;
    int left = passed_index_threads.index_left;
    int right = passed_index_threads.index_right;
    if (left<right) {
        int calculated_middle =left + (right - left) / 2;
        t1.index_left = left;
        //printf("%d........\n",t1.index_left);
        t1.index_right = calculated_middle;
        //printf("%d////////\n",t1.index_right);
        t2.index_left = calculated_middle + 1;
        // printf("%d.........\n",t2.index_left);
        t2.index_right = right;
        //printf("%d/////////\n",t2.index_right);
        pthread_t threads[2];
        pthread_create(&threads[0], NULL, &mergeSort_threads, &t1);
        pthread_create(&threads[1], NULL, &mergeSort_threads, &t2);
        pthread_join(threads[0], NULL);
        pthread_join(threads[1], NULL);
        merge(info.array, left, calculated_middle, right);
        
        
        
        
    }
    
    
    return NULL;
}


void mergeSort_new(int arr[], int l, int r){
    pthread_t no_threads[info.size];
    if (l < r) {
        
        passed_index.index_left = l;
        passed_index.index_right = r;
        pthread_create(&no_threads[0], NULL, &mergeSort_threads, &passed_index);
        pthread_join(no_threads[0], NULL);
        
    }
    
    
}


int main() {
    FILE *fp;
    fp = fopen("Sort.txt", "r");
    fpp = fopen("Output", "w");
    fscanf(fp,"%d ",&info.size);
    fprintf(fpp,"size = %d \n",info.size);
    //    info.array[info.size];
    for (int i=0; i<info.size; i++) {
        fscanf(fp, "%d",&info.array[i]);
    }
    for (int i=0; i<info.size; i++) {
        fprintf(fpp,"%d ",info.array[i]);
    }
    fprintf(fpp,"\n");
    
    mergeSort_new(info.array, 0, info.size - 1);
    
    fprintf(fpp,"Sorted array: \n");
    printArray(info.array, info.size);
}

