#   #include <stdio.h>
#   
#   long arr[] = {0xabc, 0xbc, 0xc, 0x1};
#   void bubble_b(long *data, long count) {
#       long i, last;
#       for(last = count - 1; last > 0; last--) {
#           for(i = 0; i < last; i++) {
#               if(*(data + i + 1) < *(data + i)) {
#                   long t = *(data + i + 1);
#                   *(data + i + 1) = *(data + i);
#                   *(data + i) = t;
#               }
#           }
#       }
#   }
#   
#   int main() {
#       bubble_b(arr, 4);
#       return 0;
#   }

# Execution begins at address
    .pos 0
    irmovq stack,%rsp  # Set up stack pointer
    call main          # Execution main program
    halt               # Terminate program

# Array of 4 elements
arr:
    .quad 2748
    .quad 188
    .quad 12
    .quad 1

main:
    irmovq array, %rdi  # Set first argument of bubble_b
    irmovq $4,%rsi      # Set second argument of bubble_b
    call bubble_b       # bubble(array, 4)
    ret

# void bubble_b(long *data, long count)
# data in %rdi, count in %rsi
bubble_b:
    irmovq $1,%r8       # Constant 1
    irmovq $8,%r9       # Constant 8
    rrmovq %rsi,%rax
    subq %r8,%rax       # last--
    je done             # Stop when last == 0

loop1:
    xorq %rcx,%rcx      # i = 0
loop2:
    rrmovq %rcx,%rdx    # %rdx = i
    addq %rdx,%rdx      # %rdx = 2 * i
    addq %rdx,%rdx      # %rdx = 4 * i
    addq %rdx,%rdx      # %rdx = 8 * i
    addq %rdi,%rdx      # %rdx = 8 * i + data
    mrmovq (%rdx),%r10  # %r10 = data[i]
    addq %r9,%rdx       # %rdx += 8
    mrmovq (%rdx),%rbx  # %rbx = data[i + 1]
    rrmovq %rbx,%r11    # %r11 = data[i + 1]
    subq %r10,%rbx      # %rbx = data[i + 1] - data[i]
    rrmovq %r11,%r12    # %r12 = data[i + 1]
    rrmovq %r10,%r13    # %r13 = data[i]
    cmovl  %r10,%r12    # if data[i + 1] < data[i] then %r12 = data[i]
    cmovl  %r11,%r13    # if data[i + 1] < data[i] then %r13 = data[i + 1]
    rmmovq %r12,(%rdx)  # data[i + 1] = %r12
    subq %r9,%rdx       # %rdx = %rdx - 8
    rmmovq %r13,(%rdx)  # data[i] = %r13
test:
    addq %r8,%rcx       # i++
    rrmovq %rcx,%r12    # %r12 = %rcx = i
    subq %rax,%r12      # i - last
    jl loop2            # i < last
    subq %r8,%rax       # last--
    jg loop1
done:
    ret                 # Return

# Stack starts here and grows to lower addresses
    .pos 0x200
stack: