#include "residenttab.h"
#include "residentline.h"
#include "onelineedit.h"

#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QDateTime>
#include <QDebug>
#include <QTimer>

ResidentTab::ResidentTab(QWidget *parent)
    : QWidget(parent),
      mStartTimeEdit(0),
      mEndTimeEdit(0),
      mLinesLayout(0),
      mStatusLabel(0),
      mHadErrorDuringCalculations(false)
{
    QBoxLayout* mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);

    //HowTo label
    QLabel* howToLabel = new QLabel(tr("Date's format: d/m/yy"), this);
    mainLayout->addWidget(howToLabel);

    // Add lines layout
    QBoxLayout* addLinelayout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    addLinelayout->setAlignment(Qt::AlignTop);
    QWidget* lineWidget = new QWidget(this);
    lineWidget->setLayout(addLinelayout);
    mainLayout->addWidget(lineWidget);

    QLabel* addLineLabel = new QLabel(tr("add new entry"), this);
    addLinelayout->addWidget(addLineLabel, 0, Qt::AlignLeft | Qt::AlignVCenter);
    mStartTimeEdit = new OneLineEdit(this);
    mStartTimeEdit->setEnterKeyResponseType(OneLineEdit::EmitJumpToNext);
    connect(mStartTimeEdit, SIGNAL(jumpToNext()), this, SLOT(onJumpToNextTimeEdit()));
    addLinelayout->addWidget(mStartTimeEdit);

    mEndTimeEdit = new OneLineEdit(this);
    mEndTimeEdit->setEnterKeyResponseType(OneLineEdit::EmitEnterPressed);
    connect(mEndTimeEdit, SIGNAL(enterPressed()), this, SLOT(onAddNewEntry()));
    addLinelayout->addWidget(mEndTimeEdit);

    QPushButton* addEntryButton = new QPushButton(tr("add"), this);
    connect(addEntryButton, SIGNAL(clicked()), this, SLOT(onAddNewEntry()));
    addLinelayout->addWidget(addEntryButton);

    // Lines layout
    mLinesLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
    QWidget* linesWidget = new QWidget(this);
    linesWidget->setLayout(mLinesLayout);
    mainLayout->addWidget(linesWidget);

    // Status label that contains result
    mStatusLabel = new QLabel(tr("no entries"), this);
    mainLayout->addWidget(mStatusLabel);

    setLayout(mainLayout);
    QTimer::singleShot(0, mStartTimeEdit, SLOT(setFocus()));
}

void ResidentTab::onAddNewEntry()
{
    ResidentLine* newLine = new ResidentLine(mStartTimeEdit->toPlainText(), mEndTimeEdit->toPlainText(), this);
    connect(newLine, SIGNAL(removeResidentLine(ResidentLine*)), this, SLOT(onRemoveResidentLine(ResidentLine*)));
    connect(newLine, SIGNAL(wrongStartDateFormat()), this, SLOT(onWrongDateFormat()));
    mLinesLayout->addWidget(newLine);
    recalculateResult();
    mStartTimeEdit->clear();
    mEndTimeEdit->clear();
}

void ResidentTab::onJumpToNextTimeEdit()
{
    mEndTimeEdit->setFocus(Qt::OtherFocusReason);
}

void ResidentTab::onRemoveResidentLine(ResidentLine *line)
{
    mLinesLayout->removeWidget(line);
    line->deleteLater();
    recalculateResult();
}

void ResidentTab::onWrongDateFormat()
{
    mHadErrorDuringCalculations = true;
    mStatusLabel->setText(tr("Added a line with a wrong date format"));
}

void ResidentTab::recalculateResult()
{
    const int linesCount = mLinesLayout->count();
    if (linesCount == 0)
    {
        mStatusLabel->setText(tr("no entries"));
        return;
    }

    qint64 result = 0;
    for(int i = 0; i < linesCount; i++)
    {
        ResidentLine* line = dynamic_cast<ResidentLine*>(mLinesLayout->itemAt(i)->widget());
        if (line) {
            result += line->getDays();
        }
    }
    if (!mHadErrorDuringCalculations) {
        mStatusLabel->setText(tr("Days outside: ") + QString::number(result));
    } else {
        mHadErrorDuringCalculations = false;
    }
}
