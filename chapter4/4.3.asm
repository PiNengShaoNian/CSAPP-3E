sum:
  xorq %rax,%rax # sum = 0
  andq %rsi,%rsi # Set CC
  jmp test
loop:
  mrmovq (%rdi),%r10 # Get *start
  addq %10,%rax  # Add to sum
  iaddq $8,%rdi  # start++
  iaddq $-1,%rsi # count--. Set CC
test:
  jne loop  # Stop when count = 0
  ret