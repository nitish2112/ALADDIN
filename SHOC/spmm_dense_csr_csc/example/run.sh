#!/bin/bash

$ALADDIN_HOME/common/aladdin spmm_dense_csr_csc ../dynamic_trace.gz config_example 2>&1 | tee run.log
