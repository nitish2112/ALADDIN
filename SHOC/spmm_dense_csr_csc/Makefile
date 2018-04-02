SRCS=spmm_dense_csr_csc.c

ACCEL_NAME = spmm_dense_csr_csc
TEST_BIN = $(ACCEL_NAME)
export TRACE_OUTPUT_DIR=$(ACCEL_NAME)
ifndef WORKLOAD
  export WORKLOAD=spmm_dense_csr_csc
endif
include ../common/Makefile.common
include ../common/Makefile.tracer

ultra-clean:
	rm -rf dynamic_trace.gz *.llvm *.s $(ACCEL_NAME) output.data labelmap $(ACCEL_NAME)-instrumented  example/out.csv example/$(ACCEL_NAME)_summary example/dddg_parse_progress.out

.PHONY: ultra-clean
