#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "networktopology.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ui->graphicsView->addNode(100, -100, "KCE", 1);
//    ui->graphicsView->addNode(0, 0,"FCB", 2);
//    ui->graphicsView->addNode(0, 100,"FCB", 4);
//    ui->graphicsView->addNode(0, 200,"FCB", 3);

//    ui->graphicsView->addNode(100, 300, "KCE", 5);
//    ui->graphicsView->addNode(0, 400,"FCB", 6);
//    ui->graphicsView->addNode(0, 500,"FCB", 7);
//    ui->graphicsView->addNode(0, 600,"FCB", 8);
//    ui->graphicsView->addNode(100, 700, "KCE", 9);

//    ui->graphicsView->addEdge(1, 2);
//    ui->graphicsView->addEdge(2, 4);
//    ui->graphicsView->addEdge(4, 3);
//    ui->graphicsView->addEdge(6, 7);
//    ui->graphicsView->addEdge(7, 8);
//    ui->graphicsView->addEdge(1, 5);
//    ui->graphicsView->addEdge(5, 6);
//    ui->graphicsView->addEdge(3, 5);
//    ui->graphicsView->addEdge(9, 5);
//    ui->graphicsView->addEdge(9, 8);

    //NetworkTopology nt;
    connect(ui->actionClose,&QAction::triggered,this,QCoreApplication::quit);
    connect(ui->actionAllign_to_grid,&QAction::triggered,[this]{ui->graphicsView->allignToGrid();});
    connect(ui->actionFit_to_screen,&QAction::triggered,[this]{ui->graphicsView->fitInView(ui->graphicsView->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

