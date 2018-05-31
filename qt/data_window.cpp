#include "data_window.h"
#include "ui_data_window.h"

Data_Window::Data_Window(QWidget *parent) : QDialog(parent), ui(new Ui::Data_Window) {
    ui->setupUi(this);
}

Data_Window::~Data_Window() {
    delete ui;
}
