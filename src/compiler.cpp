// <gearlang/compiler.cpp> -*- C++ -*-

// This file is part of the GearLang v0.0.1 executable. This executable is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Under Section 7 of GPL version 3, you are granted additional
// permissions described in the GCC Runtime Library Exception, version
// 3.1, as published by the Free Software Foundation.

// You should have received a copy of the GNU General Public License and
// a copy of the GCC Runtime Library Exception along with this program;
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/raw_ostream.h>
#include <cstdlib>
#include <memory>
#include <optional>
#include <string>
#include <vector>
#include "token.cpp"

namespace std_gearlang::tree {
    class Exit {
    private:
        int code;

    public:
        Exit(int c) {
            code = c;
        }

        static std::optional<Exit> try_parse(
            std::vector<std::shared_ptr<std_gearlang::token::Base>>::iterator iterator
        ) {
            if(iterator->get()->type() != "exit") {
                return std::nullopt;
            }

            return Exit(std::stoi((iterator+1)->get()->get_value().c_str()));
        }

        int get_code() {
            return code;
        }
    };
}

namespace std_gearlang {
    class Compiler {
    private:
        std::string output;
        std::vector<std::shared_ptr<std_gearlang::token::Base>>& tokens;

    public:
        Compiler(std::vector<std::shared_ptr<std_gearlang::token::Base>>& t) {
            output = "";
            tokens = t;
        }

        static void test(auto& t) {
            auto output = std_gearlang::tree::Exit::try_parse(t.begin());

            if(!output) {
                throw;
            }

            llvm::LLVMContext context;
            llvm::Module mod("test", context);
            llvm::FunctionType* funcType = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
            llvm::Function* start = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "_start", mod);
            llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context, "entry", start);
            llvm::IRBuilder<> builder(entryBlock);
            builder.CreateRetVoid();
            mod.print(llvm::outs(), nullptr);
        }
    };
}