#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QColor>
#include <QComboBox>
#include <QDesktopWidget>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QListView>
#include <QPushButton>
#include <QRegExp>
#include <QSpacerItem>
#include <QSplitter>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

#include "regexpdbeditor.h"
#include "regexpedit.h"
#include "textedit.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void match();
    void setPatternSyntax(int pattern);
    void setMinimal(int minimal);

private:
    RegExpDb *db;
    RegExpEdit *regExpInput;
    TextEdit *dataInput;
    QLabel *exactMatchStatus;
    QLabel *matchCount;

    QColor captureColor[16];
    QTextCharFormat defaultFormat;

    QRegExp *regExp;
};



#endif // MAINWINDOW_H
