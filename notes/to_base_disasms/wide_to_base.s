_Z10wideToBaseRN9benchmark5StateE:      # @_Z10wideToBaseRN9benchmark5StateE
.Lfunc_begin2:
	.cfi_startproc
	.cfi_personality 3, __gxx_personality_v0
	.cfi_lsda 3, .Lexception2
# %bb.0:
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset %rbx, -16
	movb	_ZGVZN16BenchmarkContext8instanceEvE3ctx(%rip), %al
	testb	%al, %al
	je	.LBB5_1
.LBB5_4:
	movq	_ZZN16BenchmarkContext8instanceEvE3ctx+24(%rip), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	_Z13__myrtti_castI8WideRootP9WideFinalEPT_T0_ # TAILCALL
.LBB5_1:
	.cfi_def_cfa_offset 16
	movl	$_ZGVZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	__cxa_guard_acquire
	testl	%eax, %eax
	je	.LBB5_4
# %bb.2:
.Ltmp6:
	movl	$_ZZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	_ZN21BenchmarkContextTrait5setupEv
.Ltmp7:
# %bb.3:
	movl	$_ZN16BenchmarkContextD2Ev, %edi
	movl	$_ZZN16BenchmarkContext8instanceEvE3ctx, %esi
	movl	$__dso_handle, %edx
	callq	__cxa_atexit
	movl	$_ZGVZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	__cxa_guard_release
	movq	_ZZN16BenchmarkContext8instanceEvE3ctx+24(%rip), %rdi
	popq	%rbx
	.cfi_def_cfa_offset 8
	jmp	_Z13__myrtti_castI8WideRootP9WideFinalEPT_T0_ # TAILCALL
.LBB5_5:
	.cfi_def_cfa_offset 16
.Ltmp8:
	movq	%rax, %rbx
	movl	$_ZGVZN16BenchmarkContext8instanceEvE3ctx, %edi
	callq	__cxa_guard_abort
	movq	%rbx, %rdi
	callq	_Unwind_Resume
.Lfunc_end5:
	.size	_Z10wideToBaseRN9benchmark5StateE, .Lfunc_end5-_Z10wideToBaseRN9benchmark5StateE
	.cfi_endproc
	.section	.gcc_except_table,"a",@progbits
	.p2align	2
GCC_except_table5:
.Lexception2:
	.byte	255                     # @LPStart Encoding = omit
	.byte	255                     # @TType Encoding = omit
	.byte	1                       # Call site Encoding = uleb128
	.uleb128 .Lcst_end2-.Lcst_begin2
.Lcst_begin2:
	.uleb128 .Lfunc_begin2-.Lfunc_begin2 # >> Call Site 1 <<
	.uleb128 .Ltmp6-.Lfunc_begin2   #   Call between .Lfunc_begin2 and .Ltmp6
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp6-.Lfunc_begin2   # >> Call Site 2 <<
	.uleb128 .Ltmp7-.Ltmp6          #   Call between .Ltmp6 and .Ltmp7
	.uleb128 .Ltmp8-.Lfunc_begin2   #     jumps to .Ltmp8
	.byte	0                       #   On action: cleanup
	.uleb128 .Ltmp7-.Lfunc_begin2   # >> Call Site 3 <<
	.uleb128 .Lfunc_end5-.Ltmp7     #   Call between .Ltmp7 and .Lfunc_end5
	.byte	0                       #     has no landing pad
	.byte	0                       #   On action: cleanup
.Lcst_end2:
	.p2align	2