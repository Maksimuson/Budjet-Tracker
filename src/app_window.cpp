#include "app_window.h"
#include "model.h"
#include "storage.h"
#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cctype>





AppWindow::AppWindow() {
    // Инициализация указателей
    salary_entry = nullptr;
    food_entry = nullptr;
    fun_entry = nullptr;
    clothes_entry = nullptr;
    balance_label = nullptr;
    chart_drawing_area = nullptr;
    
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Budget Tracker");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Основной контейнер
    GtkWidget* main_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(window), main_hbox);

    // Левая панель
    GtkWidget* left_panel = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(main_hbox), left_panel, TRUE, TRUE, 0);

    // create_toolbar();
    // gtk_box_pack_start(GTK_BOX(left_panel), toolbar, FALSE, FALSE, 0);

    GtkWidget* input_section = create_input_section();
    gtk_box_pack_start(GTK_BOX(left_panel), input_section, FALSE, FALSE, 0);

    create_table();
    gtk_box_pack_start(GTK_BOX(left_panel), treeview, TRUE, TRUE, 0);

    // Правая панель с диаграммой
    GtkWidget* chart_section = create_chart_section();
    gtk_box_pack_start(GTK_BOX(main_hbox), chart_section, TRUE, TRUE, 0);
}

void AppWindow::show() {
    gtk_widget_show_all(window);
}

void AppWindow::create_toolbar() {
    toolbar = gtk_toolbar_new();

    GtkToolItem* add_income = gtk_tool_button_new(NULL, "Add income");
    GtkToolItem* add_expense = gtk_tool_button_new(NULL, "Add expense");
    GtkToolItem* save_btn = gtk_tool_button_new(NULL, "Save");
    GtkToolItem* load_btn = gtk_tool_button_new(NULL, "Download");

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

GtkWidget* AppWindow::create_input_section() {
    GtkWidget* frame = gtk_frame_new("Управление бюджетом");
    GtkWidget* vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(frame), vbox);

    // Поле для зарплаты
    GtkWidget* salary_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget* salary_label = gtk_label_new("Зарплата:");
    salary_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(salary_entry), "Введите сумму зарплаты");
    gtk_box_pack_start(GTK_BOX(salary_hbox), salary_label, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(salary_hbox), salary_entry, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), salary_hbox, FALSE, FALSE, 0);

    // Таблица расходов
    GtkWidget* expenses_frame = gtk_frame_new("Расходы");
    GtkWidget* expenses_table = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(expenses_frame), expenses_table);

    // Заголовки
    gtk_grid_attach(GTK_GRID(expenses_table), gtk_label_new("Категория"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(expenses_table), gtk_label_new("Сумма"), 1, 0, 1, 1);

    // Food
    gtk_grid_attach(GTK_GRID(expenses_table), gtk_label_new("Food"), 0, 1, 1, 1);
    food_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(food_entry), "0.00");
    gtk_grid_attach(GTK_GRID(expenses_table), food_entry, 1, 1, 1, 1);

    // Fun
    gtk_grid_attach(GTK_GRID(expenses_table), gtk_label_new("Fun"), 0, 2, 1, 1);
    fun_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(fun_entry), "0.00");
    gtk_grid_attach(GTK_GRID(expenses_table), fun_entry, 1, 2, 1, 1);

    // Clothes
    gtk_grid_attach(GTK_GRID(expenses_table), gtk_label_new("Clothes"), 0, 3, 1, 1);
    clothes_entry = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(clothes_entry), "0.00");
    gtk_grid_attach(GTK_GRID(expenses_table), clothes_entry, 1, 3, 1, 1);

    gtk_box_pack_start(GTK_BOX(vbox), expenses_frame, FALSE, FALSE, 0);

    // Поле для отображения остатка
    std::cout << "Создаем поле остатка..." << std::endl;
    GtkWidget* balance_frame = gtk_frame_new("Остаток");
    balance_label = gtk_label_new("0.00");
    std::cout << "balance_label создан: " << balance_label << std::endl;
    
    // Устанавливаем больший размер шрифта для остатка
    PangoAttrList *attrs = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_scale_new(2.0);  // Увеличиваем размер в 2 раза
    pango_attr_list_insert(attrs, attr);
    gtk_label_set_attributes(GTK_LABEL(balance_label), attrs);
    pango_attr_list_unref(attrs);
    
    gtk_container_add(GTK_CONTAINER(balance_frame), balance_label);
    gtk_box_pack_start(GTK_BOX(vbox), balance_frame, FALSE, FALSE, 10);
    std::cout << "Поле остатка добавлено в интерфейс" << std::endl;

    // Подключение обработчиков событий
    if (salary_entry) {
        g_signal_connect(salary_entry, "activate", G_CALLBACK(on_salary_changed), this);
    }
    if (food_entry) {
        g_signal_connect(food_entry, "activate", G_CALLBACK(on_expense_changed), this);
    }
    if (fun_entry) {
        g_signal_connect(fun_entry, "activate", G_CALLBACK(on_expense_changed), this);
    }
    if (clothes_entry) {
        g_signal_connect(clothes_entry, "activate", G_CALLBACK(on_expense_changed), this);
    }

    return frame;
}

GtkWidget* AppWindow::create_chart_section() {
    GtkWidget* frame = gtk_frame_new("Диаграмма расходов");
    chart_drawing_area = gtk_drawing_area_new();
    if (chart_drawing_area) {
        gtk_widget_set_size_request(chart_drawing_area, 300, 300);
        gtk_container_add(GTK_CONTAINER(frame), chart_drawing_area);
        g_signal_connect(chart_drawing_area, "draw", G_CALLBACK(on_draw_chart), this);
    }
    
    return frame;
}


void AppWindow::update_summary() {
    std::cout << "========== update_summary вызван ==========" << std::endl;
    std::cout << "Доход: " << model.totalIncome() << ", Расход: " << model.totalExpense() << ", Баланс: " << model.balance() << std::endl;
    std::cout << "balance_label адрес: " << balance_label << std::endl;
    
    // Обновляем отображение остатка
    if (balance_label) {
        double balance = model.balance();
        std::cout << "Создаем текст для остатка: " << balance << std::endl;
        gchar* balance_text = g_strdup_printf("%.2f", balance);
        std::cout << "Текст создан: " << balance_text << std::endl;
        std::cout << "Устанавливаем текст в label..." << std::endl;
        gtk_label_set_text(GTK_LABEL(balance_label), balance_text);
        std::cout << "Текст установлен!" << std::endl;
        g_free(balance_text);
        std::cout << "Остаток обновлен: " << balance << std::endl;
    } else {
        std::cout << "ОШИБКА: balance_label == NULL!" << std::endl;
    }

    // Обновляем диаграмму
    std::cout << "Вызываем update_chart..." << std::endl;
    update_chart();
    std::cout << "========== update_summary завершен ==========" << std::endl;
}

void AppWindow::update_chart() {
    std::cout << "update_chart начало" << std::endl;
    if (chart_drawing_area) {
        std::cout << "chart_drawing_area существует" << std::endl;
        if (GTK_IS_DRAWING_AREA(chart_drawing_area)) {
            std::cout << "chart_drawing_area это GTK_DRAWING_AREA" << std::endl;
            gtk_widget_queue_draw(chart_drawing_area);
            std::cout << "gtk_widget_queue_draw выполнен" << std::endl;
        } else {
            std::cout << "chart_drawing_area НЕ является GTK_DRAWING_AREA" << std::endl;
        }
    } else {
        std::cout << "chart_drawing_area == NULL" << std::endl;
    }
}


void AppWindow::on_add_income(GtkWidget*, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    Operation op = { "2025-10-12", 1000, "Salary", "income", "Test" };
    self->model.addOperation(op);
    self->update_summary();
}

void AppWindow::on_add_expense(GtkWidget*, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    Operation op = { "2025-10-12", 300, "Food", "expense", "Lunch" };
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

void AppWindow::on_salary_changed(GtkWidget* widget, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    if (!self || !widget) return;
    
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(widget));
    if (!text) return;
    
    std::cout << "Зарплата изменена: " << text << std::endl;
    
    // Удаляем старые записи о зарплате
    self->model.operations.erase(
        std::remove_if(self->model.operations.begin(), self->model.operations.end(),
            [](const Operation& op) { return op.category == "Salary"; }),
        self->model.operations.end()
    );
    
    // Если текст не пустой, добавляем новую запись
    if (strlen(text) > 0) {
        // Простая проверка на валидность числа
        bool is_valid = true;
        for (int i = 0; text[i] != '\0'; i++) {
            if (!isdigit(text[i]) && text[i] != '.' && text[i] != ',') {
                is_valid = false;
                break;
            }
        }
        
        if (is_valid) {
            double amount = atof(text);
            if (amount > 0) {
                // Добавляем новую запись о зарплате
                Operation op = { "2025-01-01", amount, "Salary", "income", "Зарплата" };
                self->model.addOperation(op);
                std::cout << "Зарплата добавлена: " << amount << std::endl;
            }
        }
    }
    
    std::cout << "Баланс: " << self->model.balance() << " (Доход: " << self->model.totalIncome() << ", Расход: " << self->model.totalExpense() << ")" << std::endl;
    self->update_summary();
}

void AppWindow::on_expense_changed(GtkWidget* widget, gpointer data) {
    AppWindow* self = (AppWindow*)data;
    if (!self || !widget) return;
    
    const gchar* text = gtk_entry_get_text(GTK_ENTRY(widget));
    if (!text) return;
    
    // Определяем категорию по виджету
    std::string category;
    if (widget == self->food_entry) category = "Food";
    else if (widget == self->fun_entry) category = "Fun";
    else if (widget == self->clothes_entry) category = "Clothes";
    else return; // Неизвестная категория
    
    std::cout << "Расход " << category << " изменен: " << text << std::endl;
    
    // Удаляем старые записи этой категории
    self->model.operations.erase(
        std::remove_if(self->model.operations.begin(), self->model.operations.end(),
            [&category](const Operation& op) { return op.category == category; }),
        self->model.operations.end()
    );
    
    // Если текст не пустой, добавляем новую запись
    if (strlen(text) > 0) {
        // Простая проверка на валидность числа
        bool is_valid = true;
        for (int i = 0; text[i] != '\0'; i++) {
            if (!isdigit(text[i]) && text[i] != '.' && text[i] != ',') {
                is_valid = false;
                break;
            }
        }
        
        if (is_valid) {
            double amount = atof(text);
            if (amount > 0) {
                // Добавляем новую запись
                Operation op = { "2025-01-01", amount, category, "expense", "Расход" };
                self->model.addOperation(op);
                std::cout << category << " добавлен: " << amount << std::endl;
            }
        }
    }
    
    std::cout << "Баланс: " << self->model.balance() << " (Доход: " << self->model.totalIncome() << ", Расход: " << self->model.totalExpense() << ")" << std::endl;
    self->update_summary();
}

gboolean AppWindow::on_draw_chart(GtkWidget* widget, cairo_t* cr, gpointer data) {
    std::cout << "on_draw_chart вызван" << std::endl;
    AppWindow* self = (AppWindow*)data;
    if (!self || !widget || !cr) {
        std::cout << "on_draw_chart: NULL параметр" << std::endl;
        return FALSE;
    }
    
    std::cout << "on_draw_chart: получаем размеры" << std::endl;
    // Получаем размеры области рисования
    int width = gtk_widget_get_allocated_width(widget);
    int height = gtk_widget_get_allocated_height(widget);
    
    std::cout << "on_draw_chart: width=" << width << ", height=" << height << std::endl;
    if (width <= 0 || height <= 0) return FALSE;
    
    // Очищаем фон
    cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
    cairo_paint(cr);
    
    // Вычисляем расходы по категориям
    double food_amount = 0, fun_amount = 0, clothes_amount = 0;
    
    for (const auto& op : self->model.operations) {
        if (op.type == "expense") {
            if (op.category == "Food") food_amount += op.amount;
            else if (op.category == "Fun") fun_amount += op.amount;
            else if (op.category == "Clothes") clothes_amount += op.amount;
        }
    }
    
    double total = food_amount + fun_amount + clothes_amount;
    
    std::cout << "on_draw_chart: total=" << total << std::endl;
    if (total == 0) {
        // Если нет расходов, показываем сообщение
        std::cout << "on_draw_chart: нет расходов, рисуем сообщение" << std::endl;
        cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
        cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 16);
        cairo_move_to(cr, width/2 - 50, height/2);
        cairo_show_text(cr, "No data");
        std::cout << "on_draw_chart: сообщение нарисовано" << std::endl;
        return TRUE;
    }
    
    // Рисуем круговую диаграмму
    double center_x = width / 2.0;
    double center_y = height / 2.0;
    double radius = std::min(width, height) / 3.0;
    
    double current_angle = 0;
    
    // Food (зеленый)
    if (food_amount > 0) {
        double angle = (food_amount / total) * 2 * M_PI;
        cairo_set_source_rgb(cr, 0.2, 0.8, 0.2);
        cairo_move_to(cr, center_x, center_y);
        cairo_arc(cr, center_x, center_y, radius, current_angle, current_angle + angle);
        cairo_close_path(cr);
        cairo_fill(cr);
        current_angle += angle;
    }
    
    // Fun (синий)
    if (fun_amount > 0) {
        double angle = (fun_amount / total) * 2 * M_PI;
        cairo_set_source_rgb(cr, 0.2, 0.2, 0.8);
        cairo_move_to(cr, center_x, center_y);
        cairo_arc(cr, center_x, center_y, radius, current_angle, current_angle + angle);
        cairo_close_path(cr);
        cairo_fill(cr);
        current_angle += angle;
    }
    
    // Clothes (красный)
    if (clothes_amount > 0) {
        double angle = (clothes_amount / total) * 2 * M_PI;
        cairo_set_source_rgb(cr, 0.8, 0.2, 0.2);
        cairo_move_to(cr, center_x, center_y);
        cairo_arc(cr, center_x, center_y, radius, current_angle, current_angle + angle);
        cairo_close_path(cr);
        cairo_fill(cr);
    }
    
    // Добавляем легенду
    cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
    cairo_select_font_face(cr, "Arial", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
    cairo_set_font_size(cr, 12);
    
    int y_pos = 20;
    if (food_amount > 0) {
        cairo_set_source_rgb(cr, 0.2, 0.8, 0.2);
        cairo_rectangle(cr, 10, y_pos - 10, 15, 10);
        cairo_fill(cr);
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_move_to(cr, 30, y_pos);
        cairo_show_text(cr, ("Food: " + std::to_string((int)food_amount)).c_str());
        y_pos += 20;
    }
    
    if (fun_amount > 0) {
        cairo_set_source_rgb(cr, 0.2, 0.2, 0.8);
        cairo_rectangle(cr, 10, y_pos - 10, 15, 10);
        cairo_fill(cr);
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_move_to(cr, 30, y_pos);
        cairo_show_text(cr, ("Fun: " + std::to_string((int)fun_amount)).c_str());
        y_pos += 20;
    }
    
    if (clothes_amount > 0) {
        cairo_set_source_rgb(cr, 0.8, 0.2, 0.2);
        cairo_rectangle(cr, 10, y_pos - 10, 15, 10);
        cairo_fill(cr);
        cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
        cairo_move_to(cr, 30, y_pos);
        cairo_show_text(cr, ("Clothes: " + std::to_string((int)clothes_amount)).c_str());
    }
    
    return TRUE;
}

void AppWindow::on_update_all(GtkWidget* widget, gpointer data) {
    std::cout << "on_update_all вызван" << std::endl;
    AppWindow* self = (AppWindow*)data;
    if (!self) {
        std::cout << "ОШИБКА: self == NULL" << std::endl;
        return;
    }
    
    std::cout << "Очищаем операции..." << std::endl;
    // Очищаем все старые операции
    self->model.operations.clear();
    
    std::cout << "Обрабатываем зарплату..." << std::endl;
    // Обрабатываем зарплату
    if (self->salary_entry) {
        const gchar* text = gtk_entry_get_text(GTK_ENTRY(self->salary_entry));
        if (text && strlen(text) > 0) {
            bool is_valid = true;
            for (int i = 0; text[i] != '\0'; i++) {
                if (!isdigit(text[i]) && text[i] != '.' && text[i] != ',') {
                    is_valid = false;
                    break;
                }
            }
            
            if (is_valid) {
                double amount = atof(text);
                if (amount > 0) {
                    Operation op = { "2025-01-01", amount, "Salary", "income", "Зарплата" };
                    self->model.addOperation(op);
                }
            }
        }
    }
    
    // Обрабатываем расходы
    GtkWidget* entries[] = {self->food_entry, self->fun_entry, self->clothes_entry};
    const char* categories[] = {"Food", "Fun", "Clothes"};
    
    for (int i = 0; i < 3; i++) {
        if (entries[i]) {
            const gchar* text = gtk_entry_get_text(GTK_ENTRY(entries[i]));
            if (text && strlen(text) > 0) {
                bool is_valid = true;
                for (int j = 0; text[j] != '\0'; j++) {
                    if (!isdigit(text[j]) && text[j] != '.' && text[j] != ',') {
                        is_valid = false;
                        break;
                    }
                }
                
                if (is_valid) {
                    double amount = atof(text);
                    if (amount > 0) {
                        Operation op = { "2025-01-01", amount, categories[i], "expense", "Расход" };
                        self->model.addOperation(op);
                    }
                }
            }
        }
    }
    
    std::cout << "Вызываем update_summary из on_update_all..." << std::endl;
    self->update_summary();
    std::cout << "on_update_all завершен успешно" << std::endl;
}
