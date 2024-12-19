#include <gtkmm.h>
#include "gtk_page_route_config.h" // 假设这个头文件存在
#include "../mid/gtk_page_route_config_mid.h" // 假设这个头文件存在
using namespace std;

class MyWindow : public Gtk::ApplicationWindow {
public:
    MyWindow();

private:
    void on_next_page_button_clicked();

    Gtk::Stack *stack;
    Gtk::Button *next_page_button;
};

MyWindow::MyWindow() {
    // 创建主窗口
    set_title("GtkStack Example");
    set_default_size(400, 300);

    // 创建一个 GtkStack
    stack = Gtk::make_managed<Gtk::Stack>();
    stack->set_transition_type(Gtk::StackTransitionType::SLIDE_LEFT_RIGHT);

    // 创建页面 1
    // Gtk::Widget page1 = build_routing_table(stack); // 假设这个函数存在
    // page1.set_name("page1");

    // 创建页面 2
    auto page2 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    auto label2 = Gtk::make_managed<Gtk::Label>("This is Page 2");
    page2->append(*label2);
    page2->set_name("page2");

    // 创建页面 3
    auto page3 = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 5);
    auto label3 = Gtk::make_managed<Gtk::Label>("This is Page 3");
    page3->append(*label3);
    page3->set_name("page3");

    // 创建 GtkStackSwitcher
    auto stack_switcher = Gtk::make_managed<Gtk::StackSwitcher>();
    stack_switcher->set_stack(*stack);

    // 创建切换到下一页的按钮
    next_page_button = Gtk::make_managed<Gtk::Button>("Next Page");
    next_page_button->signal_clicked().connect(*this, on_next_page_button_clicked);
    // 创建一个主容器
    auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 5);
    vbox->append(*stack_switcher);
    vbox->append(*stack);
    vbox->append(*next_page_button);

    // 将主容器添加到窗口
    set_child(*vbox);
}

void MyWindow::on_next_page_button_clicked() {
    // 获取当前可见的页面名称
    const gchar *current_page_name = stack->get_visible_child_name().c_str();

    // 打印当前页面名称到日志
    g_log("test", G_LOG_LEVEL_MESSAGE, "current_page_name: %s", current_page_name);

    // 根据当前页面名称决定下一个页面
    if (g_strcmp0(current_page_name, "page1") == 0) {
        stack->set_name("page2"); // 切换到页面 2
    } else if (g_strcmp0(current_page_name, "page2") == 0) {
        stack->set_name("page3"); // 切换到页面 3
    } else {
        stack->set_name("page1"); // 返回到页面 1
    }
}

// 主函数
int main(int argc, char **argv) {
    auto app = Gtk::Application::create("org.example.GtkStackExample");
    return app->run();
}
