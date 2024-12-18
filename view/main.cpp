#include <gtk/gtk.h>
#include <pcap.h>
#include <time.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <net/ethernet.h>
#include <arpa/inet.h>

#define PCAP_FILE_PATH "../pingIP.pcap.pcapng"  // 替换为您的 PCAP 文件路径

typedef struct {
    GtkWidget *list_box;
} AppWidgets;

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    AppWidgets *widgets = (AppWidgets *)args;

    // 打印时间戳
    char time_string[64];
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", localtime((const time_t *)&header->ts.tv_sec));

    // 解析以太网头
    struct ether_header *eth_header = (struct ether_header *)packet;
    char source_mac[18], dest_mac[18];
    snprintf(source_mac, sizeof(source_mac), "%s", ether_ntoa((struct ether_addr *)eth_header->ether_shost));
    snprintf(dest_mac, sizeof(dest_mac), "%s", ether_ntoa((struct ether_addr *)eth_header->ether_dhost));

    // 解析 IP 头
    char info[256];
    if (ntohs(eth_header->ether_type) == ETHERTYPE_IP) {
        struct ip *ip_header = (struct ip *)(packet + sizeof(struct ether_header));
        char source_ip[INET_ADDRSTRLEN], dest_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &ip_header->ip_src, source_ip, sizeof(source_ip));
        inet_ntop(AF_INET, &ip_header->ip_dst, dest_ip, sizeof(dest_ip));

        // 根据协议类型解析 TCP、UDP 或 ICMP
        switch (ip_header->ip_p) {
            case IPPROTO_TCP: {
                struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));
                snprintf(info, sizeof(info), "Time: %s, Protocol: TCP, Source MAC: %s, Destination MAC: %s, Source IP: %s, Destination IP: %s, Source Port: %d, Destination Port: %d",
                         time_string, source_mac, dest_mac, source_ip, dest_ip, ntohs(tcp_header->th_sport), ntohs(tcp_header->th_dport));
                break;
            }
            case IPPROTO_UDP: {
                struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct ip));
                snprintf(info, sizeof(info), "Time: %s, Protocol: UDP, Source MAC: %s, Destination MAC: %s, Source IP: %s, Destination IP: %s, Source Port: %d, Destination Port: %d",
                         time_string, source_mac, dest_mac, source_ip, dest_ip, ntohs(udp_header->uh_sport), ntohs(udp_header->uh_dport));
                break;
            }
            case IPPROTO_ICMP: {
                struct icmp *icmp_header = (struct icmp *)(packet + sizeof(struct ether_header) + sizeof(struct ip));
                snprintf(info, sizeof(info), "Time: %s, Protocol: ICMP, Source MAC: %s, Destination MAC: %s, Source IP: %s, Destination IP: %s, Type: %d, Code: %d",
                         time_string, source_mac, dest_mac, source_ip, dest_ip, icmp_header->icmp_type, icmp_header->icmp_code);
                break;
            }
            default:
                snprintf(info, sizeof(info), "Time: %s, Protocol: Unknown (%d), Source MAC: %s, Destination MAC: %s, Source IP: %s, Destination IP: %s",
                         time_string, ip_header->ip_p, source_mac, dest_mac, source_ip, dest_ip);
                break;
        }
    } else if (ntohs(eth_header->ether_type) == ETHERTYPE_ARP) {
        snprintf(info, sizeof(info), "Time: %s, Protocol: ARP, Source MAC: %s, Destination MAC: %s",
                 time_string, source_mac, dest_mac);
    } else {
        snprintf(info, sizeof(info), "Time: %s, Protocol: Unknown Ethernet Type (%x), Source MAC: %s, Destination MAC: %s",
                 time_string, ntohs(eth_header->ether_type), source_mac, dest_mac);
    }

    // 在列表中添加数据
    GtkWidget *row = gtk_label_new(info);
    gtk_list_box_insert(GTK_LIST_BOX(widgets->list_box), row, -1);
    gtk_widget_show(row);
}

void open_pcap_file(AppWidgets *widgets) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;

    // 打开指定的 PCAP 文件
    handle = pcap_open_offline(PCAP_FILE_PATH, errbuf);
    if (handle == NULL) {
        g_printerr("Could not open file %s: %s\n", PCAP_FILE_PATH, errbuf);
        return;
    }

    // 循环读取数据包
    pcap_loop(handle, 0, packet_handler, (u_char *)widgets);

    // 关闭 PCAP 文件
    pcap_close(handle);
}

static void activate(GApplication *app, gpointer user_data) {
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "PCAP Packet Viewer");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // 创建一个垂直盒子作为容器
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_window_set_child(GTK_WINDOW(window), box);  // 将盒子设置为窗口的子组件

    // 创建列表框
    AppWidgets *widgets = g_new(AppWidgets, 1);
    widgets->list_box = gtk_list_box_new();
    gtk_box_append(GTK_BOX(box), widgets->list_box);  // 将列表框添加到盒子中

    // 打开 PCAP 文件并解析数据包
    open_pcap_file(widgets);

    // 显示窗口
    gtk_widget_show(window);  // 显示窗口及其所有组件
}

int main(int argc, char **argv) {
    GtkApplication *app = gtk_application_new("com.example.pcapviewer", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}