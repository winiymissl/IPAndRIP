//
// Created by bochen on 2024/12/18.
//

#ifndef GTK_PAGE_ROUTE_CONFIG_VIEWMODEL_H
#define GTK_PAGE_ROUTE_CONFIG_VIEWMODEL_H
#include <string>
#include <vector>
#include <sys/_types/_u_char.h>
#include "../model/route_model.h"
using namespace std;

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

std::string config_route(std::string ip, std::string mask, std::string gateway);

void open_pcap_file();
#endif //GTK_PAGE_1_VIEWMODEL_H
