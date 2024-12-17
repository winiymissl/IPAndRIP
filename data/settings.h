//
// Created by bochen on 2024/12/17.
//

#ifndef SETTINGS_H
#define SETTINGS_H


#include <iostream>

class setttings {
public :
    static setttings &get_instance() {
        static setttings instance;
        return instance;
    }

    std::string pcap_info_path1() const {
        return pcap_info_path;
    }

    void set_pcap_info_path(const std::string &pcap_info_path) {
        this->pcap_info_path = pcap_info_path;
    }

    std::string router_info_path1() const {
        return router_info_path;
    }

    void set_router_info_path(const std::string &router_info_path) {
        this->router_info_path = router_info_path;
    }

private:
    std::string pcap_info_path;
    std::string router_info_path;

    //禁止外部拷贝和赋值
    setttings(const setttings &other)
        : pcap_info_path{other.pcap_info_path},
          router_info_path{other.router_info_path} {
    }

    setttings(setttings &&other) noexcept
        : pcap_info_path{std::move(other.pcap_info_path)},
          router_info_path{std::move(other.router_info_path)} {
    }

    setttings &operator=(const setttings &other) {
        if (this == &other)
            return *this;
        pcap_info_path = other.pcap_info_path;
        router_info_path = other.router_info_path;
        return *this;
    }

    setttings &operator=(setttings &&other) noexcept {
        if (this == &other)
            return *this;
        pcap_info_path = std::move(other.pcap_info_path);
        router_info_path = std::move(other.router_info_path);
        return *this;
    }
};

#endif //SETTINGS_H