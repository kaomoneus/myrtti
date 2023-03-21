# MyRTTI Solution
*This is a C++ RTTI solution with full access to classes hierarchy and minimum
addional coding for classes definition.*

## The problem (aka the Goal of RTTI)
TODO

## About our solution
This solution assumes single declaration point principle. So, there is only one
point in code you mark class as a runtime:
* No need to put extracode in .cpp files
* No need to edit parent class
* Minimal extra code in the beginning of child class
* No need to put extra code in class constructors or other methods


## Some existing RTTI solutions
### LLVM, classof - This is a very simple and fast RTTI solution.

   (*details: [LLVM-style RTTI, Basic Setup](https://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html#basic-setup)*)

   ```c++
   class Shape {
   public:
      /// Discriminator for LLVM-style RTTI (dyn_cast<> et al.)
      enum ShapeKind {
         SK_Square,
         SK_Circle
      };
   private:
      const ShapeKind Kind;
   public:
      ShapeKind getKind() const { return Kind; }
      Shape(ShapeKind K) : Kind(K) {}

      // class body
   };

   class Square : public Shape {
      double SideLength;
   public:
      Square(double S) : Shape(SK_Square), SideLength(S) {}

      // class body
   };

   void usage() {
      Shape *S = ...;

      // "isa" picks S->Kind and compares it with SK_Circle
      if (isa<Circle>(S)) {/* do something ... */}
   }
   ```

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
### LLVM, RTTIExtend
   (*details: [LLVM-style RTTI, RTTI for Open Class Hierarchies](https://llvm.org/docs/HowToSetUpLLVMStyleRTTI.html#rtti-for-open-class-hierarchies)*)


   ```c++
   template <typename ThisT, typename ParentT>
   class RTTIExtends : public ParentT {
   public:
      // Inherit constructors from ParentT.
      using ParentT::ParentT;
      static const void *classID() { return &ThisT::ID; }
      const void *dynamicClassID() const override { return &ThisT::ID; }

      bool isA(const void *const ClassID) const override {
         return ClassID == classID() || ParentT::isA(ClassID);
      }
   };

   class Shape : public RTTIExtends<Shape, RTTIRoot> {
   public:
      static char ID;
      // class body
   };

   class Square : public RTTIExtends<Square, Shape> {
   public:
      static char ID;
      // class body
   };

   char Shape::ID = 0;
   char Square::ID = 1;
   ```

   * Pros:
      * Much easier to design children:
         1. Inherit from RTTIExtends.
         2. Setup `child::ID` static variable.
   * Cons:
      * Still doesn't support hierarchy, but potentially it might be improved though.
      * You still have to keep track of extra `child::ID`.
### XNU, OSMetaClass

   (*details: [IOKit Funamentals -> Runtime Type Information (OSMetaClass)](https://developer.apple.com/library/archive/documentation/DeviceDrivers/Conceptual/IOKitFundamentals/BaseClasses/BaseClasses.html#//apple_ref/doc/uid/TP0000016-CJBFJECG)*)

   Introduces two macros (complicated ones):
   * `OSDeclareDefaultStructors` - generates constructor prototype
   which accepts child class name.
   * `OSDefineMetaClassWithInit` - accepts className and superClass,
   resolves link to superClass meta information and stores it in childClass instance.

   Usage:
   ```c++
   // .h
   class MyDriver : public IOEthernetController
   {
      OSDeclareDefaultStructors(MyDriver);
      // class body
   };

   // .cpp

   #include "MyDriver.h"
   OSDefineMetaClassAndStructors(MyDriver, IOEthernetController);

   // rest of definitions
   ```

   * Pros:
      * No need to update parent classes.
      * Keeps hierarchy
   * Cons:
      * You still need to put extra code in two places: .h and .cpp
      * Multiple inharitance is not supported

### UnrealEngine, UObject

   Uses additional code generator which injects class hierarchy into class static fields, injects type information during instance construction.

   ```c++
   // .h
   #pragma once

   #include 'Object.h'
   #include 'MyObject.generated.h'
   UCLASS()
   class MYPROJECT_API UMyObject : public UObject
   {
      GENERATED_BODY()
   };

   // .cpp
   // ...
   void usage() {
      UClass* ClassA = UDamageType::StaticClass();

      TSubclassOf<UDamageType> ClassB;

      // Performs a runtime check
      ClassB = ClassA;
   }
   ```

   (*details: [UE Documentation, Objects](https://docs.unrealengine.com/5.1/en-US/objects-in-unreal-engine/)*)
   * Pros:
      * Keeps hierarchy.
      * All RTTI-related definitions are gathered in .h file.
   * Cons:
      * It it uses extra code generator to maintain RTTI stuff.
      * Proprietary, and we only can suppose what's behind some macros.
