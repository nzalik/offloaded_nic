#!/bin/bash

# Compile the XDP eBPF program
clang-10 -O2 -target bpf -c my_xdp_program.c -o my_xdp_program.o

#Stop any program running on the interface
sudo ip link set wlo1 xdp off

# Load the XDP eBPF program onto the network interface
sudo ip link set dev wlo1 xdp obj my_xdp_program.o sec xdp

# Show the logs 
sudo cat /sys/kernel/debug/tracing/trace_pipe