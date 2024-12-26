//
// Created by bochen on 2024/12/22.
//

#ifndef PAGEPCAPREAD_H
#define PAGEPCAPREAD_H
#include <gtkmm.h>

Gtk::Box *build_page_read_pcap(Gtk::Box *);

class PagePcapRead {
    PagePcapRead() = default;

public:
    ~PagePcapRead();

    void on_setup_label(const Glib::RefPtr<Gtk::ListItem> &list_item, Gtk::Align halign);

    void on_bind_time(const Glib::RefPtr<Gtk::ListItem> &list_item);

    void on_bind_des_ip(const Glib::RefPtr<Gtk::ListItem> &list_item);
    void on_bind_sour_ip(const Glib::RefPtr<Gtk::ListItem> &list_item);
    void on_bind_des_mac(const Glib::RefPtr<Gtk::ListItem> &list_item);
    void on_bind_sour_mac(const Glib::RefPtr<Gtk::ListItem> &list_item);
    void on_bind_code(const Glib::RefPtr<Gtk::ListItem> &list_item);
    void on_bind_protocol(const Glib::RefPtr<Gtk::ListItem> &list_item);

    static PagePcapRead *getInstance();

    //Child widgets:
    Gtk::Box m_ButtonBox;
    Gtk::Button m_Button_File;
    Gtk::Button m_Button_Folder;
    Gtk::Label m_Label;
    //表格
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::ColumnView m_ColumnView;

    // A Gio::ListStore item.
    class ModelColumns : public Glib::Object {
    public:
        Glib::ustring time;
        Glib::ustring protocol;
        Glib::ustring des_mac;
        Glib::ustring sour_mac;
        Glib::ustring sour_ip;
        Glib::ustring des_ip;
        Glib::ustring code;

        static Glib::RefPtr<ModelColumns> create(const Glib::ustring &time,
                                                 const Glib::ustring &protocol,
                                                 const Glib::ustring &des_mac,
                                                 const Glib::ustring &sour_mac,
                                                 const Glib::ustring &sour_ip,
                                                 const Glib::ustring &des_ip,
                                                 const Glib::ustring &code
        ) {
            return Glib::make_refptr_for_instance<ModelColumns>(
                new ModelColumns(time, protocol, des_mac, sour_mac, sour_ip, des_ip, code));
        }

    protected:
        ModelColumns(const Glib::ustring &time, const Glib::ustring &protocol,
                     const Glib::ustring &des_mac, const Glib::ustring &sour_mac, const Glib::ustring &sour_ip,
                     const Glib::ustring &des_ip, const Glib::ustring &code)
            : time(time),
              protocol(protocol),
              des_mac(des_mac),
              sour_mac(sour_mac),
              sour_ip(sour_ip),
              des_ip(des_ip),
              code(code) {
        }
    };

    Glib::RefPtr<Gio::ListStore<ModelColumns> > m_ListStore;

    //Signal handlers:
    void on_button_file_clicked();

    void on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult> &result,
                               const Glib::RefPtr<Gtk::FileDialog> &dialog);
};

#endif //PAGEPCAPREAD_H
