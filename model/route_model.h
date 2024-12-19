//
// Created by bochen on 2024/12/18.
//

#ifndef ROUTE_MODEL_H
#define ROUTE_MODEL_H
#include <string>
#include <vector>
//路由表子项
// struct _RouteItem {
//     GObject parent_instance;
//     const char *route_type; // 路由类型
//     const char *destination_network; // 目标网络
//     const char *subnet_mask; // 子网掩码
//     const char *next_hop; // 下一跳
//     const char *outgoing_interface; // 出口接口
//     const char *id; // 序号id
// };

//路由表子项
using namespace std;

//
class RoutingTableItem {
public:
    RoutingTableItem() = default;

    ~RoutingTableItem() = default;

    string route_type1() const {
        return route_type;
    }

    void set_route_type(const string &route_type) {
        this->route_type = route_type;
    }

    string destination_network1() const {
        return destination_network;
    }

    void set_destination_network(const string &destination_network) {
        this->destination_network = destination_network;
    }

    string subnet_mask1() const {
        return subnet_mask;
    }

    void set_subnet_mask(const string &subnet_mask) {
        this->subnet_mask = subnet_mask;
    }

    string next_hop1() const {
        return next_hop;
    }

    void set_next_hop(const string &next_hop) {
        this->next_hop = next_hop;
    }

    string outgoing_interface1() const {
        return outgoing_interface;
    }

    void set_outgoing_interface(const string &outgoing_interface) {
        this->outgoing_interface = outgoing_interface;
    }

private:
    string route_type;
    string destination_network;
    string subnet_mask;
    string next_hop;
    string outgoing_interface;
};

//路由表
class RoutingTable {
public:
    RoutingTable() = default;


    vector<RoutingTableItem> items1() const {
        return items;
    }

    void set_items(const vector<RoutingTableItem> &items) {
        this->items = items;
    }

private :
    vector<RoutingTableItem> items = vector<RoutingTableItem>();
};
#endif //ROUTE_MODEL_H
