#ifndef RESIDENTLINE_H
#define RESIDENTLINE_H

#include <QWidget>

class QLabel;

class ResidentLine : public QWidget
{
    Q_OBJECT
public:
    explicit ResidentLine(const QString startTime, const QString endTime, QWidget *parent = 0);


    qint64 getDays();

    void setStartTime(QString startTime);
    void setEndTime(QString endTime);

signals:
    void removeResidentLine(ResidentLine* line);
    void wrongStartDateFormat();
    void wrongEndDateFormat();

private slots:
    void onRemoveLine();

private:
    QLabel* mStartTimeLabel;
    QLabel* mEndTimeLabel;

};

#endif // RESIDENTLINE_H
