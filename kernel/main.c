#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0;

// Use Entry Point Address in our main.c
extern void _entry();
extern void _myentry();


// start() jumps here in supervisor mode on all CPUs.
void
main()
{
  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\n");
    printf("xv6 kernel is booting\n\n");
    printf("Entrypoint address is %p\n\n", _entry);
    printf("Stacksize per CPU is %d bytes\n\n", 1024 * CPUSTACKSIZE);
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
    // The next two lines assume, that the function freepg() is defined  
    printf("freepages %d\n", freepg());
    printf("free memory: %d bytes\n", freepg() * 4096);
    printf("\n");
    printf("hart %d started\n", cpuid());
    __sync_synchronize();
    started = 1;
  } else {
    uint waitcycle = 0; 
    while(started == 0)
      waitcycle = waitcycle + 1; //count the waitcylce per hart
      ;
    __sync_synchronize();
    printf("hart %d starting: wait cycle %d\n", cpuid(), waitcycle);
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }

  scheduler();        
}
