//
// Created by bochen on 2024/12/25.
//

#ifndef PAGECORE_H
#define PAGECORE_H
#include <giomm/liststore.h>
#include <gtkmm/box.h>


void build_pcap_core(Gtk::Box *box);

class PageCore {
    PageCore() = default;

public:
    PageCore *getInstance();

    ~PageCore();

    //两个指针，最终在core里面判断逻辑
};

#endif //PAGECORE_H
