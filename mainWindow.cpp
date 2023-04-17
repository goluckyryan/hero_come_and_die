#include "mainWindow.h"

#include <QPalette>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){

  setWindowTitle("Heros, come and die!");
  setGeometry(500, 100, 1000, 500);
  
  // QPalette palette = this->palette();
  // palette.setColor(QPalette::Window, Qt::black);
  // setPalette(palette);



  QGraphicsScene scene;
  QGraphicsRectItem rect(0, 0, 100, 100);
  rect.setBrush(QBrush(Qt::red));
  scene.addItem(&rect);

  QGraphicsView view(&scene);
  view.setDragMode(QGraphicsView::ScrollHandDrag);

  setCentralWidget(&view);

}

MainWindow::~MainWindow(){

}
