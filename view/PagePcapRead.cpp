//
// Created by bochen on 2024/12/22.
//

#include "PagePcapRead.h"
#include "../mid/gtk_page_pcap_read.h"
#include <iostream>

#include "PageRouteConfig.h"

void PagePcapRead::on_button_file_clicked() {
    auto dialog = Gtk::FileDialog::create();
    // Add filters, so that only certain file types can be selected:
    auto filters = Gio::ListStore<Gtk::FileFilter>::create();
    //过滤器
    //过滤器
    // 创建文件过滤器对象，用于筛选特定类型的文件
    auto filter_pcap = Gtk::FileFilter::create();
    filter_pcap->set_name("PCAP files");
    // 添加.pcap扩展名的匹配模式
    filter_pcap->add_pattern("*.pcap");
    // 添加.pcapng扩展名的匹配模式，使其能同时匹配两种文件格式
    filter_pcap->add_pattern("*.pcapng");

    // 获取已有的文件过滤器列表（假设filters已经正确定义并初始化，如果没有则需要先创建合适的容器来存储文件过滤器）
    filters->append(filter_pcap);
    // 将包含筛选规则的文件过滤器设置到文件对话框中
    dialog->set_filters(filters);

    dialog->open(sigc::bind(sigc::mem_fun(
                                *this, &PagePcapRead::on_file_dialog_finish), dialog));
}

PagePcapRead::~PagePcapRead() {
}

void PagePcapRead::on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult> &result,
                                         const Glib::RefPtr<Gtk::FileDialog> &dialog) {
    // Handle the response:
    try {
        auto file = dialog->open_finish(result);
        // Notice that this is a std::string, not a Glib::ustring.
        auto filename = file->get_path();
        std::cout << "File selected: " << filename << std::endl;
        getInstance()->m_Label.set_label(filename);
        // 读取pcap文件
        vector<PacketInfo> data = open_pcap_file(filename.c_str());
        for (PacketInfo &packet: data) {
            getInstance()->m_ListStore->append(
                PagePcapRead::ModelColumns::create(packet.time, packet.protocol, packet.sourceMAC, packet.destinationMAC,
                                                   packet.sourceIP, packet.destinationIP , packet.icmpCode));
        }
        //测试
        getInstance()->m_ListStore->append(
            PagePcapRead::ModelColumns::create("1234", "Billy Bob", "1234", "1324", "1324", "1324", "asdf"));
    } catch (const Gtk::DialogError &err) {
        // Can be thrown by dialog->open_finish(result).
        std::cout << "No file selected. " << err.what() << std::endl;
    }
    catch (const Glib::Error &err) {
        std::cout << "Unexpected exception. " << err.what() << std::endl;
    }
}

void PagePcapRead::on_setup_label(
    const Glib::RefPtr<Gtk::ListItem> &list_item, Gtk::Align halign) {
    list_item->set_child(*Gtk::make_managed<Gtk::Label>("", halign));
}

void PagePcapRead::on_bind_time(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->time);
}

PagePcapRead *PagePcapRead::getInstance() {
    static PagePcapRead *instance = new PagePcapRead();
    return instance;
}


void PagePcapRead::on_bind_sour_ip(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->sour_ip);
}

void PagePcapRead::on_bind_des_ip(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->des_ip);
}

void PagePcapRead::on_bind_des_mac(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->des_mac);
}

void PagePcapRead::on_bind_sour_mac(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->sour_mac);
}

void PagePcapRead::on_bind_code(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->code);
}

void PagePcapRead::on_bind_protocol(const Glib::RefPtr<Gtk::ListItem> &list_item) {
    auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
    if (!col)
        return;
    auto label = dynamic_cast<Gtk::Label *>(list_item->get_child());
    if (!label)
        return;
    label->set_text(col->protocol);
}

Gtk::Box *build_page_read_pcap(Gtk::Box *box) {
    PagePcapRead *page = PagePcapRead::getInstance();

    box->append(page->m_ButtonBox);
    page->m_Button_File.set_name("choose_file");
    page->m_Button_File.set_label("choose_file");
    page->m_Button_File.set_margin(10);
    page->m_Label.set_label("choose_file");
    page->m_Label.set_margin(10);

    box->append(page->m_Button_File);
    box->append(page->m_Label);
    box->append(page->m_ScrolledWindow);

    page->m_ScrolledWindow.set_child(page->m_ColumnView);
    page->m_ScrolledWindow.set_expand(true);

    page->m_ListStore = Gio::ListStore<PagePcapRead::ModelColumns>::create();

    auto selection_model = Gtk::SingleSelection::create(page->m_ListStore);
    selection_model->set_autoselect(false);
    selection_model->set_can_unselect(true);
    page->m_ColumnView.set_model(selection_model);
    page->m_ColumnView.add_css_class("data-table");
    page->m_ColumnView.set_reorderable(true);

    auto factory = Gtk::SignalListItemFactory::create();
    auto column = Gtk::ColumnViewColumn::create("nothing", factory);
    //time
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*page,
                                                             &PagePcapRead::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*page, &PagePcapRead::on_bind_time));
    column = Gtk::ColumnViewColumn::create("time", factory);
    page->m_ColumnView.append_column(column);
    //protocol
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*page,
                                                             &PagePcapRead::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*page, &PagePcapRead::on_bind_protocol));
    column = Gtk::ColumnViewColumn::create("protocol", factory);
    page->m_ColumnView.append_column(column);
    //sour ip
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*page,
                                                             &PagePcapRead::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*page, &PagePcapRead::on_bind_sour_ip));
    column = Gtk::ColumnViewColumn::create("sour ip", factory);
    page->m_ColumnView.append_column(column);
    //des ip
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*page,
                                                             &PagePcapRead::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*page, &PagePcapRead::on_bind_des_ip));
    column = Gtk::ColumnViewColumn::create("des ip", factory);
    page->m_ColumnView.append_column(column);

    //sour mac
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*page,
                                                             &PagePcapRead::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*page, &PagePcapRead::on_bind_sour_mac));
    column = Gtk::ColumnViewColumn::create("sour mac", factory);
    page->m_ColumnView.append_column(column);

    //des mac
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*page,
                                                             &PagePcapRead::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*page, &PagePcapRead::on_bind_des_mac));
    column = Gtk::ColumnViewColumn::create("des mac", factory);
    page->m_ColumnView.append_column(column);

    //code
    factory = Gtk::SignalListItemFactory::create();
    factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*page,
                                                             &PagePcapRead::on_setup_label),
                                               Gtk::Align::BASELINE_CENTER));
    factory->signal_bind().connect(
        sigc::mem_fun(*page, &PagePcapRead::on_bind_code));
    column = Gtk::ColumnViewColumn::create("code", factory);
    page->m_ColumnView.append_column(column);


    page->m_Button_File.signal_clicked().connect(sigc::mem_fun(*page,
                                                               &PagePcapRead::on_button_file_clicked));
    return box;
}
