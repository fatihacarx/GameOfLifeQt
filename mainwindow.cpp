/*
    Fatih (6251581), Javi (), Lesik (6081100), Kelvin Tsang (5428328)

    Milestone 1

*/
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    game(new GameWidget(this))
{
    ui->setupUi(this);
    ui->gridLayout->addWidget(game);
}

MainWindow::~MainWindow() {delete ui;}

// Widgets im mainwindow.ui werden zu Funktionen in gamewidget zugewiesen
void MainWindow::on_Button_start_clicked() {game->startGame();}
void MainWindow::on_Button_stop_clicked() {game->stopGame();}
void MainWindow::on_Button_clear_clicked() {game->clear();}
void MainWindow::on_SpinBox_universe_size_valueChanged(int arg1) {game->setUniverseSize(arg1);}
void MainWindow::on_SpinBox_generation_intervall_valueChanged(int arg1) {game->setTimerIntervall(arg1);}
void MainWindow::on_Button_save_clicked() {game->saveToFile();}
void MainWindow::on_Button_load_clicked() {game->loadFromFile();}
