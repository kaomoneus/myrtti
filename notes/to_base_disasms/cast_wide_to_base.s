_Z13__myrtti_castI8WideRootP9WideFinalEPT_T0_: # @_Z13__myrtti_castI8WideRootP9WideFinalEPT_T0_
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	testq	%rdi, %rdi
	je	.LBB6_1
# %bb.2:
	movq	%rdi, %rbx
	movq	(%rdi), %rax
	addq	-24(%rax), %rbx
	jmp	.LBB6_3
.LBB6_1:
	xorl	%ebx, %ebx
.LBB6_3:
	callq	_ZN8WideRoot4infoEv
	movq	%rax, %r9
	movq	16(%rbx), %rcx
	movq	24(%rbx), %r8
	xorl	%edx, %edx
	divq	%r8
	movq	(%rcx,%rdx,8), %rax
	testq	%rax, %rax
	je	.LBB6_10
# %bb.4:
	movq	(%rax), %rbx
	cmpq	%r9, 8(%rbx)
	je	.LBB6_9
# %bb.5:
	movq	%rdx, %rsi
	.p2align	4, 0x90
.LBB6_7:                                # =>This Inner Loop Header: Depth=1
	movq	%rbx, %rcx
	movq	(%rbx), %rbx
	testq	%rbx, %rbx
	je	.LBB6_10
# %bb.8:                                #   in Loop: Header=BB6_7 Depth=1
	movq	8(%rbx), %rdi
	movq	%rdi, %rax
	xorl	%edx, %edx
	divq	%r8
	cmpq	%rsi, %rdx
	jne	.LBB6_10
# %bb.6:                                #   in Loop: Header=BB6_7 Depth=1
	cmpq	%rdi, %r9
	jne	.LBB6_7
# %bb.12:
	testq	%rcx, %rcx
	je	.LBB6_10
.LBB6_13:
	movq	16(%rbx), %rax
	movq	%rax, 8(%rsp)
	testq	%rax, %rax
	je	.LBB6_11
# %bb.14:
	#APP
	#NO_APP
	movq	8(%rsp), %rax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB6_9:
	.cfi_def_cfa_offset 32
	testq	%rbx, %rbx
	jne	.LBB6_13
.LBB6_10:
	movq	$0, 8(%rsp)
.LBB6_11:
	callq	abort
.Lfunc_end6:
	.size	_Z13__myrtti_castI8WideRootP9WideFinalEPT_T0_, .Lfunc_end6-_Z13__myrtti_castI8WideRootP9WideFinalEPT_T0_
	.cfi_endproc