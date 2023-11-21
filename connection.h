#ifndef CONNECTION_H
#define CONNECTION_H
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>

class connection
{
public:
    connection();
    bool createconnect();
};

#endif // CONNECTION_H
