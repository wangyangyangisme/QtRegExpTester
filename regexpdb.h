#ifndef REGEXPDB_H
#define REGEXPDB_H

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>

#include <QAction>
#include <QListView>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>

#include <QDebug>

class RegExpDb
{
public:
    RegExpDb();
    bool insertRow(QString name, QString value);
    bool updateRow(QString originalName, QString name, QString value);
    void deleteRow(QString name);
    QString getValue(QString name);
    QString lastError();

    QSqlTableModel *model;

private:
    QSqlDatabase db;
    QString errorString;

};

#endif // REGEXPDB_H
