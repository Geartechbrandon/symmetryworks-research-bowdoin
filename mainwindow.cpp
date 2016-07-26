/****************************************************************************

Deploy on Mac: /Users/sngo/Applications/Qt/5.7/clang_64/bin/macdeployqt3

****************************************************************************/

#include "mainwindow.h"

MainWindow::MainWindow()
{
    
    currInterface = new Interface(this);
  
    // qDebug() << "setting " << this->currInterface << " to " << currInterface;

    QHBoxLayout *centerLayout = new QHBoxLayout();
    QWidget *centerWidget = new QWidget();
    centerLayout->addWidget(this->currInterface);
    centerWidget->setLayout(centerLayout);

    setCentralWidget(centerWidget);
    
    connect(this->currInterface, SIGNAL(imageActionStatus(bool)), this, SLOT(updateImageActionStatus(bool)));
    
    // QWidget *topFiller = new QWidget;
    // topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
    //                           "invoke a context menu</i>"));
    // infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    // infoLabel->setAlignment(Qt::AlignCenter);

    // QWidget *bottomFiller = new QWidget;
    // bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //undoStack = new QUndoStack(this);
    
    createActions();
    createMenus();
    createDockWindows();
   

    // QString message = tr("A context menu is available by right-clicking");
    // statusBar()->showMessage(message);
    
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    int x = (screenGeometry.width()-this->width()) * 0.3;
    int y = (screenGeometry.height()-this->height()) * 0.15;
    this->move(x, y);
                               
    setWindowTitle(tr("Wallpaper Generation"));
    
    
    setFixedSize(sizeHint());
    
    //setFixedSize(screenGeometry.width() * 0.6, screenGeometry.height() * 0.7);
    //resize(this->currInterface->width() * 0.85, this->currInterface->height() * 0.85);
}

MainWindow::~MainWindow()
{
    //delete currInterface;
    
}

//void MainWindow::changedCommand()
//{
//    QUndoCommand *changedCommand = new UndoCommand();
//    undoStack->push(changedCommand);
//}

// #ifndef QT_NO_CONTEXTMENU
// void MainWindow::contextMenuEvent(QContextMenuEvent *event)
// {
//     QMenu menu(this);
//     menu.addAction(cutAct);
//     menu.addAction(copyAct);
//     menu.addAction(pasteAct);
//     menu.exec(event->globalPos());
// }

// #endif // QT_NO_CONTEXTMENU

void MainWindow::createActions()
{
    // newAct = new QAction(tr("&New"), this);
    // newAct->setShortcuts(QKeySequence::New);
    // newAct->setStatusTip(tr("Create a new file"));
    // connect(newAct, &QAction::triggered, this, &MainWindow::newFile);

    loadAct = new QAction(tr("Load Workspace..."), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load an existing .wpr file"));
    connect(loadAct, SIGNAL(triggered()), currInterface, SLOT(loadFromSettings()));

    saveAct = new QAction(tr("Save Current Workspace"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the setting to disk"));
    connect(saveAct, SIGNAL(triggered()), currInterface, SLOT(saveCurrWorkspace()));
    
    saveAsAct = new QAction(tr("Save Current Workspace As..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct, SIGNAL(triggered()), currInterface, SLOT(saveCurrWorkspaceAs()));
    
    undoAct = currInterface->undoStack->createUndoAction(this, tr("&Undo"));
    undoAct->setShortcuts(QKeySequence::Undo);
//    connect(undoAct, SIGNAL(triggered()), currInterface->scaleAEdit, SLOT(undo()));
    
    redoAct = currInterface->undoStack->createRedoAction(this, tr("&Redo"));
    
    redoAct->setShortcuts(QKeySequence::Redo);
//    connect(redoAct, SIGNAL(triggered()), currInterface->scaleAEdit, SLOT(redo()));


    // printAct = new QAction(tr("&Print..."), this);
    // printAct->setShortcuts(QKeySequence::Print);
    // printAct->setStatusTip(tr("Print the document"));
    // connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exportImageAct = new QAction(tr("Export Image..."), this);
    // exportImageAct->setShortCuts()
    exportImageAct->setStatusTip(tr("Export to an image file"));
    connect(exportImageAct, SIGNAL(triggered()), currInterface, SLOT(exportImageFunction()));
    
    snapshotAct = new QAction(tr("Snapshot Image"), this);
    snapshotAct->setShortcut(QKeySequence("Ctrl+D"));
    snapshotAct->setStatusTip(tr("Save current instance to snapshots"));
    connect(snapshotAct, SIGNAL(triggered()), currInterface, SLOT(snapshotFunction()));
    
//    clearSnapshotsAct = new QAction(tr("Clear All Snapshots"), this);
//    clearSnapshotsAct->setShortcut(QKeySequence("Ctrl+K"));
//    clearSnapshotsAct->setStatusTip(tr("Save current instance to snapshots"));
//    connect(clearSnapshotsAct, SIGNAL(triggered()), currInterface->historyDisplay, SLOT(clearAllHistory()));

    // exitAct = new QAction(tr("Exit"), this);
    // exitAct->setShortcuts(QKeySequence::Quit);
    // exitAct->setStatusTip(tr("Exit the application"));
    // connect(exitAct, &QAction::triggered, this, &QWidget::close);

    setOverflowColorAct = new QAction(tr("Set Overflow Color..."), this);
    setOverflowColorAct->setStatusTip(tr("Set default color for overflow pixel on image"));
    connect(setOverflowColorAct, SIGNAL(triggered()), currInterface, SLOT(showOverflowColorPopUp()));
    setOverflowColorAct->setEnabled(false);

    showImageDataGraphAct = new QAction(tr("Show Image Data Points"), this);
    showImageDataGraphAct->setStatusTip(tr("Display a graph that shows points of image that are called up"));
    connect(showImageDataGraphAct, SIGNAL(triggered()), currInterface, SLOT(showImageDataGraph()));
    showImageDataGraphAct->setEnabled(false);

//    resetPreviewAct = new QAction(tr("Reset Preview"), this);
//    resetPreviewAct->setStatusTip(tr("Reset Preview Display Size"));
//    connect(resetPreviewAct, SIGNAL(triggered()), currInterface, SLOT(previewDisplayResetSize()));

//    viewTermsTableAct = new QAction(tr("View/Edit All Terms"), this);
//    viewTermsTableAct->setStatusTip(tr("View or Edit all function terms"));
//    connect(viewTermsTableAct, SIGNAL(triggered()), currInterface, SLOT(termViewPopUp()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    // fileMenu->addAction(newAct);
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    // fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    // fileMenu->addAction(exitAct);
    fileMenu->addAction(snapshotAct);
    //fileMenu->addAction(clearSnapshotsAct);
    fileMenu->addAction(exportImageAct);

     editMenu = menuBar()->addMenu(tr("Edit"));
     editMenu->addAction(undoAct);
     editMenu->addAction(redoAct);
     editMenu->addSeparator();

    
//     editMenu->addAction(cutAct);
//     editMenu->addAction(copyAct);
//     editMenu->addAction(pasteAct);
//     editMenu->addSeparator();

    // helpMenu = menuBar()->addMenu(tr("&Help"));
    // helpMenu->addAction(aboutAct);
    // helpMenu->addAction(aboutQtAct);

    viewMenu = menuBar()->addMenu(tr("Advanced"));
    //viewMenu->addAction(resetPreviewAct);
    viewMenu->addSeparator();
    viewMenu->addAction(setOverflowColorAct);
    viewMenu->addAction(showImageDataGraphAct);
    //viewMenu->addSeparator();
    //viewMenu->addAction(viewTermsTableAct);
}

void MainWindow::createDockWindows() 
{
    rightDock = new QDockWidget(tr("Snapshots"), this);
    rightDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    // rightDock->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // leftDock = new QDockWidget(tr("Pattern Previews"), this);
    // leftDock->setFeatures(QDockWidget::DockWidgetClosable);

    snapShotWindow = new HistoryDisplay(this);
    // functionIconsWindow = new QWidget(this, Qt::Window);

    currInterface->setSnapShotWindow(snapShotWindow);
    // currInterface->setFunctionIconsWindow(functionIconsWindow);

    rightDock->setWidget(snapShotWindow->viewHistoryWidget);
    // leftDock->setWidget(functionIconsWindow);

    // leftDock->setFixedSize(500, 600);

    // leftDock->hide();

    addDockWidget(Qt::RightDockWidgetArea, rightDock);
    // addDockWidget(Qt::LeftDockWidgetArea, leftDock);
}


//void MainWindow::moveEvent(QMoveEvent* event)
//{
//    const QPoint global = this->mapToGlobal(rect().center());
//    
//    QList<QWidget *> children = this->findChildren<QWidget *>();
//    
//    QList<QWidget *>::iterator i = children.begin();
//    
//    while (i != children.end()) {
//        if((*i)->isWindow()) {
//            (*i)->move(global.x() - (*i)->width() / 2, global.y() - (*i)->height() / 2);
//        }
//        ++i;
//       
//        
//    }
//    
//}
