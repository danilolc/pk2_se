#ifndef PBOXNUMBER_H
#define PBOXNUMBER_H

#include <functional>
#include <iostream>

#include <QSpinBox>
#include "../../src/types.h"

#define PBOX_DWORD 0
#define PBOX_WORD  1
#define PBOX_BYTE  2
#define PBOX_int   3

typedef std::function<void()> func;

class Q_WIDGETS_EXPORT PBoxNumber : public QSpinBox {
    Q_OBJECT

public:
    PBoxNumber(QWidget* widget);
    ~PBoxNumber();

    void link_function(func function);

    void link_var(DWORD& variable);
    void link_var(WORD& variable);
    void link_var(BYTE& variable);
    void link_var(int& variable);

    void setOffset(int offset);
    void UpdateValue();
    void PsetValue(int value);

private:
    DWORD* variable_dword;
    WORD*  variable_word;
    BYTE*  variable_byte;
    int*   variable_int;

    int type;
    int offset;
    func change_function;

private slots:
    void change_var(int value);
};

#endif // PBOXNUMBER_H
