#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <string>

static llvm::LLVMContext context;
static llvm::Module main_module("main", context);

namespace std_gearlang::ir {
    void create_start() {
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
        llvm::Function* start = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "_start", main_module);

        llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context, "entry", start);
        llvm::IRBuilder<> builder(entryBlock);

        builder.CreateRetVoid();
        main_module.print(llvm::outs(), nullptr);
    }
}