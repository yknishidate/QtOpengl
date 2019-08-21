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

void TreeView::addMesh(std::string name){
    QStandardItem * newMesh( new QStandardItem( QString::fromStdString(name) ));
    root->appendRow( newMesh );
    qDebug() << "Added New Mesh:" << QString::fromStdString(name);
}

void TreeView::addModel(Model* model){
    root->appendRow(new QStandardItem(QString::fromStdString(model->getName())));
    qDebug() << "Added New Model:" << QString::fromStdString(model->getName());
}
