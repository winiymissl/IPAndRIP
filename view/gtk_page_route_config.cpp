//
// Created by bochen on 2024/12/18.
//
#include "gtk_page_route_config.h"
#include "../model/route_model.h"

// #define ROUTE_TYPE_ITEM (route_item_get_type())
// G_DECLARE_FINAL_TYPE(RoutingTableItem, route_item, ROUTE, ITEM, GObject)


// struct _RouteItemClass {
// GObjectClass parent_class;
// };

// G_DEFINE_TYPE(RoutingTableItem, route_item, G_TYPE_OBJECT)

// static void route_item_init(RoutingTableItem *item) {
// }
//
// static void route_item_class_init(RouteItemClass *clazz) {
// }


static void setup_cb(GtkSignalListItemFactory *factory, GObject *listitem) {
    GtkWidget *label = gtk_label_new(NULL);
    gtk_list_item_set_child(GTK_LIST_ITEM(listitem), label);
}

static void bind_col1_cb(GtkSignalListItemFactory *factory, GtkListItem *listitem) {
    GtkWidget *label = gtk_list_item_get_child(listitem);
    RoutingTableItem *item = (RoutingTableItem *) gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
    gtk_label_set_text(GTK_LABEL(label), item->route_type1().data());
}

static void bind_col2_cb(GtkSignalListItemFactory *factory, GtkListItem *listitem) {
    GtkWidget *label = gtk_list_item_get_child(listitem);
    RoutingTableItem *item = (RoutingTableItem *) gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
    gtk_label_set_text(GTK_LABEL(label), item->destination_network1().data());
}

static void bind_col3_cb(GtkSignalListItemFactory *factory, GtkListItem *listitem) {
    GtkWidget *label = gtk_list_item_get_child(listitem);
    RoutingTableItem *item = (RoutingTableItem *) gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
    gtk_label_set_text(GTK_LABEL(label), item->subnet_mask1().data());
}

static void bind_col4_cb(GtkSignalListItemFactory *factory, GtkListItem *listitem) {
    GtkWidget *label = gtk_list_item_get_child(listitem);
    RoutingTableItem *item = (RoutingTableItem *) gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
    gtk_label_set_text(GTK_LABEL(label), item->next_hop1().data());
}

static void bind_col5_cb(GtkSignalListItemFactory *factory, GtkListItem *listitem) {
    GtkWidget *label = gtk_list_item_get_child(listitem);
    RoutingTableItem *item = (RoutingTableItem *) gtk_list_item_get_item(GTK_LIST_ITEM(listitem));
    gtk_label_set_text(GTK_LABEL(label), item->next_hop1().data());
}

typedef struct {
    GListStore *store;
    GtkWidget *text_views[5];
} AddActiveData;

static RoutingTableItem *route_item_new(const char *route_type, const char *destination_network,
                                        const char *subnet_mask,
                                        const char *next_hop, const char *outgoing_interface) {

    RoutingTableItem *item = new RoutingTableItem();
    item->route_type1() = g_strdup(route_type);
    item->destination_network1() = g_strdup(destination_network);
    item->subnet_mask1() = g_strdup(subnet_mask);
    item->next_hop1() = g_strdup(next_hop);
    item->outgoing_interface1() = g_strdup(outgoing_interface);
    return item;
}

void add_active(GtkWidget *widget, gpointer data) {
    AddActiveData *add_data = (AddActiveData *) data;
    GListStore *store = add_data->store;
    GtkWidget **text_views = add_data->text_views;

    GtkTextBuffer *tb_route_type = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_views[0]));
    GtkTextBuffer *tb_destination_network = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_views[1]));
    GtkTextBuffer *tb_subnet_mask = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_views[2]));
    GtkTextBuffer *tb_next_hop = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_views[3]));
    GtkTextBuffer *tb_outgoing_interface = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_views[4]));

    GtkTextIter start, end;

    // 获取 route_type 的文本
    gtk_text_buffer_get_start_iter(tb_route_type, &start);
    gtk_text_buffer_get_end_iter(tb_route_type, &end);
    gchar *route_type = gtk_text_buffer_get_text(tb_route_type, &start, &end, FALSE);

    // 获取 destination_network 的文本
    gtk_text_buffer_get_start_iter(tb_destination_network, &start);
    gtk_text_buffer_get_end_iter(tb_destination_network, &end);
    gchar *destination_network = gtk_text_buffer_get_text(tb_destination_network, &start, &end, FALSE);

    // 获取 subnet_mask 的文本
    gtk_text_buffer_get_start_iter(tb_subnet_mask, &start);
    gtk_text_buffer_get_end_iter(tb_subnet_mask, &end);
    gchar *subnet_mask = gtk_text_buffer_get_text(tb_subnet_mask, &start, &end, FALSE);

    // 获取 next_hop 的文本
    gtk_text_buffer_get_start_iter(tb_next_hop, &start);
    gtk_text_buffer_get_end_iter(tb_next_hop, &end);
    gchar *next_hop = gtk_text_buffer_get_text(tb_next_hop, &start, &end, FALSE);

    // 获取 outgoing_interface 的文本
    gtk_text_buffer_get_start_iter(tb_outgoing_interface, &start);
    gtk_text_buffer_get_end_iter(tb_outgoing_interface, &end);
    gchar *outgoing_interface = gtk_text_buffer_get_text(tb_outgoing_interface, &start, &end, FALSE);

    // 检查是否有任何文本为空
    if (g_strcmp0(route_type, "") == 0 ||
        g_strcmp0(destination_network, "") == 0 ||
        g_strcmp0(subnet_mask, "") == 0 ||
        g_strcmp0(next_hop, "") == 0 ||
        g_strcmp0(outgoing_interface, "") == 0) {
        // 释放获取的字符串
        g_free(route_type);
        g_free(destination_network);
        g_free(subnet_mask);
        g_free(next_hop);
        g_free(outgoing_interface);

        // 返回，不创建新的 RouteItem
        return;
    }


    // 创建新的 RouteItem
    RoutingTableItem *new_item = route_item_new(route_type, destination_network, subnet_mask, next_hop,
                                                outgoing_interface);
    g_list_store_append(store, new_item);

    // 清空文本视图
    gtk_text_buffer_set_text(tb_route_type, "", -1);
    gtk_text_buffer_set_text(tb_destination_network, "", -1);
    gtk_text_buffer_set_text(tb_subnet_mask, "", -1);
    gtk_text_buffer_set_text(tb_next_hop, "", -1);
    gtk_text_buffer_set_text(tb_outgoing_interface, "", -1);

    // 释放获取的字符串
    g_free(route_type);
    g_free(destination_network);
    g_free(subnet_mask);
    g_free(next_hop);
    g_free(outgoing_interface);
}

typedef struct {
    GtkSingleSelection *selection;
    GListStore *store;
} RemoveActiveData;

void remove_active(GtkWidget *widget, gpointer data) {
    RemoveActiveData *remove_data = (RemoveActiveData *) data;

    GtkSingleSelection *selection = GTK_SINGLE_SELECTION(remove_data->selection);
    GListStore *store = remove_data->store;

    // 获取当前选中的 RouteItem
    RoutingTableItem *selected_item = (RoutingTableItem *) gtk_single_selection_get_selected_item(selection);
    if (selected_item != NULL) {
        GtkTreeIter iter;

        // 获取选中项的迭代器
        if (gtk_tree_model_get_iter_first(GTK_TREE_MODEL(store), &iter)) {
            do {
                RoutingTableItem *item;
                gtk_tree_model_get(GTK_TREE_MODEL(store), &iter, 0, &item, -1); // 假设 RouteItem 在第 0 列
                if (item == selected_item) {
                    // 找到匹配的项，删除它
                    gtk_list_store_remove(GTK_LIST_STORE(store), &iter);
                    break; // 退出循环
                }
            } while (gtk_tree_model_iter_next(GTK_TREE_MODEL(store), &iter));
        }
    }
}

GtkWidget *build_routing_table(GtkWidget *stack) {
    //left
    //多行编辑器
    //route_type
    GtkWidget *tv_route_type = gtk_text_view_new();
    GtkTextBuffer *tb_route_type = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_route_type));
    gchar *text_route_type = ""; // 初始化 text
    gtk_text_buffer_set_text(tb_route_type, text_route_type, -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv_route_type), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request(tv_route_type, 150, 50); // 设置最小宽度和高度
    //destination_network
    GtkWidget *tv_destination_network = gtk_text_view_new();
    GtkTextBuffer *tb_destination_network = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_destination_network));
    gchar *text_destination_network = ""; // 初始化 text
    gtk_text_buffer_set_text(tb_destination_network, text_destination_network, -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv_destination_network), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request(tv_destination_network, 150, 50); // 设置最小宽度和高度
    //subnet_mask
    GtkWidget *tv_subnet_mask = gtk_text_view_new();
    GtkTextBuffer *tb_subnet_mask = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_subnet_mask));
    gchar *text_subnet_mask = ""; // 初始化 text
    gtk_text_buffer_set_text(tb_subnet_mask, text_subnet_mask, -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv_subnet_mask), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request(tv_subnet_mask, 150, 50); // 设置最小宽度和高度
    //next_hop
    GtkWidget *tv_next_hop = gtk_text_view_new();
    GtkTextBuffer *tb_next_hop = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_next_hop));
    gchar *text_next_hop = ""; // 初始化 text
    gtk_text_buffer_set_text(tb_next_hop, text_next_hop, -1);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv_next_hop), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request(tv_next_hop, 150, 50); // 设置最小宽度和高度
    //outgoing_interface
    GtkWidget *tv_outgoing_interface = gtk_text_view_new();
    GtkTextBuffer *tb_outgoing_interface = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv_outgoing_interface));
    gchar *text_outgoing_interface = ""; // 初始化 text
    gtk_text_buffer_set_text(tb_outgoing_interface, text_outgoing_interface, -1);

    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(tv_outgoing_interface), GTK_WRAP_WORD_CHAR);
    gtk_widget_set_size_request(tv_outgoing_interface, 150, 50); // 设置最小宽度和高度


    GtkWidget *route_config_box_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 创建一个垂直盒子作为页面 1
    GtkWidget *label0 = gtk_label_new("Config routingTable config"); // 创建一个标签
    gtk_box_append(GTK_BOX(route_config_box_layout), label0); // 将标签添加到页面 1
    GtkWidget *label1 = gtk_label_new("route type"); // 创建一个标签
    gtk_box_append(GTK_BOX(route_config_box_layout), label1); // 将标签添加到页面 1
    gtk_box_append(GTK_BOX(route_config_box_layout), tv_route_type);
    GtkWidget *label2 = gtk_label_new("destination_network"); // 创建一个标签
    gtk_box_append(GTK_BOX(route_config_box_layout), label2);
    gtk_box_append(GTK_BOX(route_config_box_layout), tv_destination_network);
    GtkWidget *label3 = gtk_label_new("subnet_mask");
    gtk_box_append(GTK_BOX(route_config_box_layout), label3);
    gtk_box_append(GTK_BOX(route_config_box_layout), tv_subnet_mask);
    GtkWidget *label4 = gtk_label_new("next_hop");
    gtk_box_append(GTK_BOX(route_config_box_layout), label4);
    gtk_box_append(GTK_BOX(route_config_box_layout), tv_next_hop);
    GtkWidget *label5 = gtk_label_new("outgoing_interface");
    gtk_box_append(GTK_BOX(route_config_box_layout), label5);
    gtk_box_append(GTK_BOX(route_config_box_layout), tv_outgoing_interface);
    GtkWidget *add = gtk_button_new_with_label("add");
    //*****************************************************************************************************
    //right
    GtkWidget *route_route_list_layout = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    GListStore *store = g_list_store_new(G_TYPE_OBJECT);


    g_list_store_append(store, route_item_new("Static", "192.168.1.0", "255.255.255.0", "192.168.1.1", "eth0"));
    g_list_store_append(store, route_item_new("Dynamic", "10.0.0.0", "255.0.0.0", "10.0.0.1", "eth1"));
    g_list_store_append(store, route_item_new("Static", "172.16.0.0", "255.240.0.0", "172.16.0.1", "eth2"));

    // 创建 AddActiveData 结构体
    AddActiveData *add_data = g_new(AddActiveData, 1);
    add_data->store = store; // 假设 store 已经在此函数中定义
    add_data->text_views[0] = tv_route_type;
    add_data->text_views[1] = tv_destination_network;
    add_data->text_views[2] = tv_subnet_mask;
    add_data->text_views[3] = tv_next_hop;
    add_data->text_views[4] = tv_outgoing_interface;
    g_signal_connect(add, "clicked", G_CALLBACK(add_active), add_data);
    gtk_box_append(GTK_BOX(route_config_box_layout), add);


    GtkWidget *route_list = gtk_column_view_new(NULL);
    gtk_column_view_set_show_column_separators(GTK_COLUMN_VIEW(route_list), TRUE);


    GtkListItemFactory *factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_col1_cb), NULL);
    GtkColumnViewColumn *column1 = gtk_column_view_column_new("Route Type", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(route_list), column1);

    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_col2_cb), NULL);
    GtkColumnViewColumn *column2 = gtk_column_view_column_new("Destination Network", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(route_list), column2);

    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_col3_cb), NULL);
    GtkColumnViewColumn *column3 = gtk_column_view_column_new("Subnet Mask", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(route_list), column3);

    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_col4_cb), NULL);
    GtkColumnViewColumn *column4 = gtk_column_view_column_new("Next Hop", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(route_list), column4);

    factory = gtk_signal_list_item_factory_new();
    g_signal_connect(factory, "setup", G_CALLBACK(setup_cb), NULL);
    g_signal_connect(factory, "bind", G_CALLBACK(bind_col5_cb), NULL);
    GtkColumnViewColumn *column5 = gtk_column_view_column_new("Outgoing Interface", factory);
    gtk_column_view_append_column(GTK_COLUMN_VIEW(route_list), column5);

    GtkSingleSelection *selection = gtk_single_selection_new(G_LIST_MODEL(store));
    gtk_single_selection_set_autoselect(selection, TRUE);
    gtk_column_view_set_model(GTK_COLUMN_VIEW(route_list), GTK_SELECTION_MODEL(selection));
    // 将列添加到 GtkColumnView
    GtkWidget *label_route_table = gtk_label_new("route table");
    gtk_box_append(GTK_BOX(route_route_list_layout), label_route_table);
    gtk_box_append(GTK_BOX(route_route_list_layout), route_list);

    GtkWidget *remove = gtk_button_new_with_label("reomve");
    RemoveActiveData *remove_data = g_new(RemoveActiveData, 1);
    remove_data->store = store;
    remove_data->selection = selection;
    // 在创建按钮时设置要删除的项
    g_signal_connect(remove, "clicked", G_CALLBACK(remove_active), remove_data);
    gtk_box_append(GTK_BOX(route_route_list_layout), remove);


    //whole page
    GtkWidget *paned = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_paned_set_start_child(GTK_PANED(paned), route_config_box_layout);
    gtk_paned_set_end_child(GTK_PANED(paned), route_route_list_layout);
    // 将页面 1 添加到 GtkStack，并命名为 "page1"
    gtk_stack_add_named(GTK_STACK(stack), paned, "page1");
    return route_config_box_layout;
}
