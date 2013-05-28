#include "onelineedit.h"

#include <QKeyEvent>

#define MAGIC_TEXTEDIT_HEIGHT_SIZE 12

OneLineEdit::OneLineEdit(QWidget *parent)
    : QTextEdit(parent),
      mEnterKeyResponse(Default)
{
    setWordWrapMode(QTextOption::NoWrap);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setMaximumHeight(fontMetrics().height() + MAGIC_TEXTEDIT_HEIGHT_SIZE);
    setTabChangesFocus(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void OneLineEdit::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter))
    {
        switch (mEnterKeyResponse)
        {
            case None:
                return;
            case EmitEnterPressed:
                emit enterPressed();
                return;
            case EmitJumpToNext:
                emit jumpToNext();
                return;
            default:
                break;
        }
    }
    QTextEdit::keyPressEvent(event);
}

void OneLineEdit::setEnterKeyResponseType(EnterKeyResponseType type)
{
    mEnterKeyResponse = type;
}
