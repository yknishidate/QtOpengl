#include "treeview.h"
#include <QDebug>


TreeView::TreeView(QWidget *parent)
    : QTreeView(),
      root( new QStandardItem( "root" ) )
{
  QStandardItemModel * model( new QStandardItemModel() ) ;

  setHeaderHidden(true);
  model->appendRow( root ) ;
  this->setModel( model ) ;

  this->setRootIndex( root->index() ) ;

  this->expandAll() ;
}

void TreeView::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Delete){
        QModelIndex index_selected = currentIndex();
        int row = index_selected.row();
        qDebug() << "Deleted Model :" << row;
        this->root->removeRow(index_selected.row());
        emit modelDeleted(row);
    }
}

void TreeView::addMesh(std::string name){
    QStandardItem * newMesh( new QStandardItem( QString::fromStdString(name) ));
    root->appendRow( newMesh );
    qDebug() << "Added New Mesh:" << QString::fromStdString(name);
}

void TreeView::addModel(Model* model){
    root->appendRow(new QStandardItem(QString::fromStdString(model->getName())));
    qDebug() << "Added Model   :" << QString::fromStdString(model->getName());
}
