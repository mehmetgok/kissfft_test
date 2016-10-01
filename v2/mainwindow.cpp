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

    N=8192;

    x.resize(N); y.resize(N); amp.resize(N/2+1);

    in=(kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx)*N);
    out=(kiss_fft_cpx*)KISS_FFT_MALLOC(sizeof(kiss_fft_cpx)*N);

    for(int i=0; i<N ; i++)
    {
        in[i].r = 0.0f;
        in[i].i = 0.0f;
    }


    // create graph and assign data to it:
    ui->qwSignal->addGraph();

    ui->qwFFT->addGraph();

    // give the axes some labels:
    ui->qwSignal->xAxis->setLabel("x");
    ui->qwSignal->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->qwSignal->yAxis->setRange(-5, 75);
    ui->qwSignal->xAxis->setRange(0, 8192);

    // give the axes some labels:
    ui->qwFFT->xAxis->setLabel("x");
    ui->qwFFT->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
    ui->qwFFT->yAxis->setRange(0, 2);
    ui->qwFFT->xAxis->setRange(0, 256);

    ui->qwFFT->xAxis->setTickStep(4.0);
    ui->qwFFT->xAxis->setTicks(true);


    myBars = new QCPBars(ui->qwFFT->xAxis, ui->qwFFT->yAxis);
    ui->qwFFT->addPlottable(myBars);

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
       in[i].r = 3*sin(2 * M_PI * 50 * i / N) + 2*sin(2 * M_PI * 30 * i / N) + rand()/5000;
       // in[i].i = 0;

       x[i] = i;
       y[i] = in[i].r;
    }

    ui->qwSignal->graph(0)->setData(x, y);
    ui->qwSignal->replot();

    TestFFT(in, out, N);

    for (int i = 1; i < N/2; i++)
       amp[i] = sqrt(out[i].i*out[i].i+out[i].r*out[i].r)/N;

    // ui->qwFFT->graph(0)->setData(x, amp);

    myBars->setData(x, amp);
    ui->qwFFT->replot();

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
