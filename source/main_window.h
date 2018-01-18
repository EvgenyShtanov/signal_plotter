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
#include "../custom_plot/qcustomplot.h"
#include "signals_eval.h"

// Constants
static const double freq_warn_prec = 0.03;
static const double freq_error_prec = 0.05;
static const unsigned int freq_factor_to_pass = 2;

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
  void open_csv_radio_dialog();
  void open_csv_attenuation_dialog();
  void save_report_dialog();
  void titleDoubleClick(QMouseEvent *event);
  void axisLabelDoubleClick(QCPAxis* axis, QCPAxis::SelectablePart part);
  void legendDoubleClick(QCPLegend* legend, QCPAbstractLegendItem* item);
  void selectionChanged();
  void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
  void addGraph1(Samples data, GraphParams const& graph_params);
  void addGraph2(Samples data, GraphParams const& graph_params);
  void updateGraph();
  void contextMenuRequest(QPoint pos);
  void showSelectedGraph();
  void hideSelectedGraph();
  void removeSelectedGraph();
  void removeAllGraphs();
  void mousePress();
  void mouseWheel();
  void smooth();
  void approximate();
  void estimate_contour_params();

private:;
  void load_csv_radio();
  void load_csv_attenuation();
  Samples load_csv(QString filepath, GraphParams *graph_params);
  void signal_analyzer(double *a, double *b, double *q_factor, double *freq);
  void save_report(QString filepath);
  void verify_half_periods(Intervals const& zero_intervals);
  void verify_half_periods(std::vector<unsigned int> const& zero_points);

  // Debug function
  void plot_points(std::vector<QPoint> const& xy_points, GraphParams const& g_params);

private:;
  Ui::MainWindow *ui;
  // Немодальные диалоги задания величин:
  QInputDialog *QIDFreqNominal; // Номинальная частота резонанса антенны.
  QInputDialog *QIDRmeas; // Измерительное сопротивление.
  QInputDialog *QIDFreqParRes; // Частота при параллельном резонансе.
  QInputDialog *QIDNPeaks; // Число анализируемых пиков.
  double Rmeas;
  double ParResFreq;
  double FreqNominalAntenna;
  unsigned int NumOfAnalysedPeaks;
  float decimation_factor;
  unsigned int median_mask_size;
  // The end of radio impulse.
  unsigned int radio_end_index;
  // Paths to opened .csv files.
  QString path_to_radio_csv;
  QString path_to_attenuation_csv;
  QString path_to_report;
  Samples samples_radio;
  bool samples_radio_show;
  Samples samples_radio_smoothed;
  bool samples_radio_smoothed_show;
  Samples samples_attenuation;
  bool samples_attenuation_show;
  Samples samples_attenuation_smoothed;
  bool samples_attenuation_smoothed_show;
  GraphParams graph_radio;
  GraphParams graph_attenuation;
};

#endif
