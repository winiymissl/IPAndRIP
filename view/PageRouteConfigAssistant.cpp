//
// Created by bochen on 2024/12/20.
//
#include <iostream>
#include "PageRouteConfigAssistant.h"

PageRouteConfigAssistant::PageRouteConfigAssistant()
    : m_box1(Gtk::Orientation::VERTICAL, 12),
      m_box2(Gtk::Orientation::VERTICAL, 12),
      m_box3(Gtk::Orientation::VERTICAL, 12),
      m_box4(Gtk::Orientation::VERTICAL, 12),
      m_box5(Gtk::Orientation::VERTICAL, 12) {
    set_title("config assistant");
    set_default_size(800, 600);

    signal_cancel().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_assistant_cancel));
    signal_close().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_assistant_close));
    signal_prepare().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_assistant_prepare));

    //box1
    m_box1.append(m_label1);
    m_box1.append(m_entry1);
    m_label1.set_wrap();
    m_label1.set_text("Type route type to continue:");
    m_label1.set_margin_top(20);
    m_label1.set_valign(Gtk::Align::CENTER);
    m_entry1.set_valign(Gtk::Align::CENTER);
    m_entry1.set_margin(10);

    append_page(m_box1);

    set_page_title(*get_nth_page(0), "route type");
    set_page_type(m_box1, Gtk::AssistantPage::Type::INTRO);

    m_entry1.signal_changed().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_entry1_changed));
    //box2
    m_box2.append(m_label2);
    m_box2.append(m_entry2);
    m_label2.set_wrap();
    m_label2.set_text("Type destination network to continue:");
    m_label2.set_margin_top(20);
    m_label2.set_valign(Gtk::Align::CENTER);
    m_entry2.set_valign(Gtk::Align::CENTER);
    m_entry2.set_margin(10);

    append_page(m_box2);

    set_page_title(*get_nth_page(1), "destination network");
    set_page_type(m_box2, Gtk::AssistantPage::Type::CONTENT);
    m_entry2.signal_changed().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_entry2_changed));

    //m_box3
    m_box3.append(m_label3);
    m_box3.append(m_entry3);
    m_label3.set_wrap();
    m_label3.set_text("Type subnet mask to continue:");
    m_label3.set_margin_top(20);
    m_label3.set_valign(Gtk::Align::CENTER);
    m_entry3.set_valign(Gtk::Align::CENTER);
    m_entry3.set_margin(10);

    append_page(m_box3);


    set_page_title(*get_nth_page(2), "subnet mask");
    set_page_type(m_box3, Gtk::AssistantPage::Type::CONTENT);

    m_entry3.signal_changed().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_entry3_changed));

    //m_box4
    m_box4.append(m_label4);
    m_box4.append(m_entry4);
    m_label4.set_wrap();
    m_label4.set_text("Type next_hop to continue:");
    m_label4.set_margin_top(20);
    m_label4.set_valign(Gtk::Align::CENTER);
    m_entry4.set_valign(Gtk::Align::CENTER);
    m_entry4.set_margin(10);

    append_page(m_box4);

    set_page_title(*get_nth_page(3), "next_hop");
    set_page_type(m_box4, Gtk::AssistantPage::Type::CONTENT);

    m_entry4.signal_changed().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_entry4_changed));
    //m_box5
    m_box5.append(m_label5);
    m_box5.append(m_entry5);
    m_label5.set_wrap();
    m_label5.set_text("Type outgoing interface to continue:");
    m_label5.set_margin_top(20);
    m_label5.set_valign(Gtk::Align::CENTER);
    m_entry5.set_valign(Gtk::Align::CENTER);
    m_entry5.set_margin(10);

    append_page(m_box5);

    set_page_title(*get_nth_page(4), "outgoing interface");
    set_page_type(m_box5, Gtk::AssistantPage::Type::CONTENT);


    m_entry5.signal_changed().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_entry5_changed));
    //m_box6
    m_box6.append(m_label6);
    m_label6.set_wrap();
    auto str = "confirm";
    m_label6.set_text(str);
    m_label6.set_margin_top(20);
    m_label6.set_valign(Gtk::Align::CENTER);

    append_page(m_box6);

    set_page_title(*get_nth_page(5), "confirmation");
    set_page_type(m_box6, Gtk::AssistantPage::Type::CONFIRM);
    set_page_complete(m_box6, true);

    signal_apply().connect(sigc::mem_fun(*this, &PageRouteConfigAssistant::on_assistant_apply));
}

PageRouteConfigAssistant::~PageRouteConfigAssistant() {
}

PageRouteConfigAssistant *&PageRouteConfigAssistant::getInstance() {
    static PageRouteConfigAssistant *instance = new PageRouteConfigAssistant(); // 局部静态变量，线程安全
    return instance;
}


void PageRouteConfigAssistant::on_assistant_apply() {
    std::cout << "Apply was clicked";
    print_status();
}


void PageRouteConfigAssistant::get_result(
    Glib::ustring &entry_type, Glib::ustring &destination_network, Glib::ustring &subnet_mask, Glib::ustring &next_hop,
    Glib::ustring &outgoing_interface
) {
    entry_type = m_entry1.get_text();
    destination_network = m_entry2.get_text();
    subnet_mask = m_entry3.get_text();
    next_hop = m_entry4.get_text();
    outgoing_interface = m_entry5.get_text();
}

void PageRouteConfigAssistant::on_assistant_cancel() {
    std::cout << "Cancel was clicked";
    print_status();
    set_visible(false);
}


void PageRouteConfigAssistant::on_assistant_close() {
    std::cout << "Assistant was closed";
    print_status();
    set_visible(false);
}

void PageRouteConfigAssistant::on_assistant_prepare(Gtk::Widget *widget) {
    set_title(Glib::ustring::compose("Gtk::Assistant example (Page %1 of %2)", get_current_page() + 1, get_n_pages()));
}

void PageRouteConfigAssistant::on_entry1_changed() {
    // The page is only complete if the entry contains text.
    if (m_entry1.get_text_length())
        set_page_complete(m_box1, true);
    else
        set_page_complete(m_box1, false);
}

void PageRouteConfigAssistant::on_entry2_changed() {
    // The page is only complete if the entry contains text.
    if (m_entry2.get_text_length())
        set_page_complete(m_box2, true);
    else
        set_page_complete(m_box2, false);
}

void PageRouteConfigAssistant::on_entry3_changed() {
    // The page is only complete if the entry contains text.
    if (m_entry3.get_text_length())
        set_page_complete(m_box3, true);
    else
        set_page_complete(m_box3, false);
}

void PageRouteConfigAssistant::on_entry4_changed() {
    // The page is only complete if the entry contains text.
    if (m_entry4.get_text_length())
        set_page_complete(m_box4, true);
    else
        set_page_complete(m_box4, false);
}

void PageRouteConfigAssistant::on_entry5_changed() {
    // The page is only complete if the entry contains text.
    if (m_entry5.get_text_length())
        set_page_complete(m_box5, true);
    else
        set_page_complete(m_box5, false);
}


void PageRouteConfigAssistant::print_status() {
    std::cout << ", entry contents: \n" <<
            m_entry1.get_text() << "|" << m_entry2.get_text() << m_entry3.get_text() << "|" << m_entry4.get_text() <<
            "|" << m_entry4.get_text() << "|" << std::endl;
}
