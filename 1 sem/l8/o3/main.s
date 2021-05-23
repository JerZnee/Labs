	.file	"main.c"
	.text
	.section	.rodata
.LC0:
	.string	"%d"
.LC1:
	.string	"f=%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
#APP
# 6 "main.c" 1
	dhs
# 0 "" 2
#NO_APP
	leaq	-20(%rbp), %rax
	movq	%rax, %rsi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	__isoc99_scanf@PLT
	movl	$0, -12(%rbp)
.L5:
	movl	-20(%rbp), %eax
	cmpl	%eax, -12(%rbp)
	jge	.L2
	movl	-20(%rbp), %eax
	testl	%eax, %eax
	js	.L3
	movl	-20(%rbp), %eax
	movl	$2, %esi
	movl	%eax, %edi
	call	_Z3proii@PLT
	movl	%eax, -16(%rbp)
	jmp	.L4
.L3:
	movl	-20(%rbp), %eax
	movl	%eax, %esi
	movl	$2, %edi
	call	_Z3proii@PLT
	movl	%eax, -16(%rbp)
.L4:
	addl	$1, -12(%rbp)
	jmp	.L5
.L2:
	movl	-16(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax
	call	_Z6printfPKcz@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L7
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 10.2.0"
	.section	.note.GNU-stack,"",@progbits
