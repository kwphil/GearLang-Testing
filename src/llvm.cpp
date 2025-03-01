// <gearlang/llvm.cpp> -*- C++ -*-
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

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