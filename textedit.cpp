#include "textedit.h"

TextEdit::TextEdit(QWidget *parent) :
    QTextEdit(parent)
{
    defaultFormat.setForeground(QBrush::QBrush(Qt::black));

    setAcceptRichText(false);
}

void TextEdit::setColors(QStringList colorList)
{
    colors = colorList;
}

void TextEdit::exactMatch(QRegExp *regExp, QString *result)
{
    if(regExp->exactMatch(toPlainText()))
        *result = "true";
    else
        *result = "false";

    int captureCount =  regExp->captureCount();

    blockSignals(true);
    QTextCursor tempCursor = textCursor();
    selectAll();
    setTextColor(QColor("black")); // reset formating
    moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    QString cap;
    for(int i=0; i < captureCount && i < colors.length(); i++)
    {
        cap = regExp->cap(i+1);
        if(find(cap))
        {
            setTextColor(QColor(colors.at(i)));
        }
    }

    blockSignals(false);
    setTextCursor(tempCursor);
}

void TextEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() > Qt::Key_QuoteDbl &&  e->key() < Qt::Key_AsciiTilde)
        setCurrentCharFormat(defaultFormat);

    QTextEdit::keyPressEvent(e);
}
