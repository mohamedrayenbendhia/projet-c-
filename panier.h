#ifndef PANIER_H
#define PANIER_H
#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>

class panier
{
public:
    panier();
    panier(int,int,float);
    int getref_panier();
    int getcin_client();
    int getprix_panier();

    void setref_panier(int);
     void setcin_client(int);
      void setprix_panier(float);

      bool ajouter();
      QSqlQueryModel *afficher();
    //  bool modifier(int,int,float);
      bool modifier();
      bool supprimer(int);
       bool RechercheSponsorParID(int IDrecherche);
       QSqlQueryModel *tri_ref();
       QSqlQueryModel *tri_cin();
       QSqlQueryModel *tri_price();
     QSqlQueryModel*  rechercher(QString rech);
       QSqlQueryModel * stat();




private:
    int ref_panier;
    int cin_client;
    float prix_panier;
};

#endif // PANIER_H
