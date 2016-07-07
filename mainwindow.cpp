/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "mainwindow.h"

MainWindow::MainWindow()
{
    currInterface = new interface();

    // qDebug() << "setting " << this->currInterface << " to " << currInterface;

    QHBoxLayout *centerLayout = new QHBoxLayout();
    QWidget *centerWidget = new QWidget();
    centerLayout->addWidget(this->currInterface);
    centerWidget->setLayout(centerLayout);

    setCentralWidget(centerWidget);

    // QWidget *topFiller = new QWidget;
    // topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
    //                           "invoke a context menu</i>"));
    // infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    // infoLabel->setAlignment(Qt::AlignCenter);

    // QWidget *bottomFiller = new QWidget;
    // bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    createActions();
    createMenus();

    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);

    setWindowTitle(tr("Bridget & Son"));
    setMinimumSize(160, 160);
    resize(this->currInterface->width() * 1.05, this->currInterface->height() * 1.05);
}

MainWindow::~MainWindow()
{
    delete currInterface;
}

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

    loadAct = new QAction(tr("Load..."), this);
    loadAct->setShortcuts(QKeySequence::Open);
    loadAct->setStatusTip(tr("Load an existing file"));
    connect(loadAct, SIGNAL(triggered()), currInterface, SLOT(loadFromSettings()));

    saveAct = new QAction(tr("Save..."), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save the setting to disk"));
    connect(saveAct, SIGNAL(triggered()), currInterface, SLOT(saveCurrSettings()));

    // printAct = new QAction(tr("&Print..."), this);
    // printAct->setShortcuts(QKeySequence::Print);
    // printAct->setStatusTip(tr("Print the document"));
    // connect(printAct, &QAction::triggered, this, &MainWindow::print);

    exportImageAct = new QAction(tr("Export Image"), this);
    // exportImageAct->setShortCuts()
    exportImageAct->setStatusTip(tr("Export to an image file"));
    connect(exportImageAct, SIGNAL(triggered()), currInterface, SLOT(exportImageFunction()));

    // exitAct = new QAction(tr("Exit"), this);
    // exitAct->setShortcuts(QKeySequence::Quit);
    // exitAct->setStatusTip(tr("Exit the application"));
    // connect(exitAct, &QAction::triggered, this, &QWidget::close);

    enlargePreviewAct = new QAction(tr("Enlarge Preview"), this);
    enlargePreviewAct->setStatusTip(tr("Enlarge Preview Display by 25 %%"));
    connect(enlargePreviewAct, SIGNAL(triggered()), currInterface, SLOT(previewDisplayEnlarge()));

    shrinkPreviewAct = new QAction(tr("Shrink Preview"), this);
    shrinkPreviewAct->setStatusTip(tr("Shrink Preview Display by 25 %%"));
    connect(shrinkPreviewAct, SIGNAL(triggered()), currInterface, SLOT(previewDisplayShrink()));

    resetPreviewAct = new QAction(tr("Reset Preview"), this);
    resetPreviewAct->setStatusTip(tr("Reset Preview Display Size"));
    connect(resetPreviewAct, SIGNAL(triggered()), currInterface, SLOT(previewDisplayResetSize()));

    // undoAct = new QAction(tr("&Undo"), this);
    // undoAct->setShortcuts(QKeySequence::Undo);
    // undoAct->setStatusTip(tr("Undo the last operation"));
    // connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    // redoAct = new QAction(tr("&Redo"), this);
    // redoAct->setShortcuts(QKeySequence::Redo);
    // redoAct->setStatusTip(tr("Redo the last operation"));
    // connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    // cutAct = new QAction(tr("Cu&t"), this);
    // cutAct->setShortcuts(QKeySequence::Cut);
    // cutAct->setStatusTip(tr("Cut the current selection's contents to the "
    //                         "clipboard"));
    // connect(cutAct, &QAction::triggered, this, &MainWindow::cut);

    // copyAct = new QAction(tr("&Copy"), this);
    // copyAct->setShortcuts(QKeySequence::Copy);
    // copyAct->setStatusTip(tr("Copy the current selection's contents to the "
    //                          "clipboard"));
    // connect(copyAct, &QAction::triggered, this, &MainWindow::copy);

    // pasteAct = new QAction(tr("&Paste"), this);
    // pasteAct->setShortcuts(QKeySequence::Paste);
    // pasteAct->setStatusTip(tr("Paste the clipboard's contents into the current "
    //                           "selection"));
    // connect(pasteAct, &QAction::triggered, this, &MainWindow::paste);

    // boldAct = new QAction(tr("&Bold"), this);
    // boldAct->setCheckable(true);
    // boldAct->setShortcut(QKeySequence::Bold);
    // boldAct->setStatusTip(tr("Make the text bold"));
    // connect(boldAct, &QAction::triggered, this, &MainWindow::bold);

    // QFont boldFont = boldAct->font();
    // boldFont.setBold(true);
    // boldAct->setFont(boldFont);

    // italicAct = new QAction(tr("&Italic"), this);
    // italicAct->setCheckable(true);
    // italicAct->setShortcut(QKeySequence::Italic);
    // italicAct->setStatusTip(tr("Make the text italic"));
    // connect(italicAct, &QAction::triggered, this, &MainWindow::italic);

    // QFont italicFont = italicAct->font();
    // italicFont.setItalic(true);
    // italicAct->setFont(italicFont);

    // setLineSpacingAct = new QAction(tr("Set &Line Spacing..."), this);
    // setLineSpacingAct->setStatusTip(tr("Change the gap between the lines of a "
    //                                    "paragraph"));
    // connect(setLineSpacingAct, &QAction::triggered, this, &MainWindow::setLineSpacing);

    // setParagraphSpacingAct = new QAction(tr("Set &Paragraph Spacing..."), this);
    // setParagraphSpacingAct->setStatusTip(tr("Change the gap between paragraphs"));
    // connect(setParagraphSpacingAct, &QAction::triggered,
    //         this, &MainWindow::setParagraphSpacing);

    // aboutAct = new QAction(tr("&About"), this);
    // aboutAct->setStatusTip(tr("Show the application's About box"));
    // connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    // aboutQtAct = new QAction(tr("About &Qt"), this);
    // aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    // connect(aboutQtAct, &QAction::triggered, qApp, &QApplication::aboutQt);
    // connect(aboutQtAct, &QAction::triggered, this, &MainWindow::aboutQt);

    // leftAlignAct = new QAction(tr("&Left Align"), this);
    // leftAlignAct->setCheckable(true);
    // leftAlignAct->setShortcut(tr("Ctrl+L"));
    // leftAlignAct->setStatusTip(tr("Left align the selected text"));
    // connect(leftAlignAct, &QAction::triggered, this, &MainWindow::leftAlign);

    // rightAlignAct = new QAction(tr("&Right Align"), this);
    // rightAlignAct->setCheckable(true);
    // rightAlignAct->setShortcut(tr("Ctrl+R"));
    // rightAlignAct->setStatusTip(tr("Right align the selected text"));
    // connect(rightAlignAct, &QAction::triggered, this, &MainWindow::rightAlign);

    // justifyAct = new QAction(tr("&Justify"), this);
    // justifyAct->setCheckable(true);
    // justifyAct->setShortcut(tr("Ctrl+J"));
    // justifyAct->setStatusTip(tr("Justify the selected text"));
    // connect(justifyAct, &QAction::triggered, this, &MainWindow::justify);

    // centerAct = new QAction(tr("&Center"), this);
    // centerAct->setCheckable(true);
    // centerAct->setShortcut(tr("Ctrl+E"));
    // centerAct->setStatusTip(tr("Center the selected text"));
    // connect(centerAct, &QAction::triggered, this, &MainWindow::center);

    // alignmentGroup = new QActionGroup(this);
    // alignmentGroup->addAction(leftAlignAct);
    // alignmentGroup->addAction(rightAlignAct);
    // alignmentGroup->addAction(justifyAct);
    // alignmentGroup->addAction(centerAct);
    // leftAlignAct->setChecked(true);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("File"));
    // fileMenu->addAction(newAct);
    fileMenu->addAction(loadAct);
    fileMenu->addAction(saveAct);
    // fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    // fileMenu->addAction(exitAct);

    // editMenu = menuBar()->addMenu(tr("&Edit"));
    // editMenu->addAction(undoAct);
    // editMenu->addAction(redoAct);
    // editMenu->addSeparator();
    // editMenu->addAction(cutAct);
    // editMenu->addAction(copyAct);
    // editMenu->addAction(pasteAct);
    // editMenu->addSeparator();

    // helpMenu = menuBar()->addMenu(tr("&Help"));
    // helpMenu->addAction(aboutAct);
    // helpMenu->addAction(aboutQtAct);

    viewMenu = menuBar()->addMenu(tr("View"));
    viewMenu->addAction(enlargePreviewAct);
    viewMenu->addAction(shrinkPreviewAct);
    viewMenu->addAction(resetPreviewAct);
}
