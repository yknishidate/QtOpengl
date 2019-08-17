#ifndef TREEVIEW_H
#define TREEVIEW_H

#include <QTreeView>
#include <QStandardItem>
#include <QVBoxLayout>

class TreeView : public QTreeView
{
    Q_OBJECT
public:
    TreeView(QWidget *parent = nullptr);


public slots:
    void addMesh(std::string name);

private:
    QStandardItem * root;
};

#endif // TREEVIEW_H
