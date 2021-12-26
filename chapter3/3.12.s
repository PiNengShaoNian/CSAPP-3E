uremdiv:
  movq %rdx,%r8  # Copy qp
  movq %rdi,%rax # Move x to lower 8 bytes of dividend
  movl $0,%edx   # Set upper 8 bytes of dividend to 0
  divq %rsi      # Divide by y
  movq %rax, (%r8) # Store quotient at qp
  movq %rdx,(%rcx) # Store remainder at rp
  ret