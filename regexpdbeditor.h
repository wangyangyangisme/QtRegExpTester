#ifndef REGEXPDBEDITOR_H
#define REGEXPDBEDITOR_H

#include <QWidget>
#include <QDialog>

#include <QAction>
#include <QContextMenuEvent>
#include <QDialogButtonBox>
#include <QEvent>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QMenu>
#include <QMessageBox>
#include <QSplitter>
#include <QTextEdit>
#include <QToolBar>
#include <QVBoxLayout>
#include <QDebug>

#include "regexpdb.h"

class RegExpDbEditor : public QWidget
{
    Q_OBJECT
public:
    explicit RegExpDbEditor(QWidget *parent = 0);

signals:
    void insertRegExp(QString str);

public slots:

private slots:
    void addRegExp();
    void addEditRegExpCheck();
    void delRegExp();
    void editRegExp();
    void insertRegExp();
    void currentItemChanged(QModelIndex index);
    void findItem(QString pattern);

private:
    QListView *regExpListView;
    QTextEdit *regExpEdit;
    QLineEdit *searchLineEdit;
    QAction *addAction;
    QAction *delAction;
    QAction *editAction;
    QAction *insertAction;
    RegExpDb *db;

    bool eventFilter(QObject *watched, QEvent *e);

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);

};


/* Add,Edit dialog class */

class AddEditDialog : public QDialog
{
    Q_OBJECT
public:
    AddEditDialog(bool isEditFlag = 0, QWidget *parent = 0)
        : QDialog(parent)
    {
        isEdit = isEditFlag;
        if(isEdit)
            setWindowTitle("Edit RegExp");
        else
            setWindowTitle("New RegExp");

        name = new QLineEdit(this);
        data = new QTextEdit(this);
        QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

        QHBoxLayout *hLayout = new QHBoxLayout();
        QLabel *label = new QLabel("Name:", this);
        hLayout->addWidget(label);
        hLayout->addWidget(name);
        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addLayout(hLayout);
        layout->addWidget(data);
        layout->addWidget(buttonBox);


        connect(buttonBox, SIGNAL(accepted()), this, SLOT(myAccept()));
        connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    }

    QString getName() {return name->text();}
    QString getPrevName() {return prevName;}
    QString getValue() {return data->toPlainText();}
    void setName(QString str)
    {
        prevName = str;
        name->setText(str);
    }
    void setValue(QString str) {data->setText(str);}

    bool isEdit;

signals:
    void okPressed();

private slots:
    void myAccept()
    {
        emit okPressed();
    }

private:
    QLineEdit *name;
    QTextEdit *data;
    QString prevName;
};


#endif // REGEXPDBEDITOR_H
