#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifndef M_PI
    #define M_PI 3.14159265358979324
#endif


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    N=2048;

    x.resize(N); y.resize(N);
    ampx.resize(N/2+1); amp.resize(N/2+1);

    in=(kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx)*N);
    out=(kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx)*N);

    for(int i=0; i<N ; i++)
    {
        in[i].r = 0.0f;
        in[i].i = 0.0f;
    }


    // create graph and assign data to it:
    ui->qwSignal->addGraph();
    // ui->qwSignal->setOpenGl(true);

    ui->qwFFT->addGraph();
    // ui->qwFFT->setOpenGl(true);

    // give the axes some labels:
    ui->qwSignal->xAxis->setLabel("x");
    ui->qwSignal->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->qwSignal->yAxis->setRange(-5, 25);
    ui->qwSignal->xAxis->setRange(0, N);

    // give the axes some labels:
    ui->qwFFT->xAxis->setLabel("x");
    ui->qwFFT->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->qwFFT->yAxis->setRange(0, 2);
    ui->qwFFT->xAxis->setRange(0, N/2);

 //   ui->qwFFT->xAxis->setTickStep(4.0);

    ui->qwFFT->xAxis->setTicks(true);


    myBars = new QCPBars(ui->qwFFT->xAxis, ui->qwFFT->yAxis);
  //  ui->qwFFT->addPlottable(myBars);

}

MainWindow::~MainWindow()
{
    kiss_fft_cleanup();

    free(in);
    free(out);

    delete ui;
}

void MainWindow::on_actionFFT_Test_triggered()
{




    for (int i = 0; i < N; i++)
    {
       in[i].r = 3*sin(2 * M_PI * 50 * i / N) + 2*sin(2 * M_PI * 30 * i / N) + 2*sin(2 * M_PI * 5 * i / N) + rand()/5000;
       // in[i].i = 0;

       x[i] = i;
       y[i] = in[i].r;
    }

    for (int i = 0; i < N/2+1; i++)
    {
        ampx[i] = i/1.0;
    }


    ui->qwSignal->graph(0)->setData(x, y);
    ui->qwSignal->replot();

     timer.start();

    TestFFT(in, out, N);

    nanoSec = timer.nsecsElapsed();


    for (int i = 1; i < N/2; i++)
       amp[i] = sqrt(out[i].i*out[i].i+out[i].r*out[i].r)/N;

    // ui->qwFFT->graph(0)->setData(x, amp);

    myBars->setData(ampx, amp);
    ui->qwFFT->replot();


    qDebug("Elapsed: %f us", nanoSec/1000.0);

}

void MainWindow::TestFFT(const kiss_fft_cpx *in, kiss_fft_cpx *out, int N)
{


     if ((cfg = kiss_fft_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
     {

        kiss_fft(cfg, in, out);
        free(cfg);

     }
     else
     {

       // qDebug("not enough memory\n");
       // exit(-1);
     }
}

void MainWindow::on_pushButton_clicked()
{
    this->on_actionFFT_Test_triggered();
}
