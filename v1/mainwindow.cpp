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

  myBars = new QCPBars(ui->qwFFT->xAxis, ui->qwFFT->yAxis);
  ui->qwFFT->addPlottable(myBars);



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFFT_Test_triggered()
{
    int N = 8192;

    QVector<double> x(8193), y(8193); // initialize with entries 0..100

    QVector<double> amp(8193);

    kiss_fft_cpx in[N], out[N];

    for (int i = 0; i < N; i++)
    {
       in[i].r = sin(2 * M_PI * 50 * i / N) + 2*sin(2 * M_PI * 30 * i / N) + rand()/2000;
       in[i].i = 0;

       x[i] = i;
       y[i] = in[i].r;
    }
     ui->qwSignal->graph(0)->setData(x, y);
     ui->qwSignal->replot();

    TestFFT(in, out, N);


   for (int i = 0; i < N/2; i++)
   {
       amp[i] = sqrt(out[i].i*out[i].i+out[i].r*out[i].r)/N;

   }

  // ui->qwFFT->graph(0)->setData(x, amp);

    myBars->setData(x, amp);

   ui->qwFFT->replot();


}

void MainWindow::TestFFT(const kiss_fft_cpx *in, kiss_fft_cpx *out, int N)
{
     kiss_fft_cfg cfg;

     if ((cfg = kiss_fft_alloc(N, 0/*is_inverse_fft*/, NULL, NULL)) != NULL)
      {
        size_t i;

        kiss_fft(cfg, in, out);
        free(cfg);


        /*
        for (i = 0; i < 52; i++)
          qDebug(" in[%2zu] = %+f , %+f    "
                 "out[%2zu] = %+f , %+f\n",
                 i, in[i].r, in[i].i,
                 i, out[i].r, out[i].i);
                */




      }
      else
      {
        qDebug("not enough memory\n");
        exit(-1);
      }

       kiss_fft_cleanup();
}
