define linkonce_odr dso_local %struct.DeepRoot* @_Z13__myrtti_castI8DeepRootP9DeepFinalEPT_T0_(%struct.DeepFinal* %0) local_unnamed_addr #4 comdat personality i32 (...)* @__gxx_personality_v0 {
  %2 = alloca %struct.DeepRoot*, align 8
  %3 = bitcast %struct.DeepRoot** %2 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %3) #17
  %4 = icmp eq %struct.DeepFinal* %0, null
  br i1 %4, label %14, label %5

5:                                                ; preds = %1
  %6 = bitcast %struct.DeepFinal* %0 to i8**
  %7 = load i8*, i8** %6, align 8, !tbaa !10
  %8 = getelementptr i8, i8* %7, i64 -24
  %9 = bitcast i8* %8 to i64*
  %10 = load i64, i64* %9, align 8
  %11 = bitcast %struct.DeepFinal* %0 to i8*
  %12 = getelementptr inbounds i8, i8* %11, i64 %10
  %13 = bitcast i8* %12 to %"struct.myrtti::Object"*
  br label %14

14:                                               ; preds = %5, %1
  %15 = phi %"struct.myrtti::Object"* [ %13, %5 ], [ null, %1 ]
  %16 = tail call %"struct.myrtti::ClassInfo"* @_ZN8DeepRoot4infoEv()
  %17 = ptrtoint %"struct.myrtti::ClassInfo"* %16 to i64
  %18 = getelementptr inbounds %"struct.myrtti::Object", %"struct.myrtti::Object"* %15, i64 0, i32 2, i32 0, i32 1
  %19 = load i64, i64* %18, align 8, !tbaa !12
  %20 = urem i64 %17, %19
  %21 = getelementptr inbounds %"struct.myrtti::Object", %"struct.myrtti::Object"* %15, i64 0, i32 2, i32 0, i32 0
  %22 = load %"struct.std::__detail::_Hash_node_base"**, %"struct.std::__detail::_Hash_node_base"*** %21, align 8, !tbaa !18
  %23 = getelementptr inbounds %"struct.std::__detail::_Hash_node_base"*, %"struct.std::__detail::_Hash_node_base"** %22, i64 %20
  %24 = load %"struct.std::__detail::_Hash_node_base"*, %"struct.std::__detail::_Hash_node_base"** %23, align 8, !tbaa !19
  %25 = icmp eq %"struct.std::__detail::_Hash_node_base"* %24, null
  br i1 %25, label %53, label %26

26:                                               ; preds = %14
  %27 = bitcast %"struct.std::__detail::_Hash_node_base"* %24 to %"struct.std::__detail::_Hash_node"**
  %28 = load %"struct.std::__detail::_Hash_node"*, %"struct.std::__detail::_Hash_node"** %27, align 8, !tbaa !20
  %29 = getelementptr inbounds %"struct.std::__detail::_Hash_node", %"struct.std::__detail::_Hash_node"* %28, i64 0, i32 0, i32 1
  %30 = bitcast %"struct.__gnu_cxx::__aligned_buffer"* %29 to %"struct.myrtti::ClassInfo"**
  %31 = load %"struct.myrtti::ClassInfo"*, %"struct.myrtti::ClassInfo"** %30, align 8, !tbaa !19
  %32 = icmp eq %"struct.myrtti::ClassInfo"* %31, %16
  br i1 %32, label %51, label %36

33:                                               ; preds = %42
  %34 = inttoptr i64 %45 to %"struct.myrtti::ClassInfo"*
  %35 = icmp eq %"struct.myrtti::ClassInfo"* %16, %34
  br i1 %35, label %48, label %36

36:                                               ; preds = %26, %33
  %37 = phi %"struct.std::__detail::_Hash_node"* [ %41, %33 ], [ %28, %26 ]
  %38 = getelementptr inbounds %"struct.std::__detail::_Hash_node", %"struct.std::__detail::_Hash_node"* %37, i64 0, i32 0, i32 0, i32 0
  %39 = load %"struct.std::__detail::_Hash_node_base"*, %"struct.std::__detail::_Hash_node_base"** %38, align 8, !tbaa !20
  %40 = icmp eq %"struct.std::__detail::_Hash_node_base"* %39, null
  %41 = bitcast %"struct.std::__detail::_Hash_node_base"* %39 to %"struct.std::__detail::_Hash_node"*
  br i1 %40, label %53, label %42

42:                                               ; preds = %36
  %43 = getelementptr inbounds %"struct.std::__detail::_Hash_node_base", %"struct.std::__detail::_Hash_node_base"* %39, i64 1
  %44 = bitcast %"struct.std::__detail::_Hash_node_base"* %43 to i64*
  %45 = load i64, i64* %44, align 8, !tbaa !19
  %46 = urem i64 %45, %19
  %47 = icmp eq i64 %46, %20
  br i1 %47, label %33, label %53

48:                                               ; preds = %33
  %49 = bitcast %"struct.std::__detail::_Hash_node_base"* %39 to %"struct.std::__detail::_Hash_node"*
  %50 = icmp eq %"struct.std::__detail::_Hash_node"* %37, null
  br i1 %50, label %53, label %54

51:                                               ; preds = %26
  %52 = icmp eq %"struct.std::__detail::_Hash_node"* %28, null
  br i1 %52, label %53, label %54

53:                                               ; preds = %42, %36, %14, %48, %51
  store %struct.DeepRoot* null, %struct.DeepRoot** %2, align 8, !tbaa !19
  br label %60

54:                                               ; preds = %48, %51
  %55 = phi %"struct.std::__detail::_Hash_node"* [ %49, %48 ], [ %28, %51 ]
  %56 = getelementptr inbounds %"struct.std::__detail::_Hash_node", %"struct.std::__detail::_Hash_node"* %55, i64 0, i32 0, i32 1, i32 0, i32 0, i64 8
  %57 = bitcast i8* %56 to %struct.DeepRoot**
  %58 = load %struct.DeepRoot*, %struct.DeepRoot** %57, align 8, !tbaa !21
  store %struct.DeepRoot* %58, %struct.DeepRoot** %2, align 8, !tbaa !19
  %59 = icmp eq %struct.DeepRoot* %58, null
  br i1 %59, label %60, label %61

60:                                               ; preds = %53, %54
  tail call void @abort() #18
  unreachable

61:                                               ; preds = %54
  call void asm sideeffect "", "=*r|m,0,~{memory},~{dirflag},~{fpsr},~{flags}"(%struct.DeepRoot** nonnull %2, %struct.DeepRoot* nonnull %58) #17, !srcloc !23
  %62 = load %struct.DeepRoot*, %struct.DeepRoot** %2, align 8, !tbaa !19
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %3) #17
  ret %struct.DeepRoot* %62
}