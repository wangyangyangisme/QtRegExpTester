#include "regexpedit.h"

RegExpEdit::RegExpEdit(QWidget *parent) :
    QTextEdit(parent)
{
    regExp.setPattern("(\\([^)]*[)])");
    defaultFormat.setForeground(QBrush::QBrush(Qt::black));

    setAcceptRichText(false);
}

void RegExpEdit::setColors(QStringList colorList)
{
    colors = colorList;
}

void RegExpEdit::highlight()
{
    blockSignals(true);
    QString text = toPlainText();
    QTextCursor tempCursor1 = textCursor();
    selectAll();
    setTextColor(QColor("black")); // reset formating
    moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
    int pos = 0, i = 0, f;

    while ((pos = regExp.indexIn(text, pos)) != -1 && i < colors.length()) {

        f= find(regExp.cap(1));
        pos += regExp.matchedLength();
        setTextColor(QColor(colors.at(i)));
        i++;
    }
    setTextCursor(tempCursor1);
    blockSignals(false);
//    qDebug() << toPlainText();
}

void RegExpEdit::keyPressEvent(QKeyEvent *e)
{
    switch (e->key())
    {
    case Qt::Key_Return:
        highlight();
        emit returnPressed();
        return;
    case Qt::Key_Tab:
        return;
    }
    if(e->key() > Qt::Key_QuoteDbl &&  e->key() < Qt::Key_AsciiTilde)
        setCurrentCharFormat(defaultFormat);

    QTextEdit::keyPressEvent(e);
}
