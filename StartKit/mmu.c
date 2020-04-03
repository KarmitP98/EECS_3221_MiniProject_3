#include <stdio.h>
#include <stdlib.h>

FILE *add_file_ptr, *bin_file_ptr;
int i = 0;
int log_add[1000], page_num[1000], offset[1000], frame[1000], itemp[1000], page_m[1000], phy_add[1000];
char temp[100];
char *dump;

char *readBinaryFile(int);
void outputBinaryFile();

int main() {
    add_file_ptr = fopen("../StartKit/addresses.txt", "r");

    outputBinaryFile();

    if (add_file_ptr) {
        while (fgets(temp, 1000, add_file_ptr) != NULL) {
            page_num[i] = offset[i] = log_add[i] = itemp[i] = page_m[i] =
                    _strtoi64(temp, dump, 10);
            page_num[i] /= 255;                 // Get the page number
            offset[i] &= 255;                   // Get the offset
            page_num[i] &= 15;
            page_m[i] &= 65280;
            page_m[i] >>= 8;

//            readBinaryFile(page_m[i]);

//            frame[i] = _strtoi64(readBinaryFile(page_m[i]), dump, 10);
//            frame[i] <<=8;

//            phy_add[i] = frame[i] | offset[i];

//            printf("\n%d\t%d\t%d\t%d", i, log_add[i], page_num[i], offset[i]);
//            i++;
        }

        fclose(add_file_ptr);
    }

    return 0;
}

char *readBinaryFile(int p_num) {
    bin_file_ptr = fopen("../StartKit/BACKING_STORE.bin", "rb");

    __int8 page = 0;

    if (bin_file_ptr) {
        fseek(bin_file_ptr, p_num, SEEK_SET);
        fread(page, 8, 1, bin_file_ptr);
        printf("\n%d", page);
    }

    fclose(bin_file_ptr);

    return page;
}

void outputBinaryFile()
{
    bin_file_ptr = fopen("../StartKit/BACKING_STORE.bin", "rb");

    signed __int8 page;

    if(bin_file_ptr)
    {
        for(i = 0;i<65536;i++)
        {
            fread(&page, sizeof(signed __int8),1,bin_file_ptr);
            printf("\n%d\t%d",i,page);
        }
    }

    fclose(bin_file_ptr);
}