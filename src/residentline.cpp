#include "residentline.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>

ResidentLine::ResidentLine(const QString startTime, const QString endTime, QWidget *parent)
    : QWidget(parent),
      mStartTimeLabel(0),
      mEndTimeLabel(0)
{
    QBoxLayout* mainLayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    mainLayout->setAlignment(Qt::AlignTop);

    QDateTime dateTime = QDateTime::fromString(startTime, "d/M/yy");
    if (!dateTime.isValid()) {
        emit wrongStartDateFormat();
    }
    mStartTimeLabel = new QLabel(startTime, this);
    mainLayout->addWidget(mStartTimeLabel);

    dateTime = QDateTime::fromString(endTime, "d/M/yy");
    if (!dateTime.isValid()) {
        emit wrongEndDateFormat();
    }
    mEndTimeLabel = new QLabel(endTime, this);
    mainLayout->addWidget(mEndTimeLabel);

    QPushButton* deleteButton = new QPushButton(tr("remove entry"), this);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(onRemoveLine()));
    mainLayout->addWidget(deleteButton);

    setLayout(mainLayout);
}

qint64 ResidentLine::getDays()
{
    bool invalidDate = false;
    QDateTime startDateTime = QDateTime::fromString(mStartTimeLabel->text(), "d/M/yy");
    if (!startDateTime.isValid())
    {
        emit wrongStartDateFormat();
    }
    QDateTime endDateTime = QDateTime::fromString(mEndTimeLabel->text(), "d/M/yy");
    if (!endDateTime.isValid())
    {
        emit wrongEndDateFormat();
    }

    qint64 result = 0;
    if (!invalidDate)
    {
        result = qAbs(startDateTime.daysTo(endDateTime)) - 1;
    }
    return result < 0 ? 0 : result;
}

void ResidentLine::setStartTime(QString startTime)
{
    mStartTimeLabel->setText(startTime);
}

void ResidentLine::setEndTime(QString endTime)
{
    mEndTimeLabel->setText(endTime);
}

void ResidentLine::onRemoveLine()
{
    emit removeResidentLine(this);
}
