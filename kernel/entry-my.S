# This is only for moving the entry on a different location. Just to see how things are changing

.section .data
string: 
  .asciz "\nmyentry code is exceuted\nOrignal entry code follows\n" # The string to be printed
uartbase:
  .word 0x10000000  # UART base address (in QEMU)

.section .text
.global _myentry
_myentry:
  # Only print on cpuid 0
  csrr a1, mhartid          # Loard hartid into a1
  bne a1, zero, end_print   # Jump to end_print if cpuid is not equal to 0

  # Direct UART access to print the string defined above
  la t0, string       # Load the address of the string into t0
print_loop:
  lb t1, 0(t0)        # Load the next char of the string into t1
  beqz t1, end_print  # If t1 is zero (NULL terminator), jump to end_print

  # Wait until the UART is ready to transmit the char 
  # the next to lines, are doing the same as li t2, 0x10000000 
  la a0, uartbase    # Load the address of the uartbase inti a0
  lw t2, 0(a0)       # Load the word (4 bytes) into t2 
  
uart_ready:
  lbu t3, 5(t2)       # Load the UART Line Status Register (LSR)
  andi t3, t3, 0x20   # Check if Transmit Holding Register is empty  (5 bit of LSR)
  beqz t3, uart_ready # If not empty, wait in the loop till uart is ready

  # Write the chat to the UART data register
  sb t1, 0(t2)

  addi t0, t0, 1      # Move to the next char of the string
  j print_loop        # Reapeat for the next char till NULL terminator is reached

end_print:
  # set all registers to zero , just todo some work
  mv ra, zero
  mv sp, zero
  mv gp, zero
  mv t0, zero
  mv t1, zero
  mv t2, zero
  mv s0, zero
  mv s1, zero
  mv a0, zero
  mv a1, zero
  mv a2, zero
  mv a3, zero
  mv a4, zero
  mv a5, zero
  mv a6, zero
  mv a7, zero
  mv s2, zero
  mv s3, zero
  mv s4, zero
  mv s5, zero
  mv s6, zero
  mv s7, zero
  mv s8, zero
  mv s9, zero
  mv s10, zero
  mv s11, zero
  mv t3, zero
  mv t4, zero
  mv t5, zero
  mv t6, zero

  # jump to the real entry 
  j _entry
        