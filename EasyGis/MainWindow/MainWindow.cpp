#include "MainWindow.h"

#include "../MapCanvas/MapCanvas.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindowClass())
{
    ui->setupUi(this);
    m_Canvas = new MapCanvas(this);

    setCentralWidget(m_Canvas);
}

MainWindow::~MainWindow()
{
    delete ui;
}
