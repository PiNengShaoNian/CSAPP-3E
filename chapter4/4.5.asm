# long absSum(long *start, long count)
# start in %rdi, count in %rsi
absSum:
  irmovq $8,%r8  # Constant 8
  irmovq $1,%r9  # Constant 1
  xorq %rax,%rax # sum = 0
  andq %rsi,%rsi # Set condition codes
  jmp test
loop:
  mrmovq (%rdi),%r10 # x = *start
  xorq %r11,%r11     # Constant 0
  subq %r10,%r11     # -x
  jle pos            # Skip if -x <= 0
  rrmovq %r11,%r10   # x = -x
pos:
  addq %r10,%rax     # Add to sum
  addq %r8,%rdi      # start++
  addq %r9,%rsi      # count--

test:
  jne loop  # Stop when 0
  ret