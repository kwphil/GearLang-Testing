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
    void create_start(std::string name) {
        llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
        llvm::Function* start = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "_start", mod);

        llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context, "entry", start);
        llvm::IRBuilder<> builder(entryBlock);

        builder.CreateRetVoid();
        mod.print(llvm::outs(), nullptr);
    }
}

int main() {
    std_gearlang::ir::create_empty("_start");
}