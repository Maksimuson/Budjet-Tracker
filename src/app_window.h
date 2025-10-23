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
    
    // Новые элементы интерфейса
    GtkWidget* salary_entry;
    GtkWidget* food_entry;
    GtkWidget* fun_entry;
    GtkWidget* clothes_entry;
    GtkWidget* balance_label;
    GtkWidget* chart_drawing_area;

    Model model;

public:
    AppWindow();
    void show();
private:
    void create_toolbar();
    void create_table();
    GtkWidget* create_input_section();
    GtkWidget* create_chart_section();
    void update_summary();
    void update_chart();

    static void on_add_income(GtkWidget*, gpointer);
    static void on_add_expense(GtkWidget*, gpointer);
    static void on_save(GtkWidget*, gpointer);
    static void on_load(GtkWidget*, gpointer);
    static void on_salary_changed(GtkWidget*, gpointer);
    static void on_expense_changed(GtkWidget*, gpointer);
    static void on_update_all(GtkWidget*, gpointer);
    static gboolean on_draw_chart(GtkWidget*, cairo_t*, gpointer);
};
