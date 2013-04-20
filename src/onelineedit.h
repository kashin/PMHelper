#ifndef ONELINEEDIT_H
#define ONELINEEDIT_H

#include <QTextEdit>

class QKeyEvent;

class OneLineEdit : public QTextEdit
{
    Q_OBJECT
public:
    OneLineEdit(QWidget* parent = 0);

    void keyPressEvent(QKeyEvent* event);

    /*!
     * if @param ignore is set to true, then enter key events will be ignored
     * and enterPressed signal emitted instead of adding new line
     */
    void setIgnoreEnterKey(bool ignore);

signals:
    void enterPressed();

private:
    bool mIgnoreEnter;
};

#endif // ONELINEEDIT_H
