//
// Created by bochen on 2024/12/20.
//

#include "MainWindow.h"
#include "PageRouteConfig.h"
#include "PageRouteConfigAssistant.h"

void MainWindow::connect_buttons() {
    button->signal_clicked().connect([this]() {
        // 根据当前页面切换到下一个页面
        if (stack->get_visible_child_name() == "Page 1") {
            stack->set_visible_child("Page 2");
        } else if (stack->get_visible_child_name() == "Page 2") {
            stack->set_visible_child("Page 3");
        } else {
            stack->set_visible_child("Page 1");
        }
    });
}

MainWindow::MainWindow() {
    set_title("IP");
    set_default_size(400, 300);

    stack = Gtk::make_managed<Gtk::Stack>();

    auto page1 = build_page_route_config(Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL));
    page1->set_margin(10);

    auto page2 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    page2->set_margin(10);
    auto label2 = Gtk::make_managed<Gtk::Label>("Page 2");
    page2->append(*label2);

    auto page3 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    page3->set_margin(10);
    auto label3 = Gtk::make_managed<Gtk::Label>("Page 3");
    page3->append(*label3);

    stack->add(*page1, "Page 1");
    stack->add(*page2, "Page 2");
    stack->add(*page3, "Page 3");

    auto stack_switcher = Gtk::make_managed<Gtk::StackSwitcher>();
    stack_switcher->set_stack(*stack);

    button = Gtk::make_managed<Gtk::Button>("Next Page");

    auto main_box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    main_box->append(*stack_switcher);
    main_box->append(*stack);
    main_box->append(*button);

    connect_buttons();
    set_child(*main_box);
}