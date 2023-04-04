
// TODO: Check clang version, after 383cfeee09d we need to include
//    clang/Basic/ParsedAttrInfo.h instead of clang/Sema/ParsedAttr.h
#include "clang/Sema/ParsedAttr.h"
#include "clang/Sema/Sema.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"

#include <iostream>

using namespace clang;

namespace
{
    class MyRTTIVisitor : public RecursiveASTVisitor<MyRTTIVisitor> {
    public:
    MyRTTIVisitor(DiagnosticsEngine &Diags) /* : Diags(Diags) */ {
        WarningFeatureNotImplemented = Diags.getCustomDiagID(
            DiagnosticsEngine::Warning,
            "TODO: MyRTTI plugin is not implemented.");

        Diags.Report(WarningFeatureNotImplemented);
    }
    bool VisitCXXRecordDecl(CXXRecordDecl *RecordDecl) {
        // TODO. Here we hope to do following things:
        //   For each class ClassName:
        //   1. Check whether RecordDecl inherited from myrtti::Object
        //   2. Inject myrtti::RTTI<ClassName> into bases clause.
        //   3. Inject ClassName::info() static method.
        return true;
    }

    private:
        // DiagnosticsEngine &Diags;
        unsigned WarningFeatureNotImplemented;
    };

    class MyRTTIConsumer : public ASTConsumer {
    public:
        void HandleTranslationUnit(ASTContext &Context) override {
            MyRTTIVisitor Visitor(Context.getDiagnostics());
            Visitor.TraverseDecl(Context.getTranslationUnitDecl());
        }
    };

    class MyRTTIAction : public PluginASTAction {
    public:
        std::unique_ptr<ASTConsumer> CreateASTConsumer(
            CompilerInstance &CI, llvm::StringRef
        ) override {
            return std::make_unique<MyRTTIConsumer>();
        }

        bool ParseArgs(const CompilerInstance &CI,
                        const std::vector<std::string> &args) override {
            llvm_unreachable("whoosh");
            if (!args.empty() && args[0] == "help")
                llvm::errs() << "Help for the myrtti plugin goes here\n";
            return true;
        }

        PluginASTAction::ActionType getActionType() override {
            return AddBeforeMainAction;
        }
    };
}

static FrontendPluginRegistry::Add<MyRTTIAction> X(
    "myrtti_plugin",
    "MyRTTI plugin, checks whether class inherited from myrtti::Object,"
    " for all such classes it injects ClassName::info() static method, and injects"
    " RTTI<ClassName> as a base."
);
