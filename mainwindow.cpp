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


    resize(QGuiApplication::primaryScreen()->availableSize() * 3 / 5);
}

void MainWindow::setImage(const QImage &newImage)
{
    image = newImage;

    if (image.colorSpace().isValid())
        image.convertToColorSpace(QColorSpace::SRgb);
    imageLabel->setPixmap(QPixmap::fromImage(image));

    scaleFactor = 1.0;

    scrollArea->setVisible(true);

    imageLabel->adjustSize();
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

    const QString message = tr("Opened \"%1\", %2x%3, Depth: %4")
        .arg(QDir::toNativeSeparators(fileName)).arg(image.width()).arg(image.height()).arg(image.depth());
    statusBar()->showMessage(message);
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

