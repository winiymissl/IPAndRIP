#include <gtk/gtk.h>
#include <glib.h>
// 按钮点击的回调函数
void on_button_clicked(GtkWidget *widget, gpointer data) {
    g_print("Button clicked!\n");
}

// 应用程序激活时的回调函数
static void activate(GApplication *app, gpointer user_data) {
    // 创建一个新的窗口
    GtkWidget *window = gtk_application_window_new(GTK_APPLICATION(app));
    gtk_window_set_title(GTK_WINDOW(window), "IP");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    // 创建一个按钮
    GtkWidget *button = gtk_button_new_with_label("Click Me");

    // 连接按钮的点击信号到回调函数
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), NULL);

    // 将按钮添加到窗口
    gtk_window_set_child(GTK_WINDOW(window), button);

    // 显示窗口
    gtk_widget_show(window);
}

void log_handler(const gchar *log_domain, GLogLevelFlags log_level, const gchar *message) {
    // 只处理错误和警告级别的日志
    if (log_level & (G_LOG_LEVEL_ERROR | G_LOG_LEVEL_WARNING)) {
        g_print("Log [%s]: %s\n", log_domain, message);
    }
}

int main(int argc, char *argv[]) {
    // 创建一个新的 GTK 应用程序
    GtkApplication *app = gtk_application_new("com.example.GtkApplication", G_APPLICATION_FLAGS_NONE);

    // 连接 activate 信号到回调函数
    // 连接 activate 信号到回调函数
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // 运行应用程序
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    // 释放应用程序资源
    g_object_unref(app);
    return status;
}