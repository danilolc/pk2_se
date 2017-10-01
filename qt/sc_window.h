#ifndef SC_WINDOW_H
#define SC_WINDOW_H

#include <QMainWindow>

namespace Ui {
class SC_Window;
}

class SC_Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit SC_Window(QWidget *parent = 0);
    ~SC_Window();

private:
    Ui::SC_Window *ui;
};

#endif // SC_WINDOW_H
