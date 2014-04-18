#ifndef MEMMGR_H_
#define MEMMGR_H_

#include"stdint.h"
#include"utility.h"
#define PANIC(msg) 

typedef uint32_t u32int;

u32int kmalloc_int(u32int sz, int align, u32int *phys);
u32int kmalloc_a(u32int sz);  // page aligned.
u32int kmalloc_p(u32int sz, u32int *phys); // returns a physical address.
u32int kmalloc_ap(u32int sz, u32int *phys); // page aligned and returns a physical address.
u32int kmalloc(u32int sz); // vanilla (normal). 



typedef struct registers
{
    u32int ds;                  // Data segment selector
    u32int edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    u32int int_no, err_code;    // Interrupt number and error code (if applicable)
    u32int eip, cs, eflags, useresp, ss; // Pushed by the processor automatically.
} registers_t;


typedef struct page
{
   u32int present    : 1;   // Page present in memory
   u32int rw         : 1;   // Read-only if clear, readwrite if set
   u32int user       : 1;   // Supervisor level only if clear
   u32int accessed   : 1;   // Has the page been accessed since last refresh?
   u32int dirty      : 1;   // Has the page been written to since last refresh?
   u32int unused     : 7;   // Amalgamation of unused and reserved bits
   u32int frame      : 20;  // Frame address (shifted right 12 bits)
} page_t;

typedef struct page_table
{
   page_t pages[1024];
} page_table_t;

typedef struct page_directory
{
   /**
      Array of pointers to pagetables.
   **/
   page_table_t *tables[1024];
   /**
      Array of pointers to the pagetables above, but gives their *physical*
      location, for loading into the CR3 register.
   **/
   u32int tablesPhysical[1024];
   /**
      The physical address of tablesPhysical. This comes into play
      when we get our kernel heap allocated and the directory
      may be in a different location in virtual memory.
   **/
   u32int physicalAddr;
} page_directory_t;

void initialise_paging();
void switch_page_directory(page_directory_t *new);
page_t *get_page(u32int address, int make, page_directory_t *dir);
void page_fault(registers_t regs); 


// A bitset of frames - used or free.
u32int *frames;
u32int nframes;

// Defined in kheap.c

 static void set_frame(u32int frame_addr);
 static void clear_frame(u32int frame_addr);
 static u32int test_frame(u32int frame_addr);
 static u32int first_frame();
 void alloc_frame(page_t *page, int is_kernel, int is_writeable);
 void free_frame(page_t *page);

 void initialise_paging();
 void switch_page_directory(page_directory_t *dir);
 page_t *get_page(u32int address, int make, page_directory_t *dir);
#endif
