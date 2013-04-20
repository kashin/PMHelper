#include "onelineedit.h"

#include <QKeyEvent>

#define MAGIC_TEXTEDIT_HEIGHT_SIZE 12

void OneLineEdit::keyPressEvent(QKeyEvent *event)
{
    if ( mIgnoreEnter &&
         (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) )
    {
            emit enterPressed();
    }
    else
    {
        QTextEdit::keyPressEvent(event);
    }
}

void OneLineEdit::setIgnoreEnterKey(bool ignore)
{
    mIgnoreEnter = ignore;
}


OneLineEdit::OneLineEdit(QWidget *parent)
    : QTextEdit(parent),
      mIgnoreEnter(false)
{
    setWordWrapMode(QTextOption::NoWrap);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setMaximumHeight(fontMetrics().height() + MAGIC_TEXTEDIT_HEIGHT_SIZE);
    setTabChangesFocus(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
