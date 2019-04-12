#include "stdlib.h"
#include "stdio.h"

// вывод массива
void array_out(int* array, int count) {
    int i;
    for(i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


// сортировка merge
void msort(int* array, int count, int size, int (*comparator)(const void*, const void*)) {
    
    if(count == 1) {
        return;
    }

    // разбиение
    int sep = (int) count/2;
    int array1[sep];
    int array2[count-sep];
    int i;
    for(i = 0; i < sep; i++) {
        array1[i] = array[i];
    }
    for(i = 0; i < count-sep; i++) {
        array2[i] = array[sep+i];
    }

    msort(array1, sep, size, comparator);
    msort(array2, count-sep, size, comparator);

    // слияние
    int j1=0, j2=0;
    for(i = 0; i < count; i++) {
        if(j1 == sep) {
            array[i] = array2[j2];
            j2++;
        } else if(j2 == count-sep) {
            array[i] = array1[j1];
            j1++;
        } else {
            if(comparator(&array1[j1], &array2[j2]) < 0) {
                array[i] = array1[j1];
                j1++;
            } else {
                array[i] = array2[j2];
                j2++;
            }
        }
    }
    
}

// убывающий порядок
int revers_sorter(const void* first_arg, const void* second_arg) {
    int* first = (int*)first_arg;
    int* second = (int*)second_arg;

    if(*first < *second) {
        return 1;
    }
    if(*first > *second) {
        return -1;
    }
    return 0;
}

// возрастающий порядок
int inc_sorter(const void* first_arg, const void* second_arg) {
    int* first = (int*)first_arg;
    int* second = (int*)second_arg;

    if(*first > *second) {
        return 1;
    }
    if(*first < *second) {
        return -1;
    } 
    return 0;
}

// возрастающий по модулю 5
int mod_five_sorter(const void* first_arg, const void* second_arg) {
    int first = *(int*)first_arg % 5;
    int second = *(int*)second_arg % 5;
    
    if(first < second) {
        return -1;
    } 
    if(first > second) {
        return 1;
    }
    return 0;

}

void main() {
    int array[10] = {3, 5, 1, 7, 2, 7, 6, 0, 8, 4};
    /*
    array_out(array, 10);

    qsort(array, 10, sizeof(int), &revers_sorter);
    array_out(array, 10);
    
    qsort(array, 10, sizeof(int), &inc_sorter);
    array_out(array, 10);
    
    qsort(array, 10, sizeof(int), &mod_five_sorter);
    array_out(array, 10);
    */
    
    array_out(array, 10);

    msort(array, 10, sizeof(int), &revers_sorter);
    array_out(array, 10);

    msort(array, 10, sizeof(int), &inc_sorter);
    array_out(array, 10);

    msort(array, 10, sizeof(int), &mod_five_sorter);
    array_out(array, 10);

}