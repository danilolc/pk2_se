#include "pboxnumber.h"

void PBoxNumber::link_function(func function){
    this->change_function = function;
}

void PBoxNumber::change_var(int value){
    if(type = PBOX_DWORD && variable_dword != NULL)
        *variable_dword = (DWORD)(value + this->offset);
    if(type = PBOX_WORD && variable_word != NULL)
        *variable_word = (WORD)(value + this->offset);
    if(type = PBOX_BYTE && variable_byte != NULL)
        *variable_byte = (BYTE)(value + this->offset);
    if(type = PBOX_int && variable_int != NULL)
        *variable_int = value + this->offset;

    if(change_function != NULL)
        change_function();
}

void PBoxNumber::link_var(DWORD& variable){
    this->variable_dword = &variable;
    this->type = PBOX_DWORD;
    if(this->minimum() < 0) this->setMinimum(0);
    this->PsetValue(variable - this->offset);
}
void PBoxNumber::link_var(WORD& variable){
    this->variable_word = &variable;
    this->type = PBOX_WORD;
    if(this->minimum() < 0) this->setMinimum(0);
    this->setMaximum(65535);
    this->PsetValue(variable - this->offset);
}
void PBoxNumber::link_var(BYTE& variable){
    this->variable_byte = &variable;
    this->type = PBOX_BYTE;
    if(this->minimum() < 0) this->setMinimum(0);
    this->setMaximum(255);
    this->PsetValue(variable - this->offset);
}
void PBoxNumber::link_var(int& variable){
    this->variable_int = &variable;
    this->type = PBOX_int;
    this->PsetValue(variable - this->offset);
}

void PBoxNumber::PsetValue(int value){
    if(this->value() == value)
        this->change_var(value);
    else this->setValue(value);
}

void PBoxNumber::setOffset(int offset){
    this->offset = offset;
}

PBoxNumber::PBoxNumber(QWidget* widget) : QSpinBox(widget){
    variable_dword = NULL;
    variable_word  = NULL;
    variable_byte  = NULL;
    variable_int   = NULL;
    this->offset = 0;
    connect(this, SIGNAL(valueChanged(int)), this, SLOT(change_var(int)));
}

PBoxNumber::~PBoxNumber(){

}
