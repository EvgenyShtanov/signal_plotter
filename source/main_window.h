/*!
 * 2D Plot analyser. SignalPlotter.
 *
 * Plots 2D graph. Source data is
 * -raws of .png image may be:
 * -scanlines taken by side-scan echo-sounder.
 *
 */

#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <QWidget>
#include <QObject>
#include <QGraphicsScene>
#include <QMainWindow>
#include <QGraphicsView>
#include <QAction>
#include <QGraphicsItem>
#include <QInputDialog>
#include <stdio.h>
#include <iostream>
#include <QVector>
#include <QDoubleSpinBox>
#include "../custom_plot/qcustomplot.h"
#include "signals_eval.h"

// Constants
static const double freq_warn_prec = 0.03;
static const double freq_error_prec = 0.05;
static const unsigned int freq_factor_to_pass = 2;
static const unsigned int fit_curve_size = 200;

namespace Ui {
class MainWindow;
}


struct GraphParams {
 /**
  * Parameters of graphs in customPlot.
  */
  double xOffset;
  double xScale;
  double yOffset;
  double yScale;
};

class MainWindow : public QMainWindow {
  Q_OBJECT

public:;
  explicit MainWindow(QWidget *parent=0);
  ~MainWindow();

private slots:;
  void changeFreqNominal(double);
  void changeFreqParRes(double);
  void changeRmeas(double);
  void changeNPeaks(int);
  void changeComment(QString);
  void SetFreqNominal();
  void SetFreqParRes();
  void SetRmeas();
  void SetNPeaks();
  void SetComment();
  void change_cy0(double);
  void change_ca0(double);
  void change_cw(double);
  void change_ct0(double);
  void change_cth(double);

  void open_csv_radio_dialog();
  void open_csv_attenuation_dialog();
  void save_report_dialog();
  void titleDoubleClick(QMouseEvent *event);
  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void selectionChanged();
  void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
  void addGraph1(Samples data, GraphParams const& graph_params, QString const& mes); // Radio.
  void addGraph2(Samples data, GraphParams const& graph_params, QString const& mes); // Osc.
  void addGraph3(Samples data, GraphParams const& graph_params, QString const& mes); // Exp.
  void addGraph4(Samples data, GraphParams const& graph_params, QString const& mes); // FitCurve.
  void updateGraph();
  void contextMenuRequest(QPoint pos);
  void showSelectedGraph();
  void hideSelectedGraph();
  void removeSelectedGraph();
  void removeAllGraphs();
  void mousePress();
  void mouseWheel();
  void smooth();
  int  estimate_contour_params();
  void open_fit_curve_toolbar();

private:;
  void create_parameters_setting_dialog();
  void create_fit_curve_toolbar();
  void load_csv_radio();
  void load_csv_attenuation();
  Samples load_csv(QString filepath, GraphParams *graph_params);
  int  signal_analyzer(double *a, double *b, double *q_factor, double *freq);
  void save_report(QString const& filepath);
  bool verify_half_periods(Intervals const& zero_intervals);
  bool verify_half_periods(std::vector<unsigned int> const& zero_points);
  void plot_points(std::vector<QPoint> const& xy_points, GraphParams const& g_params);
  void recalculate_param_curve();
  double y(double x);

private:;
  Ui::MainWindow *ui;
  // Немодальные диалоги задания величин:
  QInputDialog *QIDFreqNominal; // Номинальная частота резонанса антенны.
  QInputDialog *QIDRmeas; // Измерительное сопротивление.
  QInputDialog *QIDFreqParRes; // Частота при параллельном резонансе.
  QInputDialog *QIDNPeaks; // Число анализируемых пиков.
  QInputDialog *QIDComment; // Число анализируемых пиков.
  QDialog *QDParamDialog; // Диалог задания всех параметров.
  QToolBar *QTBCurveFit;
  QDoubleSpinBox *QDSB_cy0;
  QDoubleSpinBox *QDSB_ca0;
  QDoubleSpinBox *QDSB_cw;
  QDoubleSpinBox *QDSB_ct0;
  QDoubleSpinBox *QDSB_cth;
  double Rmeas;
  double FreqParRes;
  double FreqNominalAntenna;
  unsigned int NumOfAnalysedPeaks;
  QString report_comment;
  float decimation_factor;
  unsigned int median_mask_size;
  // The end of radio impulse.
  unsigned int radio_end_index;
  // Paths to opened .csv files.
  QString path_to_radio_csv;
  QString path_to_attenuation_csv;
  QString path_to_report;
  Samples samples_radio;
  Samples samples_radio_smoothed;
  Samples samples_attenuation;
  Samples samples_attenuation_smoothed;
  Samples fitting_curve;
  GraphParams graph_radio;
  GraphParams graph_attenuation;
  GraphParams graph_fitting_curve;
  // Calculated parameters.
  double Q, f_a, Ra, La, Ca, C0, U_max, I_max, F0, t0;
  // Fitting curve parameters.
  double c_y0, c_w, c_t0, c_th, c_a0;
};

#endif
