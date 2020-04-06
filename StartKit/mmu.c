/*
 * Create by Karmit
 * 17 March, 2020
 */
#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define TLB_ENTRIES 16
#define PAGES 256
#define PAGE_MASK 255

#define PAGE_SIZE 256
#define OFFSET_BITS 8
#define OFFSET_MASK 255

#define MEMORY_SIZE PAGES * PAGE_SIZE

#define BUFFER_SIZE 10

struct tlbentry {
    unsigned char logical;
    unsigned char physical;
};

struct tlbentry tlb[TLB_ENTRIES];

int current_ind = 0;

int pagetable[PAGES];

signed char main_memory[MEMORY_SIZE];

signed char *backing;

int maximum(int, int);
int search_tlb(unsigned char);
void add_tlb_entry(unsigned char, unsigned char);

int main(int argc, const char *argv[]) {

    char *csv_filename = "output.csv";
    FILE *csv_ptr;
    csv_ptr = fopen(csv_filename, "w+");

    const char *backing_filename = argv[1];
    int backing_fd = open(backing_filename, 0);
    // Map a specific memory size.
    backing = mmap(0, MEMORY_SIZE, PROT_READ, MAP_PRIVATE, backing_fd, 0);

    const char *input_filename = argv[2];
    FILE *input_fp = fopen(input_filename, "r");

    int i;
    for (i = 0; i < PAGES; i++) {
        pagetable[i] = -1;
    }

    char buffer[BUFFER_SIZE];

    int total_addresses = 0;
    int tlb_hits = 0;
    int page_faults = 0;

    unsigned char free_page = 0;

    while (fgets(buffer, BUFFER_SIZE, input_fp) != NULL) {
        int logical_address = atoi(buffer);
        int offset = logical_address & OFFSET_MASK;
        int logical_page = (logical_address >> OFFSET_BITS) & PAGE_MASK;
        int physical_page = search_tlb(logical_page);

        total_addresses++;

        if (physical_page != -1) {
            tlb_hits++;
        } else {
            physical_page = pagetable[logical_page];

            if (physical_page == -1) {
                page_faults++;
                physical_page = free_page;
                free_page++;

                memcpy(main_memory + physical_page * PAGE_SIZE, backing + logical_page * PAGE_SIZE, PAGE_SIZE);

                pagetable[logical_page] = physical_page;
            }
            add_tlb_entry(logical_page, physical_page);
        }

        int physical_address = (physical_page << OFFSET_BITS) | offset;
        signed char value = main_memory[physical_page * PAGE_SIZE + offset];
        fprintf(csv_ptr, "%d, %d, %d\n", logical_address, physical_address, value);
        printf("%d\n", value);
    }

    fclose(csv_ptr);
    printf("Page Faults = %d\nTLB Hits = %d\n", page_faults, ++tlb_hits);
    printf("Page Fault Rate = %.2f\nTLB Hit Rate = %.2f\n", page_faults / (1.00 * total_addresses),
           tlb_hits / (1.00 * total_addresses));

    return 0;
}


int maximum(int a, int b) {
    if (a > b)
        return a;
    return b;
}

int search_tlb(unsigned char logical_page) {
    int i;
    for (i = maximum((current_ind - TLB_ENTRIES), 0); i < current_ind; i++) {
        struct tlbentry *entry = &tlb[i % TLB_ENTRIES];

        if (entry->logical == logical_page) {
            return entry->physical;
        }
    }
    return -1;
}

void add_tlb_entry(unsigned char logical, unsigned char physical) {
    struct tlbentry *entry = &tlb[current_ind % TLB_ENTRIES];

    current_ind++;
    entry->logical = logical;
    entry->physical = physical;
}
