#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int test(struct xdp_md *ctx) {
	//printk("Home sweet home\n");
    bpf_printk("Hello, world!");
   return XDP_PASS;
}

char __license[] SEC("license") = "GPL";