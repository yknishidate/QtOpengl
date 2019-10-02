#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QGroupBox>
#include <QModelIndex>

class GroupBox : public QGroupBox{
    Q_OBJECT
public:
    GroupBox(QWidget *parent = nullptr);

public slots:
    void setVisibleTrue(QModelIndex);


};

#endif // GROUPBOX_H
