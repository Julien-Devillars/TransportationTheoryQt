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

#include "point.h"
QT_BEGIN_NAMESPACE


QT_END_NAMESPACE

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

    QLabel *imageLabel1;
    QLabel *imageLabel2;
    QLabel *imageLabel3;

    double scaleFactor = 1;

    QVBoxLayout* Vlayout;
    QHBoxLayout* Hlayout;

    QWidget* mainWidget;


    QAction *printAct;
    QAction *fitToWindowAct;

};
#endif // MAINWINDOW_H
