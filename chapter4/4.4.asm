# X86-64
# long rsum(long *start, long count)
# start in %rdi, count in %rsi
rsum:
  movl $0, %eax
  testq %rsi, %rsi
  jle .L9
  pushq %rbx
  movq (%rdi), %rbx
  subq $1, %rsi
  addq $8, %rdi
  call rsum
  addq %rbx, %rax
  popq %rbx
.L9:
  rep;ret

# Y86-64
# long rsum(long *start, long count)
# start in %rdi, count in %rsi
rsum:
  xorq %rax,%rax # Set return value to 0
  andq %rsi,%rsi # Set condition codes
  je return
  pushq %rbx
  mrmovq (%rdi),%rbx
  irmovq $-1,%r10
  addq %r10,%rsi
  irmovq $8,%r10
  addq %r10,%rdi
  call rsum
  addq %rbx,%rax
  popq %rbx
return:
  ret