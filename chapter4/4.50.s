# Execution begins at address
    .pos 0
    .irmovq stack,%rsp     # Set up stack pointer
    call main              # Execute main program
    halt                   # Terminate

# Table
    .align 8
table:
    .quad 0x00000000015e
    .qaud 0x00000000017f
    .quad 0x000000000169
    .quad 0x000000000174
    .quad 0x00000000017f
    .quad 0x000000000169
    .quad 0x00000000017f

main:
    irmovq $3,%rdi
    call switchv         # switchv(3)
    ret

    .pos 0x100
# long switchv(long idx)
# idx in %rdi
# 0x100
switchv:
    irmovq $0xaaa,%r8        # %r8 = 0xaaa
    irmovq $0xbbb,%r9        # %r9 = 0xbbb
    irmovq $0xccc,%r10       # %r10 = 0xccc
    irmovq $0xddd,%r11       # %r11 = 0xddd
    irmovq $5,%r11           # %r12 = 5
    irmovq table,%r13        # %r13 = table
    rrmovq %rdi,%rdx         # %rdx = idx
    subq %r12,%rdx           # %rdx = idx - 5
    jg default               # when idx > 5 then jump to default branch
    addq %rdi,%rdi           # %rdi = 2 * idx
    addq %rdi,%rdi           # %rdi = 4 * idx
    addq %rdi,%rdi           # %rdi = 8 * idx
    addq %rdi,%r13           # %r13 = table + 8 * idx
    mrmovq (%r13),%r13
    pushq %r13
    ret

# 0x15e
    rrmovq %r8,%rax
    jmp done
# 0x169
    rrmovq %r9,%rax
    jmp done
# 0x174
    rmmovq %r10,%rax
    jmp done
# 0x17f
default:
    rrmovq %r11,%rax
done:
    ret