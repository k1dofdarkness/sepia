global sepia_asm

%macro iter 3
  shufps xmm3, xmm3, %1
  shufps xmm4, xmm4, %1
  shufps xmm5, xmm5, %1
  read rdi, xmm0, %2 
  lea rdi, [rdi+1]
  read rdi, xmm1, %2  
  lea rdi, [rdi+1]
  read rdi, xmm2, %2
  lea rdi, [rdi-2]
  mov r8, %3
%endmacro

%macro read 3
  pxor %2, %2 
  pinsrb %2, byte[%1+0], 0 
  pinsrb %2, byte[%1+0], 4 
  pinsrb %2, byte[%1+0], 8 
  pinsrb %2, byte[%1+3], 12
  shufps %2, %2, %3
  cvtdq2ps %2, %2
%endmacro

section .rodata

align 16
blue_coef: dd 0.131, 0.168, 0.189, 0.131
align 16
green_coef: dd 0.543, 0.686, 0.769, 0.543
align 16
red_coef: dd  0.272, 0.349, 0.393, 0.272
align 16
max: dd 255.0, 255.0, 255.0, 255.0

section .text

sepia_asm:
  mov r8, 1
  xor rcx, rcx
.loop:
  movdqa xmm3, [blue_coef]
  movdqa xmm4, [green_coef]
  movdqa xmm5, [red_coef]
  movdqa xmm6, [max]
  cmp r8, 1
  je .first
  cmp r8, 2
  je .second
  cmp r8, 3
  je .third
.first:
  iter 0xE7, 0xE8, 2
  jmp .calculate
.second:
  iter 0x79, 0xF8, 3
  jmp .calculate
.third:
  iter 0x9E, 0xFC, 1
  lea rdi, [rdi+3]
.calculate:
  mulps xmm3, xmm0
  mulps xmm4, xmm1
  mulps xmm5, xmm2
  addps xmm3, xmm4
  addps xmm5, xmm3
  pminsd xmm5, xmm6
  cvtps2dq xmm5, xmm5
  pextrb byte[rsi+0], xmm5, 0
  pextrb byte[rsi+1], xmm5, 4
  pextrb byte[rsi+2], xmm5, 8
  pextrb byte[rsi+3], xmm5, 12
  lea rsi, [rsi+4]
  lea rdi, [rdi+3]
  add rcx, 4
  cmp rdx, rcx 
  ja .loop
  ret
