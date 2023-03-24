# MyRTTI Solution
*This is a C++ RTTI solution with full access to classes hierarchy and minimum
addional coding for classes definition.*

## The goals and problems of RTTI
*RTTI stands for Run-Time Type Information.*

### Goal
Assuming we have a set of pointers of some `Base*`, I want to figure out its real type and do some appropriate actions.

E.g.
```c++
void foo(Shape* obj) {
   if (isa<Circle>(obj)) {
      cout << "This is a Circle!\n";
   }
}
```

Which is more interesting I also want to make a cast, so example from above takes following form:

```c++
void foo(Shape* obj) {
   if (auto* circle = cast<Circle>(obj)) {
      circle->printWhoAmI();
   }
}
```

In order to do it we need two things:
1. For each object we should store information about its real type (aka RTTI).
   * NOTE: For proper cross-casting we also should keep track of pointers to all its parents. Assuming base class is virtual we can't use `static_cast` for converting `Shape` to `Circle` in example above.
   * NOTE#2: More over ideally it stores whole types hierarchy.
2. Also we need to assosiate the same information with each class. And we should be able to resolve it in run-time as well.
3. Going even further I want be able to *walk* through whole hierarchy. Doing this I can implement things like *visitor with fallbacks to parents*, constructor-like mechanics and many other things.

### Problem
Problem is that there is a quite restricted rtti support in C++.
* If enabled, it is applied to all classes and structures. Whilst we would prefer to disable it for traits.

   ...Or rather, we would prefer to enable it for restricted subset of classes, where we really need it.
* Even though you're able to perform cross-casts, there is still no way for simple visitor implementation.

As a conclusion whenever your aim are goals from above, you have to implement boiler plate code, add extra syntax, and sometimes even introduce additional codegen phases.

## Some existing RTTI solutions
### LLVM, classof
*A very simple and fast RTTI solution.*

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
      * Very simple tools usage (`isa`, `cast` and others), once you implemented class properly though.
   * Cons:
      * Extra coding in parent and child:
         * You have to extend enum with child class codes in RTTI root class.
         * In child constructors you should pass this enum value to a parent.
      * It doesn't support full class hierarchy. Having pointer to rtti root
         you only can get access to top-most child class.
      * Can't be used if final hierarchy is not known. For example root is
         defined in library, whilst children is to be defined is yet-unknown
         library-user apps.
### LLVM, RTTIExtend
   *An alternative to previous solution when the final hierarchy is not known*

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
      * No need to update parent classes.
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
      * No need to update parent classes.
   * Cons:
      * It it uses extra code generator to maintain RTTI stuff.
      * Proprietary, and we only can suppose what's behind some macros.

## Our solution: MyRTTI
Our solution assumes single declaration point principle. So, there is only one
point in code, where you mark class as a *runtime*:
* If you're declaring class without macros, then you put few marks in the beginning of class. There is still word "few". And yet (for each class) there is only one place where all those "few" are gathered.
* If you're mentally prepared to suffer using macros, then we can turn it into a single point indeed (see below).

So the benefits all together are:
* No need to put extracode in .cpp files
* No need to edit parent class
* Minimal extra code in the beginning of child class
* No need to put extra code in class constructors or other methods.

### Example

```c++
#include <iostream>
#include <memory>
#include <vector>

#include <myrtti.h>

struct Shape : RTTI<Shape>
{
    DEFINE_RTTI(Shape, Object);

    // class body
    // ...
};

struct Square : Shape, RTTI<Square>
{
    DEFINE_RTTI(Square, Shape);

    // class body
    // ...
};

int main() {
    vector<shared_ptr<Object>> objs = {
        make_shared<Shape>(),
        make_shared<Square>(),
    };

    for (auto &o : objs) {
        cout << "o->rtti->name = " << o->rtti->name << "\n";

        if (o->rtti == Square::info()) {
            cout << "Discovered Square\n";
        }
    }
    return 0;
}
```

As you can see all RTTI-related marks are gathered in the beginning of class
declaration. If you're not too disdained about macros we could rewrite
structure declaration with rtti into this:

```c++
RTTI_STRUCT_BEGIN(Square, (Shape /*need more parents?*/))
    // Structure body here
    // ...
    private:
    // Private members here
    // ...
RTTI_STRUCT_END()
```

Pros and cons of using such macros

Pros
* This is a real single-point definition!

Cons
* Syntax is ugly. In general such macros set supports `struct` only, because there
are issues with stripping access/virtual modifiers from parents set. We prefer RTTI parents to be *public*, whilst for `class` it is *protected* by default.

Well, anyways, in most of tasks we can live with that.

### Magic behind

Let's take a look at internals. There are few key things:

* `ClassInfo` - Describes all runtime information available for given class.
   ```c++
   struct ClassInfo {
      const char* name;
      // ...
      template<typename ArrayT>
      ClassInfo(const char* name, const ArrayT& parents) : name(name) {
         Hierarchy::instance()->add(this, parents);
      }
      // ...
   };
   ```
* `Object` - All classes with RTTI are inherited from `Object`. This is implicitly done when you inherit from `RTTI` class marker. `Object` is a place where we hold runtime type information (pointer to `ClassInfo` instance).
   ```c++
   struct Object {

      // Each descendant have its own info() static method.
      static const ClassInfo* info() {
         static ClassInfo v("Object");
         return v;
      }

      // Descendants will override rtti value.
      // Each object will have its own rtti value.
      const ClassInfo* rtti = info();

      // Cross cast implementation
      template<class T>
      T* cast() {
         auto found = this->crossPtrs.find(T::info());
         if (/*[[likely]]*/ found != end(this->crossPtrs))
               return static_cast<T*>(found->second);
         return nullptr;
      }

      template<class T> const T* cast() const {/*...*/}

   protected:
      // This friendship provides access to crossPtrs for RTTI specs.
      template<class T> friend class RTTI;

      std::unordered_map<const ClassInfo*, void*> crossPtrs;
   };
   ```
* `RTTI` - We force each class (`ClassT`) to inherit from `RTTI<ClassT>`. This template defines default constructor `RTTI()`, which:
   * intializes runtime information with `ClassInfo* ClassT::info()` call.
   * registers pointer casted to `ClassT` (at this point we can use `static_cast`), so we could do cross-casts.

   Important note: `RTTI()` is implicitly called in *all* `ClassT` constructors, and there is no need to put extracode (e.g. in .cpp files) in such constructors.
   ```c++
   template <class T>
   struct RTTI : virtual Object {
      RTTI() {
         auto *superSelf = static_cast<T*>(this);
         this->rtti = T::info();
         this->crossPtrs[this->rtti] = superSelf;
      }
   };
   ```
* `DEFINE_RTTI` - this macro should be called in body of new class, and it generates that `info()` static method. In this method it creates static `ClassInfo` instance for new class, and associates it with `ClassInfo` instances of all its parents, forming *hierarchy DAG*.
   ```c++
   #define DEFINE_RTTI(cn, ...) \
      static const ClassInfo* info() { \
         static ClassInfo v(#cn, ClassInfo::mk_class_info_array<__VA_ARGS__>()); \
         return v; \
      }
   ```
* `Hierarchy` - this is basically a wrapper around `DAG<ClassInfo*>` with `Hierarchy* instance()` singleton.

   It also provides some adoptations of DSF calls of this DAG.

   Below in the description of *visitor* pattern we will see it in action.

### Visitor
TODO