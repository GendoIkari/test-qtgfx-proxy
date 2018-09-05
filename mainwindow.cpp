#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setCentralWidget(&v4Widget);
    setGeometry(100, 100, 1200, 800);
}

MainWindow::~MainWindow()
{
}
