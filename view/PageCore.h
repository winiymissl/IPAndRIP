//
// Created by bochen on 2024/12/25.
//

#ifndef PAGECORE_H
#define PAGECORE_H
#include <gtkmm/box.h>


void build_pcap_core(Gtk::Box *box);

class PageCore {
    PageCore() = default;

public:
    PageCore *getInstance();

    ~PageCore();
};

#endif //PAGECORE_H
