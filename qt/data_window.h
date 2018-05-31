#ifndef DATA_WINDOW_H
#define DATA_WINDOW_H

#include <QDialog>
#include "../src/sprite.h"

namespace Ui {
class Data_Window;
}

class Data_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Data_Window(QWidget *parent = 0);
    ~Data_Window();
    PK2Sprite_Prototyyppi* sprite_prototype;

private:
    Ui::Data_Window *ui;
};

#endif // DATA_WINDOW_H
