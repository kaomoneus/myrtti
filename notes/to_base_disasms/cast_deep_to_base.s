_Z13__myrtti_castI8DeepRootP9DeepFinalEPT_T0_: # @_Z13__myrtti_castI8DeepRootP9DeepFinalEPT_T0_
	.cfi_startproc
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	testq	%rdi, %rdi
	je	.LBB2_1
# %bb.2:
	movq	%rdi, %rbx
	movq	(%rdi), %rax
	addq	-24(%rax), %rbx
	jmp	.LBB2_3
.LBB2_1:
	xorl	%ebx, %ebx
.LBB2_3:
	callq	_ZN8DeepRoot4infoEv
	movq	%rax, %r9
	movq	16(%rbx), %rcx
	movq	24(%rbx), %r8
	xorl	%edx, %edx
	divq	%r8
	movq	(%rcx,%rdx,8), %rax
	testq	%rax, %rax
	je	.LBB2_10
# %bb.4:
	movq	(%rax), %rbx
	cmpq	%r9, 8(%rbx)
	je	.LBB2_9
# %bb.5:
	movq	%rdx, %rsi
	.p2align	4, 0x90
.LBB2_7:                                # =>This Inner Loop Header: Depth=1
	movq	%rbx, %rcx
	movq	(%rbx), %rbx
	testq	%rbx, %rbx
	je	.LBB2_10
# %bb.8:                                #   in Loop: Header=BB2_7 Depth=1
	movq	8(%rbx), %rdi
	movq	%rdi, %rax
	xorl	%edx, %edx
	divq	%r8
	cmpq	%rsi, %rdx
	jne	.LBB2_10
# %bb.6:                                #   in Loop: Header=BB2_7 Depth=1
	cmpq	%rdi, %r9
	jne	.LBB2_7
# %bb.12:
	testq	%rcx, %rcx
	je	.LBB2_10
.LBB2_13:
	movq	16(%rbx), %rax
	movq	%rax, 8(%rsp)
	testq	%rax, %rax
	je	.LBB2_11
# %bb.14:
	#APP
	#NO_APP
	movq	8(%rsp), %rax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB2_9:
	.cfi_def_cfa_offset 32
	testq	%rbx, %rbx
	jne	.LBB2_13
.LBB2_10:
	movq	$0, 8(%rsp)
.LBB2_11:
	callq	abort
.Lfunc_end2:
	.size	_Z13__myrtti_castI8DeepRootP9DeepFinalEPT_T0_, .Lfunc_end2-_Z13__myrtti_castI8DeepRootP9DeepFinalEPT_T0_
	.cfi_endproc