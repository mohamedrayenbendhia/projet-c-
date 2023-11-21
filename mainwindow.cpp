#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"panier.h"
#include<QMessageBox>
#include <iostream>
#include <string>
#include<QPropertyAnimation>
#include <QTextStream>
#include <QFile>
#include <QDataStream>
#include<QTextDocument>
#include<QtPrintSupport/QPrinter>
#include<QByteArray>
#include <QSqlQuery>
#include <QTime>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts>
#include <QIntValidator>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QMainWindow>
#include <QMessageBox>
#include<QApplication>
#include <QPrinter>
#include <QTextStream>
#include <QTextDocument>
#include <QTextEdit>
#include <QTextStream>
#include<QString>
#include <QSqlQueryModel>
#include <QIntValidator>
#include <QPainter>
#include <QPdfWriter>
#include <QComboBox>
#include"qrcode.h"
#include<fstream>
#include<QFileDialog>
#include<QPrinter>
#include"qrcode.h"
using qrcodegen::QrCode;
using qrcodegen::QrSegment;
//#include <QtCharts>
#include <QIntValidator>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
     ui->tab_panier->setModel(p.afficher());



}

MainWindow::~MainWindow()
{
    delete ui;


}





void MainWindow::on_pb_ajouter_clicked()
{

    int ref_panier=ui->le_ref->text().toInt();
    int cin_client=ui->le_cin->text().toInt();
    float prix_panier=ui->le_prix->text().toFloat();
     std::string str_cin = std::to_string(cin_client);
     std::string str_ref = std::to_string(ref_panier);

     int x=0;

      if ((str_ref.length()!=8) && (str_cin.length()!=8 ))
     {
         QMessageBox::critical(nullptr, QObject::tr("WARNING"),
                     QObject::tr("Le ref doit être composé de 8 chiffres"), QMessageBox::Ok);
               x++;
     }

      else if (x==0)
      {
          panier p(ref_panier,cin_client,prix_panier);
          bool test=p.ajouter();
          if(test)
          {
              QMessageBox::critical(nullptr, QObject::tr("ajout"),
                                             QObject::tr("ajout avec succes  .\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);

              ui->tab_panier->setModel(p.afficher());

          }
          else
          {
              QMessageBox::critical(nullptr, QObject::tr("ahout"),
                                             QObject::tr("Ajout impossible.\n"
                                                      "Click Cancel to exit."), QMessageBox::Cancel);

          }

      }

}




void MainWindow::on_pb_supprimer_clicked()
{
    panier p;
    p.setref_panier(ui->le_supp_ref->text().toInt());

    bool test=p.supprimer(p.getref_panier());

    if(test)
    {
        QMessageBox::critical(nullptr, QObject::tr("id"),
                                       QObject::tr("suppression avec succes  .\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_panier->setModel(p.afficher());
    }
    else
    {


        QMessageBox::critical(nullptr, QObject::tr("id"),
                                       QObject::tr("suppression impossible  .\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);


    }






}

void MainWindow::on_pb_recherche_clicked()
{
   /* panier Sp;
    Sp.setref_panier(ui->lineEdit_recherche->text().toInt());
    bool test=Sp.RechercheSponsorParID(Sp.getref_panier());
    QMessageBox msgbox;

    if (test)
       {
        msgbox.setText("ref existe");
        ui->tab_panier->setModel(Sp.afficher());
        }
    else
        msgbox.setText("ref n'existe pas");
        msgbox.exec();
        ui->lineEdit_recherche->clear();
        */

    panier E;
                              QString rech =ui->lineEdit_recherche->text();
                              ui->tab_panier->setModel(E.rechercher(rech));
}

void MainWindow::on_radioButton_ref_clicked()
{
    panier *Sp = new panier();
     ui->tab_panier->setModel(Sp->tri_ref());
}

void MainWindow::on_radioButton_cin_clicked()
{
    panier *Sp = new panier();
     ui->tab_panier->setModel(Sp->tri_cin());
}

void MainWindow::on_radioButton_price_clicked()
{
    panier *Sp = new panier();
     ui->tab_panier->setModel(Sp->tri_price());
}
void MainWindow::on_pb_modifier_2_clicked()
{

    int ref_panier=ui->le_ref->text().toInt();
    int cin_client=ui->le_cin->text().toInt();
    int prix_panier=ui->le_prix->text().toInt();

    panier p(ref_panier,cin_client,prix_panier);

     //  panier p(ref_panier,cin_client,prix_panier);
       bool toTest =p.modifier();
       if(toTest)
       {
           QMessageBox::information(nullptr, QObject::tr("Editing panier"),
                             QObject::tr("panier modifier avec succes"), QMessageBox::Ok);
            ui->tab_panier->setModel(p.afficher());
       }
       ui->le_ref->clear();
       ui->le_cin->clear();
       ui->le_prix->clear();


       }



void MainWindow::on_qr_clicked()
{
    if(ui->tab_panier->currentIndex().row()==-1)
                   QMessageBox::information(nullptr, QObject::tr("QR code"),
                                            QObject::tr("Veuillez Choisir un CODE du Tableau.\n"
                                                        "Click Ok to exit."), QMessageBox::Ok);
               else
               {

                    int ref=ui->tab_panier->model()->data(ui->tab_panier->model()->index(ui->tab_panier->currentIndex().row(),0)).toInt();
                    const QrCode qr = QrCode::encodeText(std::to_string(ref).c_str(), QrCode::Ecc::LOW);
                    std::ofstream myfile;
                    myfile.open ("qrcode.svg") ;
                    myfile << qr.toSvgString(1);
                    myfile.close();
                    //QSvgRenderer svgRenderer(QString("qrcode.svg"));
                    QPixmap pix( QSize(90, 90) );
                    QPainter pixPainter( &pix );
                   // svgRenderer.render( &pixPainter );
                    ui->QRCODE_3->setPixmap(pix);
               }
}


void MainWindow::on_pb_ajouter_2_clicked()
{
    QString strStream;
                    QTextStream out(&strStream);
                    const int rowCount = ui->tab_panier->model()->rowCount();
                    const int columnCount =ui->tab_panier->model()->columnCount();


                    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("paniers")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<h1>Liste des Paniers </h1>"

                                "<table border=1 cellspacing=0 cellpadding=2>\n";


                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->tab_panier->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->tab_panier->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->tab_panier->isColumnHidden(column)) {
                                       QString data = ui->tab_panier->model()->data(ui->tab_panier->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";



            QTextDocument *document = new QTextDocument();
            document->setHtml(strStream);


            //QTextDocument document;
            //document.setHtml(html);
            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName("Paniers.pdf");
            document->print(&printer);

            QMessageBox::information(this, QObject::tr("PDF Enregistré!"),
            QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pb_stats_clicked()
{
    QSqlQueryModel * model= new QSqlQueryModel();
                            model->setQuery("select * from PANIERS where prix_panier < 1000 ");
                            float tarif1=model->rowCount();
                            model->setQuery("select * from PANIERS where prix_panier  between 1000 and 1500 ");
                            float tarif2=model->rowCount();
                            model->setQuery("select * from PANIERS where prix_panier >1500 ");
                            float tarif3=model->rowCount();
                            float total=tarif1+tarif2+tarif3;
                            QString a=QString("moins de 1000 Millions "+QString::number((tarif1*100)/total,'f',2)+"%" );
                            QString b=QString("entre 1000 et 1500 Millions "+QString::number((tarif2*100)/total,'f',2)+"%" );
                            QString c=QString("+1000 Millions "+QString::number((tarif3*100)/total,'f',2)+"%" );
                            QPieSeries *series = new QPieSeries();
                            series->append(a,tarif1);
                            series->append(b,tarif2);
                            series->append(c,tarif3);
                    if (tarif1!=0)
                    {QPieSlice *slice = series->slices().at(0);
                     slice->setLabelVisible();
                     slice->setPen(QPen());}
                    if ( tarif2!=0)
                    {
                             // Add label, explode and define brush for 2nd slice
                             QPieSlice *slice1 = series->slices().at(1);
                             //slice1->setExploded();
                             slice1->setLabelVisible();
                    }
                    if(tarif3!=0)
                    {
                             // Add labels to rest of slices
                             QPieSlice *slice2 = series->slices().at(2);
                             //slice1->setExploded();
                             slice2->setLabelVisible();
                    }
                            // Create the chart widget
                            QChart *chart = new QChart();
                            // Add data to chart with title and hide legend
                            chart->addSeries(series);
                            chart->setTitle("Pourcentage Par Millions :Nombre Des panierss "+ QString::number(total));
                            chart->legend()->hide();
                            // Used to display the chart
                            QChartView *chartView = new QChartView(chart);
                            chartView->setRenderHint(QPainter::Antialiasing);
                            chartView->resize(1000,500);
                            chartView->show();
}



