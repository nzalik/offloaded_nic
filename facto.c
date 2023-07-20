#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int xdp_drop(struct xdp_md *ctx) {
	//printk("Home sweet home\n");
    bpf_printk("bonjour le monde!");
   return XDP_PASS;
}

char __license[] SEC("license") = "GPL";