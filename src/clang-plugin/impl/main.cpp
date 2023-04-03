
// TODO: Check clang version, after 383cfeee09d we need to include
//    clang/Basic/ParsedAttrInfo.h instead of clang/Sema/ParsedAttr.h
#include "clang/Sema/ParsedAttr.h"
#include "clang/Sema/Sema.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"

using namespace clang;

namespace
{
    struct MyRTTIAttrInfo : ParsedAttrInfo {
        MyRTTIAttrInfo() {
            Spellings = S;
        }

        AttrHandling handleDeclAttribute(Sema &S, Decl *D,
                                        const ParsedAttr &Attr) const override {
            // Handle the attribute
            return AttributeApplied;
        }

        bool diagAppertainsToDecl(Sema &S, const ParsedAttr &Attr,
                                    const Decl *D) const override {
            // This attribute appertains to functions only.
            if (!isa<CXXRecordDecl>(D)) {

                unsigned diagID = S.Diags.getCustomDiagID(
                    DiagnosticsEngine::Error,
                    "'myrtti' attribute applied to classes or structure only."
                );

                S.Diags.Report(Attr.getLoc(), diagID);

                return false;
            }
            return true;
        }

    private:
        static constexpr Spelling S[] = {
            {ParsedAttr::AS_GNU, "myrtti"},
            {ParsedAttr::AS_C2x, "myrtti"},
            {ParsedAttr::AS_CXX11, "myrtti"},
            {ParsedAttr::AS_CXX11, "plugin::myrtti"}
        };
    };
}

static ParsedAttrInfoRegistry::Add<MyRTTIAttrInfo> Z("myrtti_attr","MyRTTI attribute");
// X("MyRTTIClangPlugin", "MyRTTI Clang Plugin");