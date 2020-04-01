#include <stdio.h>
#include <stdlib.h>

FILE *add_file_ptr;
int i = 0;
int log_add[1000], page_num[1000], offset[1000];
char temp[100];

int main() {
    add_file_ptr = fopen("D:\\EECS_3221\\EECS3221_MiniProject3-master\\StartKit\\addresses.txt", "r");

    if (add_file_ptr) {
        while (fgets(temp, 1000, add_file_ptr) != NULL) {
            page_num[i] = offset[i] = log_add[i] = atoi(temp);
            page_num[i] &= 65280;
            page_num[i] >>= 8;
            offset[i] &= 255;

            printf("\n%d\t%d\t%d\t%d", i, log_add[i], page_num[i], offset[i]);
            i++;
        }

        fclose(add_file_ptr);
    }

    return 0;
}

