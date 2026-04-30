# =========================================================
# ExpL Compiler Testing - All Stages via Stage-8 Compiler
# =========================================================

# ---------- Directory resolution ----------
TEST_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ROOT_DIR := $(abspath $(TEST_DIR)/..)

INPUT_DIR  := $(TEST_DIR)/input
OUTPUT_DIR := $(TEST_DIR)/output
EXPECTED_DIR := $(TEST_DIR)/expected-output

# ---------- Compiler (ONLY STAGE 8 USED) ----------
COMPILER := $(ROOT_DIR)/stage-8/stage-final

XSM_SCRIPT   := ./xsm
LIBRARY_NAME := library.lib
REL_OUTPUT_DIR := $(shell realpath --relative-to=$(ROOT_DIR) $(OUTPUT_DIR))

# ---------- Ensure directories exist ----------
$(shell mkdir -p $(OUTPUT_DIR))
$(shell mkdir -p $(EXPECTED_DIR))

# ---------- Source discovery ----------
ALL_EXPL := $(wildcard $(INPUT_DIR)/s*.expl)
ALL_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(ALL_EXPL))

.PRECIOUS: $(OUTPUT_DIR)/%.xsm
.PHONY: test test-stage-1 test-stage-2 test-stage-3 test-stage-4 test-stage-5 test-stage-6 test-stage-7 test-stage-8 clean clean-runtime-only help

help:
	@echo "Usage: make test | test-stage-1 | clean"
	@echo "Note: Place input for read() in input/sXtX-in.txt"

# =========================================================
# Helper Macro for Running XSM with STDIN support
# =========================================================
define run_xsm
	@echo "  Running $(notdir $(1))..."
	@IN_FILE=$(INPUT_DIR)/$(patsubst %-runtime.txt,%,$(notdir $(2)))-in.txt; \
	if [ -f "$$IN_FILE" ]; then \
		echo "    [STDIN] Using input file: $$(basename $$IN_FILE)"; \
		cd $(ROOT_DIR) && bash $(XSM_SCRIPT) -l $(LIBRARY_NAME) -e $(REL_OUTPUT_DIR)/$(notdir $(1)) < $$IN_FILE > $(abspath $(2)) 2>&1 || true; \
	else \
		cd $(ROOT_DIR) && bash $(XSM_SCRIPT) -l $(LIBRARY_NAME) -e $(REL_OUTPUT_DIR)/$(notdir $(1)) > $(abspath $(2)) 2>&1 || true; \
	fi
endef

# =========================================================
# Compile & Run Rules (ALL USING STAGE 8)
# =========================================================

$(OUTPUT_DIR)/%.xsm: $(INPUT_DIR)/%.expl
	@echo "  [Stage 8] Compiling $(notdir $<)..."
	@$(COMPILER) $< $@

$(OUTPUT_DIR)/%-runtime.txt: $(OUTPUT_DIR)/%.xsm
	$(call run_xsm, $<, $@)

# =========================================================
# Test Reporting Logic
# =========================================================
define run_report
	@echo ""
	@echo "=========================================="
	@echo "$(1)"
	@echo "=========================================="
	@pass=0; fail=0; total=0; \
	for runtime_file in $(OUTPUT_DIR)/$(2)*-runtime.txt; do \
		if [ ! -f "$$runtime_file" ]; then continue; fi; \
		base_name=$$(basename $$runtime_file -runtime.txt); \
		exp_file=$(EXPECTED_DIR)/$${base_name}.txt; \
		total=$$((total+1)); \
		printf "%-45s" "Test: $$base_name"; \
		if [ ! -f "$$exp_file" ]; then \
			printf " \033[0;33m[SKIP]\033[0m\n"; \
		elif diff -w -B "$$runtime_file" "$$exp_file" > /dev/null 2>&1; then \
			printf " \033[0;32m[PASS]\033[0m\n"; \
			pass=$$((pass+1)); \
		else \
			printf " \033[0;31m[FAIL]\033[0m\n"; \
			fail=$$((fail+1)); \
		fi; \
	done; \
	echo "-------------------------------------------"; \
	printf "TOTAL=$$total PASS=\033[0;32m$$pass\033[0m FAIL=\033[0;31m$$fail\033[0m\n"
endef

# =========================================================
# Stage-wise Reports (Grouped, but compiled with Stage 8)
# =========================================================

test-stage-1: $(filter $(OUTPUT_DIR)/s1%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 1 TESTS (via Stage 8),s1)

test-stage-2: $(filter $(OUTPUT_DIR)/s2%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 2 TESTS (via Stage 8),s2)

test-stage-3: $(filter $(OUTPUT_DIR)/s3%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 3 TESTS (via Stage 8),s3)

test-stage-4: $(filter $(OUTPUT_DIR)/s4%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 4 TESTS (via Stage 8),s4)

test-stage-5: $(filter $(OUTPUT_DIR)/s5%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 5 TESTS (via Stage 8),s5)

test-stage-6: $(filter $(OUTPUT_DIR)/s6%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 6 TESTS (via Stage 8),s6)

test-stage-7: $(filter $(OUTPUT_DIR)/s7%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 7 TESTS (via Stage 8),s7)

test-stage-8: $(filter $(OUTPUT_DIR)/s8%-runtime.txt,$(ALL_RUNTIME))
	$(call run_report,STAGE 8 TESTS (via Stage 8),s8)

# =========================================================
# Unified Test
# =========================================================

test: $(ALL_RUNTIME)
	$(call run_report,ALL TESTS (Compiled with Stage 8),)

# =========================================================
# Cleanup
# =========================================================

clean-runtime-only:
	@rm -f $(OUTPUT_DIR)/*-runtime.txt

clean:
	@rm -f $(OUTPUT_DIR)/*.xsm $(OUTPUT_DIR)/*-runtime.txt