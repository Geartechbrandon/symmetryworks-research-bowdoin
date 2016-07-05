#ifndef IOTHREAD_H
#define IOTHREAD_H

// thread used for writing an image to a file

#include "shared.h"
#include <QThread>
#include <QWaitCondition>

class IOThread : public QThread
{
    Q_OBJECT
    
public:
    IOThread(QObject *parent = 0);
    ~IOThread();
    
    void render(QImage *output, const QString &filePathToExport);
    
signals:
    void finishedExport(const QString &result);

protected:
    void run() Q_DECL_OVERRIDE;
    
private:
    QMutex mutex;
    
    QImage *output;
    QString filePathToExport;
    QString result;    
};

#endif // IOTHREAD_H



