//
// Created by bochen on 2024/12/18.
//

#ifndef GTK_PAGE_ROUTE_CONFIG_VIEWMODEL_H
#define GTK_PAGE_ROUTE_CONFIG_VIEWMODEL_H
#include <string>
#include <vector>
#include <gtkmm/aboutdialog.h>
#include <sys/_types/_u_char.h>
#include "../model/route_model.h"
using namespace std;

struct PacketInfo {
    Glib::ustring time;
    Glib::ustring protocol;
    Glib::ustring sourceMAC;
    Glib::ustring destinationMAC;
    Glib::ustring sourceIP;
    Glib::ustring destinationIP;
    Glib::ustring icmpCode;
};

std::vector<PacketInfo> open_pcap_file(const char *path);

#endif //GTK_PAGE_1_VIEWMODEL_H
