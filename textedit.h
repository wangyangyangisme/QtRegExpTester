#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QTextEdit>
#include <QTextCharFormat>
#include <QKeyEvent>
#include <QStringList>

#include <QDebug>

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit TextEdit(QWidget *parent = 0);
    void setColors(QStringList colorList);
    void exactMatch(QRegExp *regExp, QString *result);

signals:

public slots:

private:
    QTextCharFormat defaultFormat;
    QStringList colors;


protected:
    virtual void keyPressEvent(QKeyEvent *e);

};

#endif // TEXTEDIT_H
