#include "pboxbool.h"

void PBoxBool::change_var(bool value){
    if(variable != NULL)
        *variable = value;
}

void PBoxBool::link_var(bool& variable){
    this->variable = &variable;
    this->setChecked(variable);
}

PBoxBool::PBoxBool(QFrame*& frame) : QCheckBox(frame){
    variable = NULL;
    connect(this, SIGNAL(toggled(bool)), this, SLOT(change_var(bool)));
}

PBoxBool::~PBoxBool(){

}
