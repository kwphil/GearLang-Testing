BUILD_DIR := build

.PHONY: clean
clean:
	rm -rf build/*

.PHONY: $(BUILD_DIR)
$(BUILD_DIR):
	mkdir -p $@