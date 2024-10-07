#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0;

// Use Entry Point Address in our main.c
extern void _entry();


// start() jumps here in supervisor mode on all CPUs.
void
main()
{
  // Initialize an array to hold a waitcycle count per cpu.
  uint waitcycle[NCPU];

  if(cpuid() == 0){
    consoleinit();
    printfinit();
    printf("\nxv6 kernel is booting\n\n");
    printf("Entrypoint address is %p\n\n", _entry);
    printf("Config from Makefile:\nmax memory is %dM\nmaximum number of CPUs is %d\n\n", MAXMEM, NCPU);
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
    printf("\n");
    printf("hart %d started\n", cpuid());
    __sync_synchronize();
    started = 1;
  } else {
    waitcycle[cpuid()]=0;
    while(started == 0){
      waitcycle[cpuid()]= waitcycle[cpuid()] + 1; //count the waitcylce per hart
    }
    __sync_synchronize();
    printf("hart %d starting: wait cycle %d\n", cpuid(), waitcycle[cpuid()] );
    kvminithart();    // turn on paging
    trapinithart();   // install kernel trap vector
    plicinithart();   // ask PLIC for device interrupts
  }

  scheduler();        
}
