BUILD_DIR := build
CLANG_OBJ := $(BUILD_DIR)/llvm.o

$(BUILD_DIR)/libllvm.a: $(CLANG_OBJ)
    ar rcs $@ $^

.PHONY: clean
clean:
    rm build/*

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
    mkdir -p build
