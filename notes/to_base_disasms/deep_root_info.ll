define linkonce_odr dso_local %"struct.myrtti::ClassInfo"* @_ZN8DeepRoot4infoEv() local_unnamed_addr #2 comdat align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %1 = alloca %"struct.std::array", align 8
  %2 = load atomic i8, i8* bitcast (i64* @_ZGVZN8DeepRoot4infoEvE1v to i8*) acquire, align 8
  %3 = icmp eq i8 %2, 0
  br i1 %3, label %4, label %29, !prof !6

4:                                                ; preds = %0
  %5 = tail call i32 @__cxa_guard_acquire(i64* nonnull @_ZGVZN8DeepRoot4infoEvE1v) #17
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %29, label %7

7:                                                ; preds = %4
  %8 = bitcast %"struct.std::array"* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %8) #17
  %9 = load atomic i8, i8* bitcast (i64* @_ZGVZN6myrtti6Object4infoEvE1v to i8*) acquire, align 8
  %10 = icmp eq i8 %9, 0
  br i1 %10, label %11, label %18, !prof !6

11:                                               ; preds = %7
  %12 = tail call i32 @__cxa_guard_acquire(i64* nonnull @_ZGVZN6myrtti6Object4infoEvE1v) #17
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %18, label %14

14:                                               ; preds = %11
  invoke void @_ZN6myrtti9ClassInfoC2EPKcNS_10class_id_tE(%"struct.myrtti::ClassInfo"* nonnull @_ZZN6myrtti6Object4infoEvE1v, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.45, i64 0, i64 0), i64 -751586095086458297)
          to label %15 unwind label %16

15:                                               ; preds = %14
  tail call void @__cxa_guard_release(i64* nonnull @_ZGVZN6myrtti6Object4infoEvE1v) #17
  br label %18

16:                                               ; preds = %14
  %17 = landingpad { i8*, i32 }
          cleanup
  tail call void @__cxa_guard_abort(i64* nonnull @_ZGVZN6myrtti6Object4infoEvE1v) #17
  br label %32

18:                                               ; preds = %15, %11, %7
  %19 = getelementptr inbounds %"struct.std::array", %"struct.std::array"* %1, i64 0, i32 0, i64 0
  store %"struct.myrtti::ClassInfo"* @_ZZN6myrtti6Object4infoEvE1v, %"struct.myrtti::ClassInfo"** %19, align 8
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.46, i64 0, i64 0), i8** getelementptr inbounds (%"struct.myrtti::ClassInfo", %"struct.myrtti::ClassInfo"* @_ZZN8DeepRoot4infoEvE1v, i64 0, i32 0), align 8, !tbaa !26
  store i64 -3629607118424242772, i64* getelementptr inbounds (%"struct.myrtti::ClassInfo", %"struct.myrtti::ClassInfo"* @_ZZN8DeepRoot4infoEvE1v, i64 0, i32 1, i32 0), align 8, !tbaa.struct !29
  %20 = load atomic i8, i8* bitcast (i64* @_ZGVZN6myrtti9Hierarchy8instanceEvE1h to i8*) acquire, align 8
  %21 = icmp eq i8 %20, 0
  br i1 %21, label %22, label %27, !prof !6

22:                                               ; preds = %18
  %23 = tail call i32 @__cxa_guard_acquire(i64* nonnull @_ZGVZN6myrtti9Hierarchy8instanceEvE1h) #17
  %24 = icmp eq i32 %23, 0
  br i1 %24, label %27, label %25

25:                                               ; preds = %22
  store %"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 0, i32 0, i32 5), %"struct.std::__detail::_Hash_node_base"*** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 0, i32 0, i32 0), align 8, !tbaa !31
  store i64 1, i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 0, i32 0, i32 1), align 8, !tbaa !33
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (%"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 0, i32 0, i32 2, i32 0) to i8*), i8 0, i64 16, i1 false) #17
  store float 1.000000e+00, float* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 0, i32 0, i32 4, i32 0), align 8, !tbaa !34
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 0, i32 0, i32 4, i32 1) to i8*), i8 0, i64 16, i1 false) #17
  store %"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 1, i32 0, i32 5), %"struct.std::__detail::_Hash_node_base"*** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 1, i32 0, i32 0), align 8, !tbaa !31
  store i64 1, i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 1, i32 0, i32 1), align 8, !tbaa !33
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (%"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 1, i32 0, i32 2, i32 0) to i8*), i8 0, i64 16, i1 false) #17
  store float 1.000000e+00, float* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 1, i32 0, i32 4, i32 0), align 8, !tbaa !34
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 1, i32 0, i32 4, i32 1) to i8*), i8 0, i64 16, i1 false) #17
  store %"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 2, i32 0, i32 5), %"struct.std::__detail::_Hash_node_base"*** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 2, i32 0, i32 0), align 8, !tbaa !35
  store i64 1, i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 2, i32 0, i32 1), align 8, !tbaa !37
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (%"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 2, i32 0, i32 2, i32 0) to i8*), i8 0, i64 16, i1 false) #17
  store float 1.000000e+00, float* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 2, i32 0, i32 4, i32 0), align 8, !tbaa !34
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 0, i32 2, i32 0, i32 4, i32 1) to i8*), i8 0, i64 16, i1 false) #17
  store %"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 1, i32 0, i32 5), %"struct.std::__detail::_Hash_node_base"*** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 1, i32 0, i32 0), align 8, !tbaa !38
  store i64 1, i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 1, i32 0, i32 1), align 8, !tbaa !40
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (%"struct.std::__detail::_Hash_node_base"** getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 1, i32 0, i32 2, i32 0) to i8*), i8 0, i64 16, i1 false) #17
  store float 1.000000e+00, float* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 1, i32 0, i32 4, i32 0), align 8, !tbaa !34
  tail call void @llvm.memset.p0i8.i64(i8* nonnull align 8 dereferenceable(16) bitcast (i64* getelementptr inbounds (%"struct.myrtti::Hierarchy", %"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h, i64 0, i32 1, i32 0, i32 4, i32 1) to i8*), i8 0, i64 16, i1 false) #17
  %26 = tail call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"struct.myrtti::Hierarchy"*)* @_ZN6myrtti9HierarchyD2Ev to void (i8*)*), i8* bitcast (%"struct.myrtti::Hierarchy"* @_ZZN6myrtti9Hierarchy8instanceEvE1h to i8*), i8* nonnull @__dso_handle) #17
  tail call void @__cxa_guard_release(i64* nonnull @_ZGVZN6myrtti9Hierarchy8instanceEvE1h) #17
  br label %27

27:                                               ; preds = %25, %22, %18
  invoke void @_ZN6myrtti9Hierarchy3addISt5arrayIPKNS_9ClassInfoELm1EEEEvS5_RKT_(%"struct.myrtti::Hierarchy"* nonnull @_ZZN6myrtti9Hierarchy8instanceEvE1h, %"struct.myrtti::ClassInfo"* nonnull @_ZZN8DeepRoot4infoEvE1v, %"struct.std::array"* nonnull dereferenceable(8) %1)
          to label %28 unwind label %30

28:                                               ; preds = %27
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %8) #17
  call void @__cxa_guard_release(i64* nonnull @_ZGVZN8DeepRoot4infoEvE1v) #17
  br label %29

29:                                               ; preds = %4, %28, %0
  ret %"struct.myrtti::ClassInfo"* @_ZZN8DeepRoot4infoEvE1v

30:                                               ; preds = %27
  %31 = landingpad { i8*, i32 }
          cleanup
  br label %32

32:                                               ; preds = %16, %30
  %33 = phi { i8*, i32 } [ %31, %30 ], [ %17, %16 ]
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %8) #17
  call void @__cxa_guard_abort(i64* nonnull @_ZGVZN8DeepRoot4infoEvE1v) #17
  resume { i8*, i32 } %33
}