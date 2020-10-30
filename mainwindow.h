#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QColorSpace>
#include <QLabel>
#include <QDebug>
#include <QScrollBar>
#include <QScrollArea>
#include <QImageReader>
#include <QMessageBox>
#include <QStandardPaths>
#include <QImageWriter>
#include <QGuiApplication>
#include <QScreen>
#include <QRandomGenerator>
#include <QThread>
#include <QMenuBar>

#include "point.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool loadFile(const QString &fileName);

private slots:
    void open();
    void transportation();

private:
    void createActions();
    void updateActions();
    void setImage(const QImage &newImage);

    QImage image1;
    QImage image2;
    QImage image3;
    QImage image4;

    QLabel *imageLabel1;
    QLabel *imageLabel2;
    QLabel *imageLabel3;
    QLabel *imageLabel4;

    double scaleFactor = 1;

    QVBoxLayout* Vlayout;
    QHBoxLayout* Hlayout1;
    QHBoxLayout* Hlayout2;

    QWidget* mainWidget;

    bool firstTransport = true;

    QAction *printAct;
    QAction *fitToWindowAct;

};
#endif // MAINWINDOW_H
