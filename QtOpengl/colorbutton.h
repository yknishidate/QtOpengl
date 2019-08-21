#ifndef COLORBUTTON_H
#define COLORBUTTON_H
#include <QPushButton>

class ColorButton : public QPushButton
{
    Q_OBJECT
public:
    ColorButton(QWidget *parent = nullptr);

public slots:
    void setColor(QColor color);
};

#endif // COLORBUTTON_H
