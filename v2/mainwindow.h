#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include <math.h>

#include "kiss_fft130/kiss_fft.h"

#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionFFT_Test_triggered();

private:
    Ui::MainWindow *ui;

    QCPBars *myBars;

    void TestFFT(const kiss_fft_cpx *in, kiss_fft_cpx *out, int N);

    // Number of samples
    int N;

    QVector<double> x, y;
    QVector<double> amp;

    kiss_fft_cpx *in, *out;

    kiss_fft_cfg cfg;

};

#endif // MAINWINDOW_H
