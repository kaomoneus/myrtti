_ZN8DeepRoot4infoEv:                    # @_ZN8DeepRoot4infoEv
.Lfunc_begin5:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception5
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
	.cfi_def_cfa_offset 32
	.cfi_offset %rbx, -16
	movb	_ZGVZN8DeepRoot4infoEvE1v(%rip), %al
	testb	%al, %al
	je	.LBB11_1
.LBB11_11:
	movl	$_ZZN8DeepRoot4infoEvE1v, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB11_1:
	.cfi_def_cfa_offset 32
	movl	$_ZGVZN8DeepRoot4infoEvE1v, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB11_11
# %bb.2:
	movb	_ZGVZN6myrtti6Object4infoEvE1v(%rip), %al
	testb	%al, %al
	je	.LBB11_3
.LBB11_6:
	movq	$_ZZN6myrtti6Object4infoEvE1v, 8(%rsp)
	movq	$.L.str.46, _ZZN8DeepRoot4infoEvE1v(%rip)
	movabsq	$-3629607118424242772, %rax # imm = 0xCDA10B8E681805AC
	movq	%rax, _ZZN8DeepRoot4infoEvE1v+8(%rip)
	movb	_ZGVZN6myrtti9Hierarchy8instanceEvE1h(%rip), %al
	testb	%al, %al
	je	.LBB11_7
.LBB11_9:
.Ltmp18:
	leaq	8(%rsp), %rdx
	movl	$_ZZN6myrtti9Hierarchy8instanceEvE1h, %edi
	movl	$_ZZN8DeepRoot4infoEvE1v, %esi
	callq	_ZN6myrtti9Hierarchy3addISt5arrayIPKNS_9ClassInfoELm1EEEEvS5_RKT_
.Ltmp19:
# %bb.10:
	movl	$_ZGVZN8DeepRoot4infoEvE1v, %edi
	callq	__cxa_guard_release
	movl	$_ZZN8DeepRoot4infoEvE1v, %eax
	addq	$16, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	retq
.LBB11_3:
	.cfi_def_cfa_offset 32
	movl	$_ZGVZN6myrtti6Object4infoEvE1v, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB11_6
# %bb.4:
.Ltmp15:
	movabsq	$-751586095086458297, %rdx # imm = 0xF591D46DB83FAA47
	movl	$_ZZN6myrtti6Object4infoEvE1v, %edi
	movl	$.L.str.45, %esi
	callq	_ZN6myrtti9ClassInfoC2EPKcNS_10class_id_tE
.Ltmp16:
# %bb.5:
	movl	$_ZGVZN6myrtti6Object4infoEvE1v, %edi
	callq	__cxa_guard_release
	jmp	.LBB11_6
.LBB11_7:
	movl	$_ZGVZN6myrtti9Hierarchy8instanceEvE1h, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB11_9
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
	jmp	.LBB11_9
.LBB11_14:
.Ltmp17:
	movq	%rax, %rbx
	movl	$_ZGVZN6myrtti6Object4infoEvE1v, %edi
	callq	__cxa_guard_abort
	jmp	.LBB11_13
.LBB11_12:
.Ltmp20:
	movq	%rax, %rbx
.LBB11_13:
	movl	$_ZGVZN8DeepRoot4infoEvE1v, %edi
	callq	__cxa_guard_abort
	movq	%rbx, %rdi
	callq	_Unwind_Resume
.Lfunc_end11:
	.size	_ZN8DeepRoot4infoEv, .Lfunc_end11-_ZN8DeepRoot4infoEv
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table11:
.Lexception5:
	.byte	255                     # @LPStart Encoding = omit
	.byte	255                     # @TType Encoding = omit
	.byte	1                       # Call site Encoding = uleb128
	.uleb128 .Lcst_end5-.Lcst_begin5
.Lcst_begin5:
	.uleb128 .Ltmp18-.Lfunc_begin5  # >> Call Site 1 <<
	.uleb128 .Ltmp19-.Ltmp18        #   Call between .Ltmp18 and .Ltmp19
	.uleb128 .Ltmp20-.Lfunc_begin5  #     jumps to .Ltmp20
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp15-.Lfunc_begin5  # >> Call Site 2 <<
	.uleb128 .Ltmp16-.Ltmp15        #   Call between .Ltmp15 and .Ltmp16
	.uleb128 .Ltmp17-.Lfunc_begin5  #     jumps to .Ltmp17
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp16-.Lfunc_begin5  # >> Call Site 3 <<
	.uleb128 .Lfunc_end11-.Ltmp16   #   Call between .Ltmp16 and .Lfunc_end11
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
.Lcst_end5:
	.p2align	2