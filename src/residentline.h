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
    
signals:
    void removeResidentLine(ResidentLine* line);
    
private slots:
    void onRemoveLine();

private:
    QLabel* mStartTimeLabel;
    QLabel* mEndTimeLabel;
    
};

#endif // RESIDENTLINE_H
