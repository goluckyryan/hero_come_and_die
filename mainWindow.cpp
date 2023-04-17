#include "mainWindow.h"

#include <QPalette>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){

  setWindowTitle("Heros, come and die!");
  setGeometry(500, 100, 500, 1000);
  setFixedSize(500, 1000);
  
  // QPalette palette = this->palette();
  // palette.setColor(QPalette::Window, Qt::black);
  // setPalette(palette);


  QGraphicsScene * scene = new QGraphicsScene(this);
  QGraphicsRectItem * rect = new QGraphicsRectItem(10, 10, 100, 100);
  rect->setBrush(QBrush(Qt::red));
  scene->addItem(rect);
  QGraphicsView * view = new QGraphicsView(scene, this);
  setCentralWidget(view);


  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, [=]() {
            QPointF pos = rect->pos();
            pos.setX(pos.x() + 10); // move 10 pixels to the right
            rect->setPos(pos);
        });
  timer->start(500); // start after 0.5 seconds


}

MainWindow::~MainWindow(){

}
