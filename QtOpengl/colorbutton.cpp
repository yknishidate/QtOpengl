#include "colorbutton.h"

ColorButton::ColorButton(QWidget *parent)
{

}

void ColorButton::setColor(QColor color){
    if(color.isValid()){
        QPalette pal = this->palette();
        pal.setColor(QPalette::Button, color);
        this->setPalette(pal);
        this->update();
    }
}
