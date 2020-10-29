#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Transportation Theory");


    imageLabel1 = new QLabel();
    imageLabel1->setBackgroundRole(QPalette::Base);
    imageLabel1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel1->setScaledContents(true);

    imageLabel2 = new QLabel();
    imageLabel2->setBackgroundRole(QPalette::Base);
    imageLabel2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel2->setScaledContents(true);

    imageLabel3 = new QLabel();
    imageLabel3->setBackgroundRole(QPalette::Base);
    imageLabel3->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel3->setScaledContents(true);

    imageLabel4 = new QLabel();
    imageLabel4->setBackgroundRole(QPalette::Base);
    imageLabel4->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel4->setScaledContents(true);

    mainWidget = new QWidget(this);

    Vlayout = new QVBoxLayout(this);
    Hlayout1 = new QHBoxLayout(this);
    Hlayout2 = new QHBoxLayout(this);


    Hlayout1->addWidget(imageLabel1);
    Hlayout1->addWidget(imageLabel2);

    Hlayout2->addWidget(imageLabel3);
    Hlayout2->addWidget(imageLabel4);

    Vlayout->addLayout(Hlayout1);
    Vlayout->addLayout(Hlayout2);

    mainWidget->setLayout(Vlayout);

    setCentralWidget(mainWidget);

    createActions();


    resize(QGuiApplication::primaryScreen()->availableSize());
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

void MainWindow::transportation()
{

    uchar* bits1 = image1.bits();
    uchar* bits2 = image2.bits();

    QList<Point> im1;
    QList<Point> im2;

    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, 1.0);


    if(image1.width() * image1.height() != image2.width() * image2.height())
        return;

    for(int i = 0 ; i < image1.width() * image1.height() * 4; i +=4)
    {
        im1.push_back(Point(bits1[i], bits1[i+1], bits1[i+2]));
        im2.push_back(Point(bits2[i], bits2[i+1], bits2[i+2]));
    }


    QList<QPair<double, int>> scalarIdx1;
    QList<QPair<double, int>> scalarIdx2;

    const int ITERATIONS = 10;

    for(int k = 0 ; k < ITERATIONS ; ++k)
    {
        qDebug() << "K = " << k << "\n";



        double r1 = distribution(generator);
        double r2 = distribution(generator);
        double r3 = distribution(generator);
        double r4 = distribution(generator);

        double x = sqrt(-2.0 * log(r1)) * cos(2.0 * M_PI * r2);
        double y = sqrt(-2.0 * log(r1)) * sin(2.0 * M_PI * r2);
        double z = sqrt(-2.0 * log(r3)) * cos(2.0 * M_PI * r4);

        Point A(x,y,z);
        A.normalize(1.0);

        scalarIdx1.clear();
        scalarIdx2.clear();

        for(int i = 0 ; i < image1.width() * image1.height() ; ++i)
        {
            scalarIdx1.push_back(QPair<double, int>(A.dot(im1[i]), i));
            scalarIdx2.push_back(QPair<double, int>(A.dot(im2[i]), i));
        }

        std::sort(scalarIdx1.begin(), scalarIdx1.end());
        std::sort(scalarIdx2.begin(), scalarIdx2.end());

        for(int i = 0 ; i < scalarIdx1.size() ; ++i)
        {
            double diff = scalarIdx2[i].first - scalarIdx1[i].first;
            Point B = A;
            B.normalize(diff);

            Point p = Point(im1[scalarIdx1[i].second]);
            im1[scalarIdx1[i].second].x = p.x + B.x;
            im1[scalarIdx1[i].second].y = p.y + B.y;
            im1[scalarIdx1[i].second].z = p.z + B.z;
        }
    }

    image3 = QImage(image1.width(), image1.height(), QImage::Format_RGB32);

    for(int i = 0 ; i < image1.height() ; ++i)
    {
        for(int j = 0 ; j < image1.width() ; ++j)
        {
            int idx = (i * image1.width() + j);

            double b = qMax(qMin(255.0, im1[idx].x), 0.0);
            double g = qMax(qMin(255.0, im1[idx].y), 0.0);
            double r = qMax(qMin(255.0, im1[idx].z), 0.0);

            image3.setPixel(j, i, qRgb(r, g, b));
        }
    }

    if (image3.colorSpace().isValid())
        image3.convertToColorSpace(QColorSpace::SRgb);
    imageLabel3->setPixmap(QPixmap::fromImage(image3));
    imageLabel3->adjustSize();

    delete bits1;
    delete bits2;

}

void MainWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));

    QAction *openAct = fileMenu->addAction(tr("&Open"), this, &MainWindow::open);
    openAct->setShortcut(QKeySequence::Open); // Enable Ctrl + O shortcut

    fileMenu->addSeparator();
    menuBar()->addAction(tr("&Transport"), this, &MainWindow::transportation);

    QAction *exitAct = fileMenu->addAction(tr("E&xit"), this, &QWidget::close);
    exitAct->setShortcut(tr("Ctrl+Q"));
}

void MainWindow::updateActions()
{

}

MainWindow::~MainWindow()
{

}

