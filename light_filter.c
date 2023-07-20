#include <linux/bpf.h>
#include <linux/in.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <linux/if_ether.h>

#define SEC(NAME) __attribute__((section(NAME), used))

SEC("xdp")
int xdp_prog(struct xdp_md *ctx)
{
    void* data = (void*)(long)ctx->data;
    void* data_end = (void*)(long)ctx->data_end;

    struct ethhdr *eth = data;
    if (data + sizeof(*eth) <= data_end) {
        if (eth->h_proto == htons(ETH_P_IP)) {
            struct iphdr *iph = data + sizeof(*eth);
            if (data + sizeof(*eth) + sizeof(*iph) <= data_end) {
                if (iph->protocol == IPPROTO_UDP) {
                    struct udphdr *udp = data + sizeof(*eth) + sizeof(*iph);
                    if (data + sizeof(*eth) + sizeof(*iph) + sizeof(*udp) <= data_end) {
                        if (udp->dest == htons(53)) { // DNS
                            // Print a message to the kernel log
                            bpf_printk("Received DNS packet\n");
                        }
                    }
                }
            }
        }
    }
    return XDP_PASS;
}