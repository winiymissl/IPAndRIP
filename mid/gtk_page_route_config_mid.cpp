//
// Created by bochen on 2024/12/18.
//

#include "gtk_page_route_config_mid.h"
#include <gtk/gtk.h>
#include <pcap.h>
#include <string>
#include <time.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#define PCAP_FILE_PATH "../pingIP.pcap.pcapng"  // 替换为您的 PCAP 文件路径

//处理pcap文件中的数据包
void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    // 打印时间戳
    char time_string[64];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", localtime((const time_t *) &header->ts.tv_sec));

    // 解析以太网头
    struct ether_header *eth_header = (struct ether_header *) packet;
    char source_mac[18], dest_mac[18];
    snprintf(source_mac, sizeof(source_mac), "%s", ether_ntoa((struct ether_addr *) eth_header->ether_shost));
    snprintf(dest_mac, sizeof(dest_mac), "%s", ether_ntoa((struct ether_addr *) eth_header->ether_dhost));

    // 解析 IP 头
    char info[256];
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        struct ip *ip_header = (struct ip *) (packet + sizeof(struct ether_header));
        char source_ip[INET_ADDRSTRLEN], dest_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ip_header->ip_src, source_ip, sizeof(source_ip));
        inet_ntop(AF_INET, &ip_header->ip_dst, dest_ip, sizeof(dest_ip));

        // 根据协议类型解析 ICMP
        if (ip_header->ip_p == IPPROTO_ICMP) {
            struct icmp *icmp_header = (struct icmp *) (packet + sizeof(struct ether_header) + sizeof(struct ip));
            snprintf(info, sizeof(info),
                     "Time: %s, Protocol: ICMP, Source MAC: %s, Destination MAC: %s, Source IP: %s, Destination IP: %s, Type: %d, Code: %d",
                     time_string, source_mac, dest_mac, source_ip, dest_ip, icmp_header->icmp_type,
                     icmp_header->icmp_code);

            // 根据 ICMP 类型将报文添加到不同的列表
            if (icmp_header->icmp_type == 8) {
                // Echo Request
                //放在容器里面返回
            } else if (icmp_header->icmp_type == 0) {
                //放在容器里面返回
            }
        }
    }
}
//配置pcap_file文件
void open_pcap_file() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // 打开指定的 PCAP 文件
    handle = pcap_open_offline(PCAP_FILE_PATH, errbuf);
    if (handle == NULL) {
        g_printerr("Could not open file %s: %s\n", PCAP_FILE_PATH, errbuf);
        return;
    }
    // 循环读取数据包
    pcap_loop(handle, 0, packet_handler, (u_char *) NULL);
    // 关闭 PCAP 文件
    pcap_close(handle);
}
