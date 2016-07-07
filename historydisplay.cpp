//
//  historydisplay.cpp
//  
//
//  Created by Bridget E. Went on 6/30/16.
//
//

#include "historydisplay.h"

// CONSTRUCTOR
HistoryDisplay::HistoryDisplay(QObject *parent) : QObject(parent)
{
  
    // create layout elements
    viewHistoryWidget = new QWidget(static_cast<QWidget *>(parent));
    viewHistoryBox = new QGroupBox(tr("Snapshots"), viewHistoryWidget);
    viewHistoryBoxOverallLayout = new QVBoxLayout(viewHistoryWidget);
    
    clearHistoryButton = new QPushButton(tr("Clear All"), viewHistoryBox);
    viewHistoryBoxLayout = new QVBoxLayout(viewHistoryBox);
    
    viewHistoryBoxOverallLayout->addWidget(viewHistoryBox);
    viewHistoryBoxLayout->addWidget(clearHistoryButton);
    viewHistoryBoxOverallLayout->addStretch();
    
    
    // connect signals
    viewMapper = new QSignalMapper(this);
    removeMapper = new QSignalMapper(this);
    
    connect(clearHistoryButton, SIGNAL(clicked()), this, SLOT(clearAllHistory()));
    connect(removeMapper, SIGNAL(mapped(QObject*)), this, SLOT(removePreview(QObject*)));
    
}

// add an instance of the function to the running history
void HistoryDisplay::addToHistory(const QDateTime &savedTime, const QString &filePathName, AbstractFunction *function, ColorWheel *colorwheel, Settings *settings)
{

    HistoryItem *item = new HistoryItem();
    
    QVBoxLayout *historyItemsWithLabelLayout = new QVBoxLayout();
    QHBoxLayout *historyItemsLayout = new QHBoxLayout();
    QVBoxLayout *historyItemsButtonsLayout = new QVBoxLayout();
    Display *d = new Display(HISTORY_ITEM_SIZE, HISTORY_ITEM_SIZE, viewHistoryBox);
    QPushButton *viewButton = new QPushButton(tr("View"), viewHistoryBox);
    QPushButton *removeButton = new QPushButton(tr("Remove"), viewHistoryBox);
    QLabel *timeStampLabel = new QLabel(viewHistoryBox);
    
    QString newFile = savedTime.toString("MM.dd.yyyy.hh.mm.ss.zzz.t").append(".wpr");
    QString savedTimeLabel = "Saved: " + savedTime.toString("MM/dd/yyyy") + " at " + savedTime.toString("hh:mm:ss");
    timeStampLabel->setText(savedTimeLabel);
    
    historyItemsLayout->addWidget(d);
    historyItemsButtonsLayout->addWidget(viewButton);
    historyItemsButtonsLayout->addWidget(removeButton);
    historyItemsLayout->addLayout(historyItemsButtonsLayout);
    historyItemsWithLabelLayout->addLayout(historyItemsLayout);
    historyItemsWithLabelLayout->addWidget(timeStampLabel);
    viewHistoryBoxLayout->insertLayout(1, historyItemsWithLabelLayout);
    
    // saving all values to history item object
    item->preview = d;
    item->savedTime = savedTime;
    item->layoutWithLabelItem = historyItemsWithLabelLayout;
    item->layoutItem = historyItemsLayout;
    item->buttonLayoutItem = historyItemsButtonsLayout;
    item->viewButton = viewButton;
    item->removeButton = removeButton;
    item->labelItem = timeStampLabel;
    item->filePathName = filePathName;
    
    AbstractFunction *currFunction = function;
    ColorWheel *currColorWheel = colorwheel;
    Settings *clonedSettings = settings;
    
    Port *historyDisplayPort = new Port(currFunction, currColorWheel, item->preview->width(), item->preview->height(), clonedSettings);
    historyDisplayPort->paintHistoryIcon(item);
    
    // connect and map signals
    connect(viewButton, SIGNAL(clicked()), viewMapper, SLOT(map()));
    connect(removeButton, SIGNAL(clicked()), removeMapper, SLOT(map()));
    
    viewMapper->setMapping(viewButton, newFile);
    removeMapper->setMapping(removeButton, item);
    
    // map the timestamp to the history item and port
    historyItemsMap.insert(savedTime, item);
    historyPortsMap.insert(savedTime, historyDisplayPort);    

}

// remove all elements of the history item and its UI
void HistoryDisplay::removePreview(QObject *item)
{
    HistoryItem *historyItemToRemove = qobject_cast<HistoryItem*>(item);
    
    historyItemToRemove->buttonLayoutItem->removeWidget(historyItemToRemove->viewButton);
    delete historyItemToRemove->viewButton;
    
    historyItemToRemove->buttonLayoutItem->removeWidget(historyItemToRemove->removeButton);
    delete historyItemToRemove->removeButton;
    
    historyItemToRemove->layoutItem->removeItem(historyItemToRemove->buttonLayoutItem);
    delete historyItemToRemove->buttonLayoutItem;
    
    historyItemToRemove->layoutItem->removeWidget(historyItemToRemove->preview);
    delete historyItemToRemove->preview;
    
    historyItemToRemove->layoutWithLabelItem->removeItem(historyItemToRemove->layoutItem);
    delete historyItemToRemove->layoutItem;
    
    historyItemToRemove->layoutWithLabelItem->removeWidget(historyItemToRemove->labelItem);
    delete historyItemToRemove->labelItem;
    
    viewHistoryBoxLayout->removeItem(historyItemToRemove->layoutWithLabelItem);
    delete historyItemToRemove->layoutWithLabelItem;
    
    delete *(historyPortsMap.find(historyItemToRemove->savedTime));
    historyPortsMap.erase(historyPortsMap.find(historyItemToRemove->savedTime));
    
    historyItemsMap.erase(historyItemsMap.find(historyItemToRemove->savedTime));
    
    QFile::remove(historyItemToRemove->filePathName);
}


// remove all elements from the history
void HistoryDisplay::clearAllHistory()
{
    while (!historyItemsMap.empty()) {
        removePreview(historyItemsMap.begin().value());
    }
}


// called from interface to add to history if we haven't reached the maximum number of history items
void HistoryDisplay::triggerAddToHistory(const QDateTime &savedTime, const QString &filePathName, AbstractFunction *function, ColorWheel *colorwheel, Settings *settings)
{
    if (historyItemsMap.size() < MAX_HISTORY_ITEMS) {
        addToHistory(savedTime, filePathName, function->clone(), colorwheel->clone(), settings->clone());
    } else {
        removePreview(*(historyItemsMap.begin()));
        addToHistory(savedTime, filePathName, function->clone(), colorwheel->clone(), settings->clone());
    }
    
    
}




