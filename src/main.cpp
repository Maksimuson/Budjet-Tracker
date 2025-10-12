#include <gtk/gtk.h>
#include "app_window.h"

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    AppWindow window;
    window.show();
    gtk_main();
    return 0;
}
