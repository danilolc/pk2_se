#include "sc_window.h"
#include "ui_sc_window.h"

SC_Window::SC_Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SC_Window)
{
    ui->setupUi(this);
}

SC_Window::~SC_Window()
{
    delete ui;
}
