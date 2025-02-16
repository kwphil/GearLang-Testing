TOKEN_SOURCES := $(wildcard $(TOKEN_DIR)/*.cpp)
TOKEN_OBJS    := $(patsubst $(TOKEN_DIR)/%.cpp,$(TOKEN_BUILD)/%.o, $(notdir $(TOKEN_SOURCES)))

$(TOKEN_BUILD):
	mkdir -p $@

$(TOKEN_BUILD)/%.o: $(TOKEN_DIR)/%.cpp | $(TOKEN_BUILD)
	@$(GXX) $(CXX_FLAGS) -c $< -o $@
