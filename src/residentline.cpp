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

    mStartTimeLabel = new QLabel(startTime, this);
    mainLayout->addWidget(mStartTimeLabel);

    mEndTimeLabel = new QLabel(endTime, this);
    mainLayout->addWidget(mEndTimeLabel);

    QPushButton* deleteButton = new QPushButton(tr("remove entry"), this);
    connect(deleteButton, SIGNAL(clicked()), this, SLOT(onRemoveLine()));
    mainLayout->addWidget(deleteButton);

    setLayout(mainLayout);
}

qint64 ResidentLine::getDays()
{
    QDateTime startDateTime = QDateTime::fromString(mStartTimeLabel->text(), "d/M/yy");
    QDateTime endDateTime = QDateTime::fromString(mEndTimeLabel->text(), "d/M/yy");
    qint64 result = qAbs(startDateTime.daysTo(endDateTime)) - 1;
    return result < 0 ? 0 : result;
}


void ResidentLine::onRemoveLine()
{
    emit removeResidentLine(this);
}
