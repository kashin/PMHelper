#include "pmhelperapplication.h"
#include "residenttab.h"
#include <QTabWidget>

PMHelperApplication::PMHelperApplication()
{
    QTabWidget* tabWidget = new QTabWidget(this);
    ResidentTab* residentTab = new ResidentTab();
    tabWidget->addTab(residentTab, tr("Resident"));

    setCentralWidget(tabWidget);
}
