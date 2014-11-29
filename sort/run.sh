gcc -o str_sort str_sort.c insert_sort.c heap_sort.c merge_sort.c quick_sort.c
gcc -o num_sort num_sort.c insert_sort.c  merge_sort.c quick_sort.c radix_sort.c counting_sort.c
./str_sort 2>&1 > str_sort.log
./num_sort 2>&1 > num_sort.log
