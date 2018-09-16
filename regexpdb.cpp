#include "regexpdb.h"

RegExpDb::RegExpDb()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("regexp.db");

    if (db.open()) {
        model = new QSqlTableModel(0, db);

        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS r_regexp (name text PRIMARY KEY ASC, value text);");
        //query.exec("CREATE TABLE r_regexp (desc text, value text);");

        model->setTable("r_regexp");
        model->setSort(0, Qt::AscendingOrder);
        model->select();
    }
}

bool RegExpDb::insertRow(QString desc, QString value)
{
    QString query_str = "INSERT INTO r_regexp(name, value) "
                "VALUES ('%1', '%2');";

    QSqlQuery query((query_str.arg(desc).arg(value)));
    model->select();
//    qDebug() << query.lastError().text();
//    qDebug() << query.lastError().databaseText();
//    qDebug() << query.lastError().driverText();

    errorString = query.lastError().text();

    return !query.lastError().isValid();
}

bool RegExpDb::updateRow(QString originalName, QString name, QString value)
{
    QString query_str = "UPDATE r_regexp SET name='%1' , value='%2' WHERE name='%3';";

    QSqlQuery query((query_str.arg(name).arg(value).arg(originalName)));
    model->select();

    errorString = query.lastError().text();

    return !query.lastError().isValid();
}

void RegExpDb::deleteRow(QString name)
{
    QString query_str = "DELETE FROM r_regexp WHERE name='%1';";

    QSqlQuery query(query_str.arg(name));
    errorString = query.lastError().text();
//    qDebug() << query_str.arg(desc);
//    qDebug() << query.lastError().driverText();
}

QString RegExpDb::getValue(QString name)
{
     QString query_str = "SELECT value FROM r_regexp WHERE name='%1';";
     QSqlQuery query(query_str.arg(name));
     errorString = query.lastError().text();

//     qDebug() << query_str.arg(name);
//     qDebug() << query.lastError().driverText();
     query.first();
     return query.value(0).toString();
}

QString RegExpDb::lastError()
{
    return errorString;
}
