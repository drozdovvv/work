#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_openGl ( new OpenGlWidget(this))
{
    ui->setupUi(this);

    //m_openGl->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
