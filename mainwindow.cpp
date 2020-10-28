#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , imageLabel(new QLabel)
    , scrollArea(new QScrollArea)
{
    setWindowTitle("Transportation Theory");

    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);

    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(imageLabel);
    scrollArea->setVisible(false);
    setCentralWidget(scrollArea);

    createActions();


}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    //if (!fileName.isEmpty())
        //loadFile(fileName);
}


void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open"), this, &MainWindow::open);
    openAct->setShortcut(QKeySequence::Open); // Enable Ctrl + O shortcut

    fileMenu->addSeparator();

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
}

MainWindow::~MainWindow()
{

}

