#include <linux/bpf.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int xdp_drop(struct xdp_md *ctx) {
	//printk("Home sweet home\n");
    int n = 100;
    int facto = 1;

    for (int i = n; i > 0; i--) {
		facto = facto * i;
	}

    bpf_printk("Hello, world yannick! %d ", facto);
   return XDP_PASS;
}

char __license[] SEC("license") = "GPL";