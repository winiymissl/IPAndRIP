//
// Created by bochen on 2024/12/18.
//

#include "gtk_page_pcap_read.h"

#include <gtk/gtk.h>
#include <pcap.h>
#include <string>
#include <time.h>
#include <vector>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <arpa/inet.h>


std::vector<PacketInfo> open_pcap_file(const char *path) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    std::vector<PacketInfo> allPacketInfos;

    // 打开指定的 PCAP 文件
    handle = pcap_open_offline(path, errbuf);
    if (handle == NULL) {
        g_printerr("Could not open file %s: %s\n", path, errbuf);
        return allPacketInfos; // 返回空的vector
    }

    struct pcap_pkthdr *header;
    const u_char *packet;
    // 循环读取数据包，直到读完所有包
    while (int result = pcap_next_ex(handle, &header, &packet) >= 0) {
        if (result > 0) {
            // 打印时间戳
            char time_string[64];
            strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S",
                     localtime((const time_t *) &header->ts.tv_sec));

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
                    struct icmp *icmp_header = (struct icmp *) (
                        packet + sizeof(struct ether_header) + sizeof(struct ip));
                    PacketInfo packetInfo;
                    packetInfo.time = time_string;
                    packetInfo.protocol = std::to_string(ip_header->ip_p);
                    packetInfo.sourceMAC = source_mac;
                    packetInfo.destinationMAC = dest_mac;
                    packetInfo.sourceIP = source_ip;
                    packetInfo.destinationIP = dest_ip;
                    // 正确获取并赋值 ICMP 代码，这里假设 ICMP 代码在结构体中的成员名为 icmp_code
                    packetInfo.icmpCode = std::to_string(icmp_header->icmp_code);
                    allPacketInfos.push_back(packetInfo);
                }
            }
        }
    }
    // 关闭 PCAP 文件
    pcap_close(handle);
    return allPacketInfos;
}
