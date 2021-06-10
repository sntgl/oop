#pragma once

#include <QMainWindow>
#include <QApplication>
#include <QPainter>
#include <QPushButton>
#include <QtWidgets>

#include "../backend/types.h"
#include "plot_widget.h"

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();

private:
    PlotWidget *plot;

    void closeEvent(QCloseEvent *event);

    void openFile();

    void saveFile();

    void saveAsFile();

    void createMenuBar();

    void createPlotWidget();

    void aboutBox();

    void infoBox();

    bool continueCloseFile();

};
