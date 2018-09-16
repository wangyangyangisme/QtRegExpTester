#ifndef REGEXPEDIT_H
#define REGEXPEDIT_H

#include <QTextEdit>

#include <QAction>
#include <QKeyEvent>
#include <QMenu>
#include <QStringList>
#include <QTextCharFormat>

#include <QDebug>

class RegExpEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit RegExpEdit(QWidget *parent = 0);
    void setColors(QStringList colorList);
    void highlight();

signals:
    void returnPressed();

public slots:

private:
    QTextCharFormat defaultFormat;
    QStringList colors;
    QRegExp regExp;

protected:
    virtual void keyPressEvent(QKeyEvent *e);
//    virtual void contextMenuEvent(QContextMenuEvent *event);

};

#endif // REGEXPEDIT_H
