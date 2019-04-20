#include "stdlib.h"
#include "stdio.h"
#include "math.h"

// вывод массива
void array_out(int* array, int count) {
    int i;
    for(i = 0; i < count; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}


void char_out(char* array, int count) {
    int i;
    for(i = 0; i < count; i++) {
        printf("%c ", array[i]);
    }
    printf("\n");
}

void float_out(float* array, int count) {
    int i;
    for(i = 0; i < count; i++) {
        printf("%.3f ", array[i]);
    }
    printf("\n");
}


    
// рекурсивная часть сортировки
void merge(char* array, int count, int size, int (*comparator)(const void*, const void*)) {
        
    if(count == size) {
        return;
    }

    // разбиение
    int sep = (int) count/(2*size);
    char array1[sep*size];
    char array2[count-sep*size];

    int i, k;
    for(i = 0; i < sep*size; i++) {
        array1[i] = array[i];
    }
    for(i = 0; i < count-sep*size; i++) {
        array2[i] = array[sep*size+i];
    }

    merge(array1, sep*size, size, comparator);
    merge(array2, count-sep*size, size, comparator);

    // слияние
    int j1=0, j2=0;
    for(i = 0; i < count; i+=size) {
        if(j1 == sep*size) {
            for(k=0; k<size; k++) {
                array[i+k] = array2[j2+k];
            }
            j2+=size;
        } else if(j2 == count-sep*size) {
            for(k=0; k<size; k++) {
                array[i+k] = array1[j1+k];
            }
            j1+=size;
        } else {
            if(comparator(&array1[j1], &array2[j2]) < 0) {
                for(k=0; k<size; k++) {
                    array[i+k] = array1[j1+k];
                }
                j1+=size;
            } else {
                for(k=0; k<size; k++) {
                    array[i+k] = array2[j2+k];
                }
                j2+=size;
            }
        }
    }
}

// преобразование массива и вызов сортировки
void msort(void* t_array, int array_count, int size, int (*comparator)(const void*, const void*)) {    
   
    char *array = (char*)t_array;
    merge(array, array_count*size, size, comparator);
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

// возрастающий порядок символьный
int ab_sorter(const void* first_arg, const void* second_arg) {
    char* first = (char*)first_arg;
    char* second = (char*)second_arg;

    if(*first > *second) {
        return 1;
    }
    if(*first < *second) {
        return -1;
    } 
    return 0;
}

// убывающий порядок символьный
int zy_sorter(const void* first_arg, const void* second_arg) {
    char* first = (char*)first_arg;
    char* second = (char*)second_arg;

    if(*first < *second) {
        return 1;
    }
    if(*first > *second) {
        return -1;
    } 
    return 0;
}

// возрастающий для вещественных
int f_inc_sorter(const void* first_arg, const void* second_arg) {
    float* first = (float*)first_arg;
    float* second = (float*)second_arg;

    if(*first < *second) {
        return -1;
    } 
    if(*first > *second) {
        return 1;
    }
    return 0;

}

// вещественные по убыванию дробной части
int frac_rev_sorter(const void* first_arg, const void* second_arg) {
    float first, second, intpart;
    first = fabsf(modff(*(float*)first_arg, &intpart));
    second = fabsf(modff(*(float*)second_arg, &intpart));

    if(first > second) {
        return -1;
    } 
    if(first < second) {
        return 1;
    }
    return 0;

}

void main() {
    int array[10] = {3, 5, 1, 7, 2, 7, 6, 0, 8, 4};
    char array_c[6] = {'q', 'w', 'e', 'r', 't', 'y'};
    float array_f[9] = {-0.6, 67.543, -8765, 345, 123.123, 6754.786, 6754.785, 0,-4};
     
    array_out(array, 10);

    msort(array, 10, sizeof(int), &inc_sorter);
    array_out(array, 10);

    msort(array, 10, sizeof(int), &revers_sorter);
    array_out(array, 10);

       
    char_out(array_c, 6);

    msort(array_c, 6, sizeof(char), &ab_sorter);
    char_out(array_c, 6);

    msort(array_c, 6, sizeof(char), &zy_sorter);
    char_out(array_c, 6);

    
    float_out(array_f, 9);
    
    msort(array_f, 9, sizeof(float), &f_inc_sorter);
    float_out(array_f, 9);

    msort(array_f, 9, sizeof(float), &frac_rev_sorter);
    float_out(array_f, 9);
} 