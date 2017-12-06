//A replacement to Qt Boxes to link a pointer of a variable to automatcaly change it.

#ifndef PBOXBOOL_H
#define PBOXBOOL_H

#include <QCheckBox>
#include <QString>
#include <QFrame>

class Q_WIDGETS_EXPORT PBoxBool : public QCheckBox {
    Q_OBJECT

public:
    PBoxBool(QFrame*& frame);
    ~PBoxBool();
    void link_var(bool& variable);

private:
    bool* variable;

private slots:
    void change_var(bool value);

};


#endif // PBOXBOOL_H
