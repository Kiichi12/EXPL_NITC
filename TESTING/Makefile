# =========================================================
# ExpL Compiler Testing - All Stages (With STDIN Support)
# =========================================================

# ---------- Directory resolution ----------
TEST_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))
ROOT_DIR := $(abspath $(TEST_DIR)/..)

INPUT_DIR  := $(TEST_DIR)/input
OUTPUT_DIR := $(TEST_DIR)/output
EXPECTED_DIR := $(TEST_DIR)/expected-output

# ---------- Tools ----------
STAGE_1_COMPILER := $(ROOT_DIR)/stage-1/stage-final
STAGE_2_COMPILER := $(ROOT_DIR)/stage-2/stage-final
STAGE_3_COMPILER := $(ROOT_DIR)/stage-3/stage-final
STAGE_4_COMPILER := $(ROOT_DIR)/stage-4/stage-final
STAGE_5_COMPILER := $(ROOT_DIR)/stage-5/stage-final
STAGE_6_COMPILER := $(ROOT_DIR)/stage-6/stage-final
STAGE_7_COMPILER := $(ROOT_DIR)/stage-7/stage-final

XSM_SCRIPT   := ./xsm
LIBRARY_NAME := library.lib
REL_OUTPUT_DIR := $(shell realpath --relative-to=$(ROOT_DIR) $(OUTPUT_DIR))

# ---------- Ensure directories exist ----------
$(shell mkdir -p $(OUTPUT_DIR))
$(shell mkdir -p $(EXPECTED_DIR))

# ---------- Source discovery ----------
STAGE_1_EXPL := $(wildcard $(INPUT_DIR)/s1*.expl)
STAGE_2_EXPL := $(wildcard $(INPUT_DIR)/s2*.expl)
STAGE_3_EXPL := $(wildcard $(INPUT_DIR)/s3*.expl)
STAGE_4_EXPL := $(wildcard $(INPUT_DIR)/s4*.expl)
STAGE_5_EXPL := $(wildcard $(INPUT_DIR)/s5*.expl)
STAGE_6_EXPL := $(wildcard $(INPUT_DIR)/s6*.expl)
STAGE_7_EXPL := $(wildcard $(INPUT_DIR)/s7*.expl)

STAGE_1_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(STAGE_1_EXPL))
STAGE_2_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(STAGE_2_EXPL))
STAGE_3_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(STAGE_3_EXPL))
STAGE_4_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(STAGE_4_EXPL))
STAGE_5_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(STAGE_5_EXPL))
STAGE_6_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(STAGE_6_EXPL))
STAGE_7_RUNTIME := $(patsubst $(INPUT_DIR)/%.expl,$(OUTPUT_DIR)/%-runtime.txt,$(STAGE_7_EXPL))

.PRECIOUS: $(OUTPUT_DIR)/%.xsm
.PHONY: test test-stage-1 test-stage-2 test-stage-3 test-stage-4 test-stage-5 test-stage-6 test-stage-7 clean clean-runtime-only help

help:
	@echo "Usage: make test | test-stage-1 | clean"
	@echo "Note: Place input for read() in input/sXtX-in.txt"

# =========================================================
# Helper Macro for Running XSM with STDIN support
# =========================================================
# $(1): Path to .xsm file
# $(2): Path to -runtime.txt (target)
define run_xsm
	@echo "  Running $(notdir $(1))..."
	@# Determine the input file name: input/sXtX-in.txt
	@IN_FILE=$(INPUT_DIR)/$(patsubst %-runtime.txt,%,$(notdir $(2)))-in.txt; \
	if [ -f "$$IN_FILE" ]; then \
		echo "    [STDIN] Using input file: $$(basename $$IN_FILE)"; \
		cd $(ROOT_DIR) && bash $(XSM_SCRIPT) -l $(LIBRARY_NAME) -e $(REL_OUTPUT_DIR)/$(notdir $(1)) < $$IN_FILE > $(abspath $(2)) 2>&1 || true; \
	else \
		cd $(ROOT_DIR) && bash $(XSM_SCRIPT) -l $(LIBRARY_NAME) -e $(REL_OUTPUT_DIR)/$(notdir $(1)) > $(abspath $(2)) 2>&1 || true; \
	fi
endef

# =========================================================
# Compile & Run Rules
# =========================================================

# STAGE 1
$(OUTPUT_DIR)/s1%.xsm: $(INPUT_DIR)/s1%.expl
	@echo "  [Stage 1] Compiling $(notdir $<)..."
	@$(STAGE_1_COMPILER) $< $@

$(OUTPUT_DIR)/s1%-runtime.txt: $(OUTPUT_DIR)/s1%.xsm
	$(call run_xsm, $<, $@)

# STAGE 2
$(OUTPUT_DIR)/s2%.xsm: $(INPUT_DIR)/s2%.expl
	@echo "  [Stage 2] Compiling $(notdir $<)..."
	@$(STAGE_2_COMPILER) $< $@

$(OUTPUT_DIR)/s2%-runtime.txt: $(OUTPUT_DIR)/s2%.xsm
	$(call run_xsm, $<, $@)

# STAGE 3
$(OUTPUT_DIR)/s3%.xsm: $(INPUT_DIR)/s3%.expl
	@echo "  [Stage 3] Compiling $(notdir $<)..."
	@$(STAGE_3_COMPILER) $< $@

$(OUTPUT_DIR)/s3%-runtime.txt: $(OUTPUT_DIR)/s3%.xsm
	$(call run_xsm, $<, $@)

# STAGE 4
$(OUTPUT_DIR)/s4%.xsm: $(INPUT_DIR)/s4%.expl
	@echo "  [Stage 4] Compiling $(notdir $<)..."
	@$(STAGE_4_COMPILER) $< $@

$(OUTPUT_DIR)/s4%-runtime.txt: $(OUTPUT_DIR)/s4%.xsm
	$(call run_xsm, $<, $@)

# STAGE 5
$(OUTPUT_DIR)/s5%.xsm: $(INPUT_DIR)/s5%.expl
	@echo "  [Stage 5] Compiling $(notdir $<)..."
	@$(STAGE_5_COMPILER) $< $@

$(OUTPUT_DIR)/s5%-runtime.txt: $(OUTPUT_DIR)/s5%.xsm
	$(call run_xsm, $<, $@)

# STAGE 6
$(OUTPUT_DIR)/s6%.xsm: $(INPUT_DIR)/s6%.expl
	@echo "  [Stage 6] Compiling $(notdir $<)..."
	@$(STAGE_6_COMPILER) $< $@

$(OUTPUT_DIR)/s6%-runtime.txt: $(OUTPUT_DIR)/s6%.xsm
	$(call run_xsm, $<, $@)

# STAGE 7
$(OUTPUT_DIR)/s7%.xsm: $(INPUT_DIR)/s7%.expl
	@echo "  [Stage 7] Compiling $(notdir $<)..."
	@$(STAGE_7_COMPILER) $< $@

$(OUTPUT_DIR)/s7%-runtime.txt: $(OUTPUT_DIR)/s7%.xsm
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

test-stage-1: $(STAGE_1_RUNTIME)
	$(call run_report,STAGE 1: Expression Evaluation,s1)

test-stage-2: $(STAGE_2_RUNTIME)
	$(call run_report,STAGE 2: Variables & I/O,s2)

test-stage-3: $(STAGE_3_RUNTIME)
	$(call run_report,STAGE 3: Control Flow (IF/WHILE),s3)

test-stage-4: $(STAGE_4_RUNTIME)
	$(call run_report,STAGE 4: 2D Arrays & Pointers,s4)

test-stage-5: $(STAGE_5_RUNTIME)
	$(call run_report,STAGE 5: Functions & Recursion,s5)

test-stage-6: $(STAGE_6_RUNTIME)
	$(call run_report,STAGE 6: Advanced Features,s6)

test-stage-7: $(STAGE_7_RUNTIME)
	$(call run_report,STAGE 7: Advanced Features,s7)

test: test-stage-1 test-stage-2 test-stage-3 test-stage-4 test-stage-5 test-stage-6 test-stage-7

clean-runtime-only:
	@rm -f $(OUTPUT_DIR)/*-runtime.txt

clean:
	@rm -f $(OUTPUT_DIR)/*.xsm $(OUTPUT_DIR)/*-runtime.txt