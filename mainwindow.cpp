#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , imageLabel1(new QLabel)
    , imageLabel2(new QLabel)
{
    setWindowTitle("Transportation Theory");

    Hlayout = new QHBoxLayout(this);

    imageLabel1->setBackgroundRole(QPalette::Base);
    imageLabel1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel1->setScaledContents(true);

    imageLabel2->setBackgroundRole(QPalette::Base);
    imageLabel2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel2->setScaledContents(true);

    mainWidget = new QWidget(this);
    Hlayout = new QHBoxLayout(this);
    mainWidget->setLayout(Hlayout);

    Hlayout->addWidget(imageLabel1);
    Hlayout->addWidget(imageLabel2);

    setCentralWidget(mainWidget);

    createActions();


    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

void MainWindow::setImage(const QImage &newImage)
{
    if(image1.isNull())
    {
        image1 = newImage;

        if (image1.colorSpace().isValid())
            image1.convertToColorSpace(QColorSpace::SRgb);
        imageLabel1->setPixmap(QPixmap::fromImage(image1));


        imageLabel1->adjustSize();
    }
    else if(image2.isNull())
    {
        image2 = newImage;

        if (image2.colorSpace().isValid())
            image2.convertToColorSpace(QColorSpace::SRgb);
        imageLabel2->setPixmap(QPixmap::fromImage(image2));

        imageLabel2->adjustSize();
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(),
                                 tr("Cannot load %1: %2")
                                 .arg(QDir::toNativeSeparators(fileName), reader.errorString()));
        return false;
    }

    setImage(newImage);

    setWindowFilePath(fileName);

    return true;
}

void MainWindow::open()
{
    QFileDialog dialog(this, tr("Open File"));

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
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

void MainWindow::updateActions()
{

}

MainWindow::~MainWindow()
{

}

