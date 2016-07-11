#ifndef shared_h
#define shared_h

#include <QVector>
#include <QDebug>
#include <QDateTime>

#include <complex>
#include <QLayout>
#include <QPushButton>
#include <QDir>

#include "display.h"

#include <time.h>

const double DEFAULT_WIDTH = 2.5;
const double DEFAULT_HEIGHT = 2.0;
const double DEFAULT_XCORNER = -0.5;
const double DEFAULT_YCORNER = -0.5;
const int DEFAULT_OUTPUT_WIDTH = 6000; //6000 width 4800 height standard for art prints
const int DEFAULT_OUTPUT_HEIGHT = 4800;
const int DEFAULT_PREVIEW_SIZE = 600;
const double DEFAULT_IMAGE_SIZE = 600;

struct Settings
{
    double Width = DEFAULT_WIDTH;
    double Height = DEFAULT_HEIGHT;
    double XCorner = DEFAULT_XCORNER;
    double YCorner = DEFAULT_YCORNER;
    int OWidth = DEFAULT_OUTPUT_WIDTH;
    int OHeight = DEFAULT_OUTPUT_HEIGHT;

    Settings* clone() {
      
        Settings* newSettings = new Settings;
        newSettings->Width = this->Width;
        newSettings->Height = this->Height;
        newSettings->XCorner = this->XCorner;
        newSettings->YCorner = this->YCorner;
        newSettings->OWidth = this->OWidth;
        newSettings->OHeight = this->OHeight;
        
        return newSettings;
    }
};


class HistoryItem : public QObject
{
    Q_OBJECT
    
public:
    
    HistoryItem(QObject *parent = 0) : QObject(parent) { }
    
    QImage *getImage() { return preview->getImage(); }
    Display *getDisplay() { return preview; }    
    
    QVBoxLayout *layoutWithLabelItem;
    QHBoxLayout *layoutItem;
    QVBoxLayout *buttonLayoutItem;
    Display *preview;
    QPushButton *viewButton;
    QPushButton *removeButton;
    QLabel *labelItem;
    QString filePathName;
    QDateTime savedTime;
    
    
};



#endif /* shared_h */
