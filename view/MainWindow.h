//
// Created by bochen on 2024/12/20.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtkmm.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow();

    ~MainWindow() = default;

private:
    Gtk::Stack *stack;
    Gtk::Button *button;

    void connect_buttons();
};

#endif //MAINWINDOW_H
