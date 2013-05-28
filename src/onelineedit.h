#ifndef ONELINEEDIT_H
#define ONELINEEDIT_H

#include <QTextEdit>

class QKeyEvent;

class OneLineEdit : public QTextEdit
{
    Q_OBJECT
public:
    enum EnterKeyResponseType {
        Default = 0,
        EmitEnterPressed,
        EmitJumpToNext,
        None = 255
    };

    OneLineEdit(QWidget* parent = 0);

    void keyPressEvent(QKeyEvent* event);

    /**
     * @brief setEnterKeyResponseType sets an 'enter' key response type
     *
     * @param mask EnterKeyResponseType that specifies required behavior.
     */
    void setEnterKeyResponseType(EnterKeyResponseType type);

signals:
    void enterPressed();
    void jumpToNext();

private:
    EnterKeyResponseType mEnterKeyResponse;
};

#endif // ONELINEEDIT_H
