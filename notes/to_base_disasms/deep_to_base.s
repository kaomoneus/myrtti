_Z10deepToBaseRN9benchmark5StateE:      # @_Z10deepToBaseRN9benchmark5StateE
.Lfunc_begin0:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception0
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movb	_ZGVZN16BenchmarkContext8instanceEvE3ctx(%rip), %al
	testb	%al, %al
	je	.LBB1_1
.LBB1_4:
	movq	_ZZN16BenchmarkContext8instanceEvE3ctx(%rip), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	_Z13__myrtti_castI8DeepRootP9DeepFinalEPT_T0_ # TAILCALL
.LBB1_1:
	.cfi_def_cfa_offset 16
	movl	$_ZGVZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB1_4
# %bb.2:
.Ltmp0:
	movl	$_ZZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	_ZN21BenchmarkContextTrait5setupEv
.Ltmp1:
# %bb.3:
	movl	$_ZN16BenchmarkContextD2Ev, %edi
	movl	$_ZZN16BenchmarkContext8instanceEvE3ctx, %esi
	movl	$__dso_handle, %edx
	callq	__cxa_atexit
	movl	$_ZGVZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	__cxa_guard_release
	movq	_ZZN16BenchmarkContext8instanceEvE3ctx(%rip), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	_Z13__myrtti_castI8DeepRootP9DeepFinalEPT_T0_ # TAILCALL
.LBB1_5:
	.cfi_def_cfa_offset 16
.Ltmp2:
	movq	%rax, %rbx
	movl	$_ZGVZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	__cxa_guard_abort
	movq	%rbx, %rdi
	callq	_Unwind_Resume
.Lfunc_end1:
	.size	_Z10deepToBaseRN9benchmark5StateE, .Lfunc_end1-_Z10deepToBaseRN9benchmark5StateE
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table1:
.Lexception0:
	.byte	255                     # @LPStart Encoding = omit
	.byte	255                     # @TType Encoding = omit
	.byte	1                       # Call site Encoding = uleb128
	.uleb128 .Lcst_end0-.Lcst_begin0
.Lcst_begin0:
	.uleb128 .Lfunc_begin0-.Lfunc_begin0 # >> Call Site 1 <<
	.uleb128 .Ltmp0-.Lfunc_begin0   #   Call between .Lfunc_begin0 and .Ltmp0
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp0-.Lfunc_begin0   # >> Call Site 2 <<
	.uleb128 .Ltmp1-.Ltmp0          #   Call between .Ltmp0 and .Ltmp1
	.uleb128 .Ltmp2-.Lfunc_begin0   #     jumps to .Ltmp2
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp1-.Lfunc_begin0   # >> Call Site 3 <<
	.uleb128 .Lfunc_end1-.Ltmp1     #   Call between .Ltmp1 and .Lfunc_end1
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
.Lcst_end0:
	.p2align	2
