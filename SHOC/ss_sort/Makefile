SRCS=ss_sort.c

ACCEL_NAME = ss_sort
TEST_BIN = $(ACCEL_NAME)
export TRACE_OUTPUT_DIR=$(ACCEL_NAME)
ifndef WORKLOAD
  export WORKLOAD=ss_sort
endif
include ../common/Makefile.common
include ../common/Makefile.tracer

ultra-clean:
	rm -rf dynamic_trace.gz *.llvm *.s $(ACCEL_NAME) output.data labelmap $(ACCEL_NAME)-instrumented  example/out.csv example/$(ACCEL_NAME)_summary example/dddg_parse_progress.out

.PHONY: ultra-clean
