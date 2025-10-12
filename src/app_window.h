#pragma once
#include <gtk/gtk.h>
#include "model.h"
#include "storage.h"

class AppWindow {
private:
    GtkWidget* window;
    GtkWidget* toolbar;
    GtkWidget* treeview;
    GtkWidget* summary_label;

    Model model;

public:
    AppWindow();
    void show();
private:
    void create_toolbar();
    void create_table();
    void update_summary();

    static void on_add_income(GtkWidget*, gpointer);
    static void on_add_expense(GtkWidget*, gpointer);
    static void on_save(GtkWidget*, gpointer);
    static void on_load(GtkWidget*, gpointer);
};
