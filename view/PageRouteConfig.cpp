//
// Created by bochen on 2024/12/20.
//

#include "PageRouteConfig.h"
#include "MainWindow.h"


void PageRouteConfig::on_setup_label(
    const Glib::RefPtr<Gtk::ListItem> &list_item, Gtk::Align halign) {
    list_item->set_child(*Gtk::make_managed<Gtk::Label>("hhhhhhhhhh", halign));
}

void PageRouteConfig::on_bind_id(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(Glib::ustring::format(col->id));
}

void PageRouteConfig::on_bind_route_type(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->route_type);
}

void PageRouteConfig::on_bind_destination_network(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    // 10 digits, using leading zeroes.
    label->set_text(col->destination_network);
}

void PageRouteConfig::on_bind_subnet_mask(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto progressbar = dynamic_cast<Gtk::ProgressBar *>(list_item->get_child());
    if (!progressbar)
        return;
    progressbar->set_text(col->subnet_mask);
}

void PageRouteConfig::on_bind_next_hop(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto progressbar = dynamic_cast<Gtk::ProgressBar *>(list_item->get_child());
    if (!progressbar)
        return;
    progressbar->set_text(col->next_hop);
}

void PageRouteConfig::on_bind_outgoing_interface(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto progressbar = dynamic_cast<Gtk::ProgressBar *>(list_item->get_child());
    if (!progressbar)
        return;
    progressbar->set_text(col->outgoing_interface);
}
PageRouteConfig *& PageRouteConfig::getInstance() {
    static PageRouteConfig *instance = new PageRouteConfig(); // 局部静态变量，线程安全
    return instance;
}

using namespace std;

Gtk::Box *build_page_route_config(Gtk::Box *box) {
    //这个page的主布局
     PageRouteConfig *config = PageRouteConfig::getInstance();


    box->set_margin(5);
    box->append(config->m_ScrolledWindow);
    box->append(config->m_Button_Add);
    box->append(config->m_Button_Remove);

    config->m_ScrolledWindow.set_child(config->m_ColumnView);
    config->m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    config->m_ScrolledWindow.set_expand();

    // Create the List model:
    config->m_ListStore = Gio::ListStore<PageRouteConfig::ModelColumns>::create();
    config->m_ListStore->append(
        PageRouteConfig::ModelColumns::create("1234", "Billy Bob", "1234", "1324", "1324", "1324"));
    config->m_ListStore->append(
        PageRouteConfig::ModelColumns::create("1234", "Billy Bob", "1234", "1324", "1324", "1324"));
    config->m_ListStore->append(
        PageRouteConfig::ModelColumns::create("1234", "Billy Bob", "1234", "1324", "1324", "1324"));

    // Set list model and selection model.
    auto selection_model = Gtk::SingleSelection::create(config->m_ListStore);
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    config->m_ColumnView.set_model(selection_model);
    config->m_ColumnView.add_css_class("data-table"); // high density table

    // Make the columns reorderable.
    // This is not necessary, but it's nice to show the feature.
    config->m_ColumnView.set_reorderable(true);

    // Add the ColumnView's columns:

    // Id column
    auto factory = Gtk::SignalListItemFactory::create();
    auto column = Gtk::ColumnViewColumn::create("nothing", factory);
    // id
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*config,
                                                             &PageRouteConfig::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*config, &PageRouteConfig::on_bind_id));
    column = Gtk::ColumnViewColumn::create("id", factory);
    config->m_ColumnView.append_column(column);
    // route type
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*config,
                                                             &PageRouteConfig::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*config, &PageRouteConfig::on_bind_route_type));
    column = Gtk::ColumnViewColumn::create("route type", factory);
    config->m_ColumnView.append_column(column);
    // subnet mask
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*config,
                                                             &PageRouteConfig::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*config, &PageRouteConfig::on_bind_subnet_mask));
    column = Gtk::ColumnViewColumn::create("subnet mask", factory);
    config->m_ColumnView.append_column(column);
    // next_hop
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*config,
                                                             &PageRouteConfig::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*config, &PageRouteConfig::on_bind_next_hop));
    column = Gtk::ColumnViewColumn::create("next_hop", factory);
    config->m_ColumnView.append_column(column);

    // outgoing_interface
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*config,
                                                             &PageRouteConfig::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*config, &PageRouteConfig::on_bind_outgoing_interface));
    column = Gtk::ColumnViewColumn::create("outgoing interface", factory);
    config->m_ColumnView.append_column(column);

    // destination network
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*config,
                                                             &PageRouteConfig::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*config, &PageRouteConfig::on_bind_destination_network));
    column = Gtk::ColumnViewColumn::create("destination network", factory);
    config->m_ColumnView.append_column(column);


    config->m_Button_Add.set_hexpand(true);
    config->m_Button_Add.set_margin(5);
    config->m_Button_Add.set_label("Add");
    config->m_Button_Add.set_valign(Gtk::Align::CENTER);
    config->m_Button_Add.signal_clicked().connect(sigc::mem_fun(*config, &PageRouteConfig::on_button_clicked_add));

    config->m_Button_Remove.set_hexpand(true);
    config->m_Button_Remove.set_margin(5);
    config->m_Button_Remove.set_label("Remove");
    config->m_Button_Remove.set_valign(Gtk::Align::CENTER);
    config->m_Button_Remove.signal_clicked().
            connect(sigc::mem_fun(*config, &PageRouteConfig::on_button_clicked_remove));

    config->m_assistant.signal_apply().connect(sigc::mem_fun(*config, &PageRouteConfig::on_assistant_apply));
    return box;
}


void PageRouteConfig::on_assistant_apply() {
    // Glib::ustring entry_type, destination_network, subnet_mask, next_hop, outgoing_interface;
    // config->m_assistant.get_result(entry_type, destination_network, subnet_mask, next_hop, outgoing_interface);
    // //添加新条目
    // config->m_ListStore->append(
    //     PageRouteConfig::ModelColumns::create("1", entry_type, destination_network, subnet_mask, next_hop,
    //                                           outgoing_interface));
}

void PageRouteConfig::on_button_clicked_add() {
    g_log("test", G_LOG_LEVEL_MESSAGE, "add");
    m_assistant.set_visible(true);
}

void PageRouteConfig::on_button_clicked_remove() {
    // auto item = config->m_ColumnView.get_model()->get_selection();
    // auto list = m_ColumnView.get_columns();
    m_ListStore->remove(0);
}

