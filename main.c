#include <gtk/gtk.h>

// 按钮点击事件处理函数
static void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("按钮被点击了！\n");
}

// 应用程序激活时的回调
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *button;

    // 创建一个新窗口
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "GTK4 示例");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    // 创建一个按钮
    button = gtk_button_new_with_label("点击我");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // 将按钮添加到窗口
    gtk_window_set_child(GTK_WINDOW(window), button);

    // 显示窗口
    gtk_widget_show(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;

    // 创建一个新的 GTK 应用程序
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // 运行应用程序
    status = g_application_run(G_APPLICATION(app), argc, argv);

    // 释放应用程序
    g_object_unref(app);

    return status;
}