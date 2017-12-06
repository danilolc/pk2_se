#ifndef PBOXNUMBER_H
#define PBOXNUMBER_H

#include <QSpinBox>
#include "../../src/types.h"

#define PBOX_DWORD 0
#define PBOX_WORD  1
#define PBOX_BYTE  2
#define PBOX_int   3

class Q_WIDGETS_EXPORT PBoxNumber : public QSpinBox {
    Q_OBJECT

public:
    PBoxNumber(QWidget* widget);
    ~PBoxNumber();
    void link_var(DWORD& variable);
    void link_var(WORD& variable);
    void link_var(BYTE& variable);
    void link_var(int& variable);
    void setOffset(int offset);

private:
    DWORD* variable_dword;
    WORD*  variable_word;
    BYTE*  variable_byte;
    int*   variable_int;

    int type;
    int offset;

private slots:
    void change_var(int value);
};

#endif // PBOXNUMBER_H
