_ZN8WideRoot4infoEv:                    # @_ZN8WideRoot4infoEv
.Lfunc_begin6:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception6
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movb	_ZGVZN8WideRoot4infoEvE1v(%rip), %al
	testb	%al, %al
	je	.LBB13_1
.LBB13_11:
	movl	$_ZZN8WideRoot4infoEvE1v, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB13_1:
	.cfi_def_cfa_offset 32
	movl	$_ZGVZN8WideRoot4infoEvE1v, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB13_11
# %bb.2:
	movb	_ZGVZN6myrtti6Object4infoEvE1v(%rip), %al
	testb	%al, %al
	je	.LBB13_3
.LBB13_6:
	movq	$_ZZN6myrtti6Object4infoEvE1v, 8(%rsp)
	movq	$.L.str.47, _ZZN8WideRoot4infoEvE1v(%rip)
	movabsq	$-2120594854850669430, %rax # imm = 0xE2922237041AD48A
	movq	%rax, _ZZN8WideRoot4infoEvE1v+8(%rip)
	movb	_ZGVZN6myrtti9Hierarchy8instanceEvE1h(%rip), %al
	testb	%al, %al
	je	.LBB13_7
.LBB13_9:
.Ltmp24:
	leaq	8(%rsp), %rdx
	movl	$_ZZN6myrtti9Hierarchy8instanceEvE1h, %edi
	movl	$_ZZN8WideRoot4infoEvE1v, %esi
	callq	_ZN6myrtti9Hierarchy3addISt5arrayIPKNS_9ClassInfoELm1EEEEvS5_RKT_
.Ltmp25:
# %bb.10:
	movl	$_ZGVZN8WideRoot4infoEvE1v, %edi
	callq	__cxa_guard_release
	movl	$_ZZN8WideRoot4infoEvE1v, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB13_3:
	.cfi_def_cfa_offset 32
	movl	$_ZGVZN6myrtti6Object4infoEvE1v, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB13_6
# %bb.4:
.Ltmp21:
	movabsq	$-751586095086458297, %rdx # imm = 0xF591D46DB83FAA47
	movl	$_ZZN6myrtti6Object4infoEvE1v, %edi
	movl	$.L.str.45, %esi
	callq	_ZN6myrtti9ClassInfoC2EPKcNS_10class_id_tE
.Ltmp22:
# %bb.5:
	movl	$_ZGVZN6myrtti6Object4infoEvE1v, %edi
	callq	__cxa_guard_release
	jmp	.LBB13_6
.LBB13_7:
	movl	$_ZGVZN6myrtti9Hierarchy8instanceEvE1h, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB13_9
# %bb.8:
	movq	$_ZZN6myrtti9Hierarchy8instanceEvE1h+48, _ZZN6myrtti9Hierarchy8instanceEvE1h(%rip)
	movq	$1, _ZZN6myrtti9Hierarchy8instanceEvE1h+8(%rip)
	xorps	%xmm0, %xmm0
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+16(%rip)
	movl	$1065353216, _ZZN6myrtti9Hierarchy8instanceEvE1h+32(%rip) # imm = 0x3F800000
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+40(%rip)
	movq	$_ZZN6myrtti9Hierarchy8instanceEvE1h+104, _ZZN6myrtti9Hierarchy8instanceEvE1h+56(%rip)
	movq	$1, _ZZN6myrtti9Hierarchy8instanceEvE1h+64(%rip)
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+72(%rip)
	movl	$1065353216, _ZZN6myrtti9Hierarchy8instanceEvE1h+88(%rip) # imm = 0x3F800000
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+96(%rip)
	movq	$_ZZN6myrtti9Hierarchy8instanceEvE1h+160, _ZZN6myrtti9Hierarchy8instanceEvE1h+112(%rip)
	movq	$1, _ZZN6myrtti9Hierarchy8instanceEvE1h+120(%rip)
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+128(%rip)
	movl	$1065353216, _ZZN6myrtti9Hierarchy8instanceEvE1h+144(%rip) # imm = 0x3F800000
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+152(%rip)
	movq	$_ZZN6myrtti9Hierarchy8instanceEvE1h+216, _ZZN6myrtti9Hierarchy8instanceEvE1h+168(%rip)
	movq	$1, _ZZN6myrtti9Hierarchy8instanceEvE1h+176(%rip)
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+184(%rip)
	movl	$1065353216, _ZZN6myrtti9Hierarchy8instanceEvE1h+200(%rip) # imm = 0x3F800000
	movups	%xmm0, _ZZN6myrtti9Hierarchy8instanceEvE1h+208(%rip)
	movl	$_ZN6myrtti9HierarchyD2Ev, %edi
	movl	$_ZZN6myrtti9Hierarchy8instanceEvE1h, %esi
	movl	$__dso_handle, %edx
	callq	__cxa_atexit
	movl	$_ZGVZN6myrtti9Hierarchy8instanceEvE1h, %edi
	callq	__cxa_guard_release
	jmp	.LBB13_9
.LBB13_14:
.Ltmp23:
	movq	%rax, %rbx
	movl	$_ZGVZN6myrtti6Object4infoEvE1v, %edi
	callq	__cxa_guard_abort
	jmp	.LBB13_13
.LBB13_12:
.Ltmp26:
	movq	%rax, %rbx
.LBB13_13:
	movl	$_ZGVZN8WideRoot4infoEvE1v, %edi
	callq	__cxa_guard_abort
	movq	%rbx, %rdi
	callq	_Unwind_Resume
.Lfunc_end13:
	.size	_ZN8WideRoot4infoEv, .Lfunc_end13-_ZN8WideRoot4infoEv
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table13:
.Lexception6:
	.byte	255                     # @LPStart Encoding = omit
	.byte	255                     # @TType Encoding = omit
	.byte	1                       # Call site Encoding = uleb128
	.uleb128 .Lcst_end6-.Lcst_begin6
.Lcst_begin6:
	.uleb128 .Ltmp24-.Lfunc_begin6  # >> Call Site 1 <<
	.uleb128 .Ltmp25-.Ltmp24        #   Call between .Ltmp24 and .Ltmp25
	.uleb128 .Ltmp26-.Lfunc_begin6  #     jumps to .Ltmp26
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp21-.Lfunc_begin6  # >> Call Site 2 <<
	.uleb128 .Ltmp22-.Ltmp21        #   Call between .Ltmp21 and .Ltmp22
	.uleb128 .Ltmp23-.Lfunc_begin6  #     jumps to .Ltmp23
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp22-.Lfunc_begin6  # >> Call Site 3 <<
	.uleb128 .Lfunc_end13-.Ltmp22   #   Call between .Ltmp22 and .Lfunc_end13
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
.Lcst_end6:
	.p2align	2