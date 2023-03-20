# MyRTTI Solution
*This is a C++ RTTI solution with full access to classes hierarchy and minimum
addional coding for classes definition.*

This solution assumes single declaration point principle. So, there is only one
point in code you mark class as a runtime:
* No need to put extracode in .cpp files
* No need to edit parent class
* Minimal extra code in the beginning of child class
* No need to put extra code in class constructors or other methods

## Some existing RTTI solutions
* LLVM, classof - This is a very simple and fast RTTI solution.

   (*details: [LLVM-style RTTI, Basic Setup](https://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html#basic-setup)*)
   * Pros
      * Very fast casting (single comparison CPU instruction)
      * Very simple tools usage, once you implemented class properly
   * Cons:
      * Extra coding in parent and child:
         * You have to extend enum with child class codes in RTTI root class
         * In child constructors you should pass this enum value to a parent
      * It doesn't support full class hierarchy. Having pointer to rtti root
         you only can get access to top-most child class.
      * Can't be used if final hierarchy is not known. For example root is
         defined in library, whilst children is to be defined is yet-unknown
         library-user apps.
* LLVM, RTTIExtend

   (*details: [LLVM-style RTTI, RTTI for Open Class Hierarchies](https://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html#rtti-for-open-class-hierarchies)*)
   * Pros:
      * Much easier to design children:
         1. Inherit from RTTIExtends.
         2. Setup `child::ID` static variable.
   * Cons:
      * Still doesn't support hierarchy, but potentially it might be improved though.
      * You still have to keep track of extra `child::ID`.
* XNU, OSMetaClass

   (*details: [IOKit Funamentals -> Runtime Type Information (OSMetaClass)](https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/IOKitFundamentals/BaseClasses/BaseClasses.html#//apple_ref/doc/uid/TP0000016-CJBFJECG)*)
   * TODO
* UnrealEngine, UObject

   (*details: [UE Documentation, Objects](https://docs.unrealengine.com/5.1/en-US/objects-in-unreal-engine/))
   * TODO
