#include "window.h"

MainWindow::MainWindow()
{
    QCoreApplication::setApplicationName("Lab 01");
    setWindowTitle(tr("Лабораторная 1"));
    createPlotWidget();
    createMenuBar();
}


void MainWindow::createPlotWidget()
{
    plot = new PlotWidget(this);
    setMinimumSize(500, 500);
    setContentsMargins(0, 0, 0, 0);
    setCentralWidget(plot);
}

void MainWindow::createMenuBar()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&Файл"));

    QAction *loadAct = new QAction(tr("&Открыть..."), this);
    loadAct->setShortcuts(QKeySequence::Open);
    connect(loadAct, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(loadAct);

    QAction *saveAct = new QAction(tr("&Сохранить"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(saveAct);

    QAction *saveAsAct = new QAction(tr("&Сохранить Как..."), this);
    saveAsAct->setShortcuts(QKeySequence::SaveAs);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveAsFile);
    fileMenu->addAction(saveAsAct);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Помощь"));

    QAction *infoAct = new QAction(tr("&Как Использовать?"), this);
    connect(infoAct, &QAction::triggered, this, &MainWindow::infoBox);
    helpMenu->addAction(infoAct);

    QAction *aboutAct = new QAction(tr("&О Программе"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::aboutBox);
    helpMenu->addAction(aboutAct);
}

void MainWindow::openFile()
{
    if (continueCloseFile())
    {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        tr("Open Model"), "/dev/oop",
                                                        tr("Text file (*.txt)"));
        plot->fileEvent(file_open, fileName.toLocal8Bit().data());
    }
}

void MainWindow::saveFile()
{
    plot->fileEvent();
}

void MainWindow::saveAsFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Model As"), "",
                                                    tr("Text file (*.txt)"));
    plot->fileEvent(file_save_as, fileName.toLocal8Bit().data());
}

void MainWindow::infoBox()
{
    QMessageBox::about(this, "Помощь", "Для открытия и сохранения файла используйте меню программы.\n"
                                       "Дла вращения объекта - зажмите мышь и переместите её.\n"
                                       "Для уменьшения/увеличения объекта - колёсико мыши.\n"
                                       "Для перемещения по холсту - зажмите пробел и мышь, после этого переместите мышь.\n"
                                       "Для перемещения без захвата центра - зажмите Cntr(Cmd) и мышь, после этого переместите мышь.");

}

void MainWindow::aboutBox()
{
    QMessageBox::about(this, "О программе", "Лабораторная работа №1 по ООП,\n"
                                            "разработано Тагиловым А.М.\n"
                                            "ИУ7-45Б, МГТУ им.Н.Э.Баумана\n");
}

bool MainWindow::continueCloseFile()
{
    bool continue_needed = true;
    if (!plot->getSaved())
    {
        QMessageBox msgBox;
        msgBox.setText("Модель была изменена!");
        msgBox.setInformativeText("Сохранить изменения?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Save, "Да");
        msgBox.setButtonText(QMessageBox::Discard, "Нет");
        msgBox.setButtonText(QMessageBox::Cancel, "Отмена");
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
            case QMessageBox::Cancel:
                continue_needed = false;
                break;
            case QMessageBox::Save:
                saveFile();
                break;
        }
    }
    return continue_needed;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!continueCloseFile())
        event->ignore();
}


