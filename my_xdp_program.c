#include <linux/bpf.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <bpf/bpf_helpers.h>

SEC("xdp")
int xdp_prog(struct xdp_md *ctx)
{
    int n = 5;
    int i = 1;
    int facto = 1;
    for (i = 1; i <= n; i++) {
        facto *= i;
    }
    bpf_printk("Dropping ICMP packet %d", facto);
    return XDP_PASS;
}

char _license[] SEC("license") = "GPL";