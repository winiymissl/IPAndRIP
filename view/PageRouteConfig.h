//
// Created by bochen on 2024/12/20.
//

#ifndef PAGE_ROUTE_CONFIG_H
#define PAGE_ROUTE_CONFIG_H

#include <gtkmm.h>

#include "PageRouteConfigAssistant.h"

Gtk::Box *build_page_route_config(Gtk::Box *);

class PageRouteConfig {
public:
    static PageRouteConfig * &getInstance();

    PageRouteConfig() = default;

    ~PageRouteConfig() = default;

    // Signal handlers:
    void on_button_clicked_add();

    void on_button_clicked_remove();

    void on_assistant_apply();

    void on_setup_label(const Glib::RefPtr<Gtk::ListItem> &list_item, Gtk::Align halign);

    void on_bind_id(const Glib::RefPtr<Gtk::ListItem> &list_item);

    void on_bind_route_type(const Glib::RefPtr<Gtk::ListItem> &list_item);

    void on_bind_destination_network(const Glib::RefPtr<Gtk::ListItem> &list_item);

    void on_bind_subnet_mask(const Glib::RefPtr<Gtk::ListItem> &list_item);

    void on_bind_next_hop(const Glib::RefPtr<Gtk::ListItem> &list_item);

    void on_bind_outgoing_interface(const Glib::RefPtr<Gtk::ListItem> &list_item);

    // A Gio::ListStore item.
    class ModelColumns : public Glib::Object {
    public:
        /**
        *   string route_type;
        *   string destination_network;
        *   string subnet_mask;
        *   string next_hop;
        *   string outgoing_interface;
         */
        Glib::ustring id;
        Glib::ustring route_type;
        Glib::ustring destination_network;
        Glib::ustring subnet_mask;
        Glib::ustring next_hop;
        Glib::ustring outgoing_interface;

        static Glib::RefPtr<ModelColumns> create(const Glib::ustring &id,
                                                 const Glib::ustring &route_type,
                                                 const Glib::ustring &destination_network,
                                                 const Glib::ustring &subnet_mask,
                                                 const Glib::ustring &next_hop,
                                                 const Glib::ustring &outgoing_interface
        ) {
            return Glib::make_refptr_for_instance<ModelColumns>(
                new ModelColumns(id, route_type, destination_network, subnet_mask, next_hop, outgoing_interface));
        }

    protected:
        ModelColumns(const Glib::ustring &id, const Glib::ustring &route_type,
                     const Glib::ustring &destination_network, const Glib::ustring &subnet_mask,
                     const Glib::ustring &next_hop,
                     const Glib::ustring &outgoing_interface) : id(id), route_type(route_type),
                                                                destination_network(destination_network),
                                                                subnet_mask(subnet_mask), next_hop(next_hop),
                                                                outgoing_interface(outgoing_interface) {
        }
    };

    // Child widgets:
    Gtk::Box m_VBox;
    Gtk::ScrolledWindow m_ScrolledWindow;
    Gtk::ColumnView m_ColumnView;
    Gtk::Button m_Button_Add;
    Gtk::Button m_Button_Remove;
    PageRouteConfigAssistant m_assistant;

    Glib::RefPtr<Gio::ListStore<ModelColumns> > m_ListStore;
};

#endif
