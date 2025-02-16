CXX_MSG     := echo "[    CC    ]"
LD_MSG      := echo "[    LD    ]"

BUILD_DIR   := build
SRC_DIR     := src

TOKEN_DIR   := $(SRC_DIR)/token
TOKEN_BUILD := $(BUILD_DIR)/token

GXX         := g++
CXX_FLAGS   := -std=c++20 -Iinclude -Wall
CXX_SOURCES := $(wildcard $(SRC_DIR)/*.cpp)

EXEC        := $(BUILD_DIR)/a.out
OBJS        := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o, $(CXX_SOURCES))

# Include token module Makefile
include $(TOKEN_DIR)/Token.mk

# Add token object files to the build
OBJS += $(TOKEN_OBJS)

.PHONY: start
start: $(BUILD_DIR) $(EXEC)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	@$(GXX) $(CXX_FLAGS) -c $< -o $@

$(EXEC): $(OBJS)
	@$(GXX) -o $@ $^

# .PHONY: clean
# clean:
#     rm -rf $(BUILD_DIR)/*
