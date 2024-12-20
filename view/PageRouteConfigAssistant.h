//
// Created by bochen on 2024/12/20.
//

#ifndef PAGEROUTECONFIGASSISTANT_H
#define PAGEROUTECONFIGASSISTANT_H
#include <gtkmm.h>
#include <gtkmm.h>


class PageRouteConfigAssistant : public Gtk::Assistant {
public:
    static PageRouteConfigAssistant * &getInstance();

    PageRouteConfigAssistant();

    virtual ~PageRouteConfigAssistant();

    void get_result(Glib::ustring &entry_type, Glib::ustring &destination_network, Glib::ustring &subnet_mask,
                    Glib::ustring &next_hop,
                    Glib::ustring &outgoing_interface);

private:
    // Signal handlers:

    void on_assistant_apply();

    void on_assistant_cancel();

    void on_assistant_close();

    void on_assistant_prepare(Gtk::Widget *widget);

    void on_entry1_changed();

    void on_entry2_changed();

    void on_entry3_changed();

    void on_entry4_changed();

    void on_entry5_changed();

    // Member functions:
    void print_status();

    // Child widgets:
    Gtk::Box m_box1, m_box2, m_box3, m_box4, m_box5, m_box6;
    Gtk::Label m_label1, m_label2, m_label3, m_label4, m_label5, m_label6;
    Gtk::Button m_Button1, m_Button2, m_Button3, m_Button4, m_Button5;
    Gtk::Entry m_entry1, m_entry2, m_entry3, m_entry4, m_entry5;
};

#endif //PAGEROUTECONFIGASSISTANT_H
