/*
    Fatih (6251581), Javi (), Lesik (6081100), Kelvin Tsang (5428328)

    Milestone 1

*/
#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QMouseEvent>
#include <QTimer>
#include <QWidget>
#include "CAbase.h"

class GameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void paintGrid();
    void paintUniverse();

signals:

public slots:
    void setTimerIntervall(int t);
    void setUniverseSize(int size);
    void startGame();
    void stopGame();
    void clear();
    void newGeneration();
    void saveToFile();
    void loadFromFile();

private:                    // Private Variablen
    QTimer *timer;
    QColor colour;
    int universeSize;
    CAbase ca;              // CAbase aus vorherigen Aufgaben
};

#endif // GAMEWIDGET_H
