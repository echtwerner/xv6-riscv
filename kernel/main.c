#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0;

// start() jumps here in supervisor mode on all CPUs.
void
main()
{
  uint w = 0; 
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\n");
    printf("xv6 kernel is booting\n");
    printf("\n");
    printf("Stacksize per CPU is %d bytes\n", 1024 * CPUSTACKSIZE);
    printf("\n");
    kinit();         // physical page allocator
    kvminit();       // create kernel page table
    kvminithart();   // turn on paging
    procinit();      // process table
    trapinit();      // trap vectors
    trapinithart();  // install kernel trap vector
    plicinit();      // set up interrupt controller
    plicinithart();  // ask PLIC for device interrupts
    binit();         // buffer cache
    iinit();         // inode table
    fileinit();      // file table
    virtio_disk_init(); // emulated hard disk
    userinit();      // first user process
    printf("freepages %d\n", freepg());
    printf("free memory: %d bytes\n", freepg() * 4096);
    printf("hart %d started\n", cpuid());
    __sync_synchronize();
    started = 1;
  } else {
    while(started == 0)
     w = w + 1;
     ;
    __sync_synchronize();
    printf("hart %d starting: wait cycle %d\n", cpuid(), w);
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }

  scheduler();        
}
