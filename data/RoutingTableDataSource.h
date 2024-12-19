//
// Created by bochen on 2024/12/19.
//

#ifndef ROUTINGTABLEDATASOURCE_H
#define ROUTINGTABLEDATASOURCE_H
#include <vector>
#include "../model/route_model.h"


class RoutingTableDataSource {
public:
    std::vector<RoutingTableItem> getRoutingTable();
};


#endif //ROUTINGTABLEDATASOURCE_H
