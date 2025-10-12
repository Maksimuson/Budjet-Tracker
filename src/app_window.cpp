#include <gtk/gtk.h>       
#include <string>          
#include <sstream>
#include <iostream>
#include "app_window.h"


AppWindow::AppWindow() {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Budjet Tracker");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    create_toolbar();
    gtk_box_pack_start(GTK_BOX(vbox), toolbar, FALSE, FALSE, 0);

    create_table();
    gtk_box_pack_start(GTK_BOX(vbox), treeview, TRUE, TRUE, 0);

    summary_label = gtk_label_new("Баланс: 0 | Доходи: 0 | Витрати: 0");
    gtk_box_pack_end(GTK_BOX(vbox), summary_label, FALSE, FALSE, 0);
}

void AppWindow::show() {
    gtk_widget_show_all(window);
}

void AppWindow::create_toolbar() {
    toolbar = gtk_toolbar_new();

    GtkToolItem* add_income = gtk_tool_button_new(NULL, "Додати дохід");
    GtkToolItem* add_expense = gtk_tool_button_new(NULL, "Додати витрату");
    GtkToolItem* save_btn = gtk_tool_button_new(NULL, "Зберегти");
    GtkToolItem* load_btn = gtk_tool_button_new(NULL, "Завантажити");

    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), add_income, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), add_expense, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), save_btn, -1);
    gtk_toolbar_insert(GTK_TOOLBAR(toolbar), load_btn, -1);

    g_signal_connect(add_income, "clicked", G_CALLBACK(on_add_income), this);
    g_signal_connect(add_expense, "clicked", G_CALLBACK(on_add_expense), this);
    g_signal_connect(save_btn, "clicked", G_CALLBACK(on_save), this);
    g_signal_connect(load_btn, "clicked", G_CALLBACK(on_load), this);
}

void AppWindow::create_table() {
    treeview = gtk_tree_view_new();
}


void AppWindow::update_summary() {
    // g_strdup_printf works like sprintf, but returns gchar*
    gchar* text = g_strdup_printf(
        "Баланс: %.2f | Доходи: %.2f | Витрати: %.2f",
        static_cast<double>(model.balance()),
        static_cast<double>(model.totalIncome()),
        static_cast<double>(model.totalExpense())
    );

    gtk_label_set_text(GTK_LABEL(summary_label), text);
    g_free(text); // free the memory allocated by g_strdup_printf
}


void AppWindow::on_add_income(GtkWidget*, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    Operation op = { "2025-10-12", 1000, "Зарплата", "income", "Тест" };
    self->model.addOperation(op);
    self->update_summary();
}

void AppWindow::on_add_expense(GtkWidget*, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    Operation op = { "2025-10-12", 300, "Їжа", "expense", "Обід" };
    self->model.addOperation(op);
    self->update_summary();
}

void AppWindow::on_save(GtkWidget*, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    Storage::save("data/operations.csv", self->model);
}

void AppWindow::on_load(GtkWidget*, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    Storage::load("data/operations.csv", self->model);
    self->update_summary();
}
