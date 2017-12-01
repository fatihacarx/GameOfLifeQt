/*
    Fatih (6251581), Javi (), Lesik (6081100), Kelvin Tsang (5428328)

    Milestone 1

*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gamewidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    GameWidget *game;

private slots:
    void on_Button_start_clicked();
    void on_Button_stop_clicked();
    void on_Button_clear_clicked();
    void on_SpinBox_universe_size_valueChanged(int arg1);
    void on_SpinBox_generation_intervall_valueChanged(int arg1);
    void on_Button_save_clicked();
    void on_Button_load_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
