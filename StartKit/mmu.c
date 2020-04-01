#include <stdio.h>
#include <stdlib.h>

FILE *add_file_ptr;
int i = 0;
int log_add[1000], page_num[1000], offset[1000], frame[10000], itemp[10000];
char temp[100];
char *dump;

int main() {
    add_file_ptr = fopen("D:\\EECS_3221\\EECS3221_MiniProject3-master\\StartKit\\addresses.txt", "r");

    if (add_file_ptr) {
        while (fgets(temp, 1000, add_file_ptr) != NULL) {
            page_num[i] = offset[i] = log_add[i] = itemp[i] =
                    _strtoi64(temp, dump, 10);
            page_num[i] /= 255;                 // Get the page number
            offset[i] &= 255;                   // Get the offset


            printf("\n%d\t%d\t%d\t%d\t%d", i, log_add[i], page_num[i], offset[i], frame[i]);
            i++;
        }

        fclose(add_file_ptr);
    }

    return 0;
}

