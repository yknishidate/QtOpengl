#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QStandardItem>
#include <QVBoxLayout>
#include "model.h"

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *parent = nullptr);


public slots:
    void addMesh(std::string name);
    void addModel(Model *);

private:
    QStandardItem * root;
};

#endif // TREEVIEW_H
