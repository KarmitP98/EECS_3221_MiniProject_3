#include <stdio.h>
#include <stdlib.h>

FILE *add_file_ptr, *bin_file_ptr;
int i = 0;
int log_add[1000], page_num[1000], offset[1000], frame[10000], itemp[10000],page_m[1000], phy_add[1000];
int page[256];
char temp[100];
char *dump;

int readBinaryFile(int);

int main() {
    add_file_ptr = fopen("D:\\EECS_3221\\EECS3221_MiniProject3-master\\StartKit\\addresses.txt", "r");

    if (add_file_ptr) {
        while (fgets(temp, 1000, add_file_ptr) != NULL) {
            page_num[i] = offset[i] = log_add[i] = itemp[i] = page_m[i] =
                    _strtoi64(temp, dump, 10);
            page_num[i] /= 255;                 // Get the page number
            offset[i] &= 255;                   // Get the offset
            page_num[i] &= 15;

            frame[i] = readBinaryFile(page_m[i]);
            frame[i] <<=8;

            phy_add[i] = frame[i] | offset[i];

            printf("\n%d\t%d\t%d\t%d\t%d\t%d", i, log_add[i], page_num[i], offset[i], frame[i],phy_add[i]);
            i++;
        }

        fclose(add_file_ptr);
    }

    return 0;
}

int readBinaryFile(int p_num)
{
    int result;
    bin_file_ptr = fopen("D:\\EECS_3221\\EECS3221_MiniProject3-master\\StartKit\\BACKING_STORE.bin","rb");

    if(bin_file_ptr)
    {
        fseek(bin_file_ptr,p_num,SEEK_SET);
        result = fread(page,8,1,bin_file_ptr);
//        printf("\n%d",result);
//        result = _strtoi64(page,dump,10);
//        result /= 32;
    }

    fclose(bin_file_ptr);

    return result;
}

