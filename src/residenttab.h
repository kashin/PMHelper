#ifndef RESIDENTTAB_H
#define RESIDENTTAB_H

#include <QWidget>

class OneLineEdit;
class QBoxLayout;
class QLabel;
class ResidentLine;
class OneLineEdit;

class ResidentTab : public QWidget
{
    Q_OBJECT
public:
    explicit ResidentTab(QWidget *parent = 0);

signals:

public slots:
    void onAddNewEntry();
    void onJumpToNextTimeEdit();
    void onRemoveResidentLine(ResidentLine* line);
    void onWrongDateFormat();

private:
    void recalculateResult();

private:
    OneLineEdit* mStartTimeEdit;
    OneLineEdit* mEndTimeEdit;
    QBoxLayout* mLinesLayout;
    QLabel* mStatusLabel;
    bool mHadErrorDuringCalculations;
};

#endif // RESIDENTTAB_H
