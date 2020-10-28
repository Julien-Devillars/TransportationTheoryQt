#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QImage>
#include <QLabel>
#include <QDebug>
#include <QScrollBar>
#include <QScrollArea>

QT_BEGIN_NAMESPACE


QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void open();

private:
    void createActions();

    QImage image;
    QLabel *imageLabel;
    QScrollArea *scrollArea;

};
#endif // MAINWINDOW_H
