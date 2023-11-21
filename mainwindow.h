#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"panier.h"
#include <QMainWindow>

#include<QPropertyAnimation>
#include<QFileDialog>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();
    void on_lineEdit_recherche_textChanged();

    void on_pb_recherche_clicked();

    void on_actionGen_rer_PDF_triggered();
    void on_actionStatistiques_triggered();

    void on_pb_ajouter_2_clicked();
    void on_radioButton_ref_clicked();

    void on_radioButton_cin_clicked();

    void on_radioButton_price_clicked();

    void on_pb_stats_clicked();

    void on_qr_clicked();

    void on_pb_modifier_2_clicked();

private:
    Ui::MainWindow *ui;
    panier p;
};
#endif // MAINWINDOW
