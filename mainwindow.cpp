#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setCentralWidget(&v4Widget);
}

MainWindow::~MainWindow()
{
}
