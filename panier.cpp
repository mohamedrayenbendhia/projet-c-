#include "panier.h"
#include<QString>
#include <QSqlQuery>
#include<QtDebug>
#include<QObject>
#include <QByteArray>
#include<map>
#include<QSqlRecord>
#include <QFile>
#include <QMessageBox>

#include<QSqlQueryModel>
panier::panier()
{
    ref_panier=0;
    cin_client=0;
    prix_panier=0;

}

panier::panier(int ref_panier,int cin_client,float prix_panier)
{
    this->cin_client=cin_client;
    this->ref_panier=ref_panier;
    this->prix_panier=prix_panier;

}

int panier:: getref_panier()
{return ref_panier;}
int panier:: getcin_client()
{return cin_client;}
int panier:: getprix_panier()
{return prix_panier;}


void panier:: setref_panier(int ref_panier)
{
    this->ref_panier=ref_panier;
}
 void panier:: setcin_client(int cin_client)
{
 this->cin_client=cin_client;

 }
void panier:: setprix_panier(float prix_panier)
{
    this->prix_panier=prix_panier;
}

bool panier::ajouter()
{
    QSqlQuery query;
    QString ref_panier_string = QString::number(ref_panier);
    QString cin_client_string = QString::number(cin_client);
    QString prix_panier_string = QString::number(prix_panier);

    // Vérifier si la référence du panier existe déjà
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT ref_panier FROM PANIERS WHERE ref_panier = :ref_panier");
    checkQuery.bindValue(":ref_panier", ref_panier_string);

    if (checkQuery.exec() && checkQuery.next()) {
        // La référence du panier existe déjà, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Erreur d'ajout"),
                              QObject::tr("La référence du panier existe déjà.\n"
                                          "Impossible d'ajouter le panier."), QMessageBox::Ok);
        return false;
    } else {
        // La référence du panier n'existe pas, procéder à l'ajout
        query.prepare("INSERT INTO PANIERS(ref_panier, cin_client, prix_panier) VALUES (:ref_panier, :cin_client, :prix_panier)");

        query.bindValue(":ref_panier", ref_panier_string);
        query.bindValue(":cin_client", cin_client_string);
        query.bindValue(":prix_panier", prix_panier_string);

        return query.exec();
    }
}

/*
bool panier::RechercheSponsorParID(int IDrecherche)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM PANIERS WHERE ref_panier=:IDrecherche");
    query.bindValue(":IDrecherche",IDrecherche);
    query.exec();
    if (!query.first()){
        return false;
    }
    else
    {
        int nref = query.record().indexOf("ref_panier");
        int ncin=query.record().indexOf("cin_client");
        int nprix=query.record().indexOf("prix_panier");


        ref_panier=query.value(nref).toInt();
        cin_client=query.value(ncin).toInt();
        prix_panier=query.value(nprix).toFloat();


        return true;
    }

}
*/

QSqlQueryModel * panier::afficher()

{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from PANIERS");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("reference panier"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("cin client "));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix panier"));

    return model;
}


bool panier::modifier(){
   QSqlQuery query;
   QString ref_panier_string= QString::number(ref_panier);
    query.prepare("UPDATE PANIERS SET ref_panier= :ref_panier, cin_client= :cin_client, prix_panier= :prix_panier WHERE ref_panier= :ref_panier");
    query.bindValue(":ref_panier",ref_panier_string);
    query.bindValue(":cin_client",cin_client);
    query.bindValue(":prix_panier",prix_panier);

    return query.exec();
}


bool panier::supprimer(int ref_panier)
{
QSqlQuery query;

query.prepare("Delete from PANIERS where ref_panier=:ref_panier ");
query.bindValue(":ref_panier", ref_panier);
return query.exec();
}



QSqlQueryModel * panier::rechercher(QString rech)

  {

        QSqlQuery query;

       QSqlQueryModel*model1=new QSqlQueryModel();





        query.prepare("SELECT * FROM PANIERS WHERE  ref_panier LIKE'%"+rech+"%'");



        query.exec();

        model1->setQuery(query);

        return model1;



  }
QSqlQueryModel * panier::tri_ref()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from PANIERS order by ref_panier  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}

QSqlQueryModel * panier::tri_cin()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from PANIERS order by cin_client  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}
QSqlQueryModel * panier::tri_price()
{
    QSqlQueryModel *model= new QSqlQueryModel;
    QSqlQuery *q=new QSqlQuery();
    q->prepare("select * from PANIERS order by prix_panier  asc");
    q->exec();
    model->setQuery(*q);
    return  model;
}


