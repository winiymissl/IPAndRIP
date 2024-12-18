#include <gtk/gtk.h> // 包含 GTK 库的头文件

// 按钮点击回调函数，用于切换到下一个页面
static void on_next_page_button_clicked(GtkButton *button, gpointer user_data) {
    GtkStack *stack = GTK_STACK(user_data); // 将 user_data 转换为 GtkStack 指针

    // 获取当前可见的页面名称
    const gchar *current_page_name = gtk_stack_get_visible_child_name(stack);

    // 打印当前页面名称到日志
    g_log("test", G_LOG_LEVEL_MESSAGE, "current_page_name: %s", current_page_name);

    // 根据当前页面名称决定下一个页面
    if (g_strcmp0(current_page_name, "page1") == 0) {
        gtk_stack_set_visible_child_name(stack, "page2"); // 切换到页面 2
    } else if (g_strcmp0(current_page_name, "page2") == 0) {
        gtk_stack_set_visible_child_name(stack, "page3"); // 切换到页面 3
    } else {
        gtk_stack_set_visible_child_name(stack, "page1"); // 返回到页面 1
    }
}

// 应用程序激活时的回调函数
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window; // 主窗口
    GtkWidget *stack; // GtkStack 容器
    GtkWidget *stack_switcher; // GtkStackSwitcher 控件
    GtkWidget *next_page_button; // 切换到下一页的按钮

    // 创建主窗口
    window = gtk_application_window_new(app); // 创建一个新的应用窗口
    gtk_window_set_title(GTK_WINDOW(window), "GtkStack Example"); // 设置窗口标题
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300); // 设置窗口默认大小

    // 创建一个 GtkStack
    stack = gtk_stack_new(); // 创建一个新的 GtkStack
    gtk_stack_set_transition_type(GTK_STACK(stack), GTK_STACK_TRANSITION_TYPE_CROSSFADE); // 设置切换效果

    // 创建页面 1
    GtkWidget *page1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 创建一个垂直盒子作为页面 1
    GtkWidget *label1 = gtk_label_new("This is Page 1"); // 创建一个标签
    gtk_box_append(GTK_BOX(page1), label1); // 将标签添加到页面 1
    gtk_stack_add_named(GTK_STACK(stack), page1, "page1"); // 将页面 1 添加到 GtkStack，并命名为 "page1"

    // 创建页面 2
    GtkWidget *page2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 创建一个垂直盒子作为页面 2
    GtkWidget *label2 = gtk_label_new("This is Page 2"); // 创建一个标签
    gtk_box_append(GTK_BOX(page2), label2); // 将标签添加到页面 2
    gtk_stack_add_named(GTK_STACK(stack), page2, "page2"); // 将页面 2 添加到 GtkStack，并命名为 "page2"

    // 创建页面 3
    GtkWidget *page3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 创建一个垂直盒子作为页面 3
    GtkWidget *label3 = gtk_label_new("This is Page 3"); // 创建一个标签
    gtk_box_append(GTK_BOX(page3), label3); // 将标签添加到页面 3
    gtk_stack_add_named(GTK_STACK(stack), page3, "page3"); // 将页面 3 添加到 GtkStack，并命名为 "page3"

    // 创建 GtkStackSwitcher
    stack_switcher = gtk_stack_switcher_new(); // 创建一个新的 GtkStackSwitcher
    gtk_stack_switcher_set_stack(GTK_STACK_SWITCHER(stack_switcher), GTK_STACK(stack)); // 将 GtkStack 关联到 GtkStackSwitcher

    // 创建切换到下一页的按钮
    next_page_button = gtk_button_new_with_label("Next Page"); // 创建一个按钮，标签为 "Next Page"
    g_signal_connect(next_page_button, "clicked", G_CALLBACK(on_next_page_button_clicked), stack); // 连接按钮点击信号到回调函数

    // 创建一个主容器
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5); // 创建一个垂直盒子作为主容器
    gtk_box_append(GTK_BOX(vbox), stack_switcher); // 将 GtkStackSwitcher 添加到主容器
    gtk_box_append(GTK_BOX(vbox), stack); // 将 GtkStack 添加到主容器
    gtk_box_append(GTK_BOX(vbox), next_page_button); // 将按钮添加到主容器

    // 将主容器添加到窗口
    gtk_window_set_child(GTK_WINDOW(window), vbox); // 设置窗口的内容为主容器

    // 显示所有控件
    gtk_widget_show(window); // 显示窗口及其所有子控件
}

// 主函数
int main(int argc, char **argv) {
    GtkApplication *app; // 应用程序对象
    int status; // 应用程序状态

    // 创建一个新的 GtkApplication
    app = gtk_application_new("org.example.GtkStackExample", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL); // 连接激活信号到回调函数
    status = g_application_run(G_APPLICATION(app), argc, argv); // 运行应用程序
    g_object_unref(app); // 释放应用程序对象
    return status; // 返回应用程序状态
}