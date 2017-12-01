/*
    Fatih (6251581), Javi (), Lesik (6082200), Kelvin Tsang (5428328)

    Milestone 1

*/
#include "gamewidget.h"
#include <QTimer>
#include <QMouseEvent>
#include <QRectF>
#include <QPainter>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
using namespace std;

GameWidget::GameWidget(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this))
{
    // der Timer wird mit dem Slot newGeneration verbunden
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

// Setter
void GameWidget::setTimerIntervall(int t) {timer->setInterval(t);}
void GameWidget::setUniverseSize(int size) {
    universeSize = size;
    ca.setSize(size, size);
    // update damit die neue Groeße die mit der Spinbox veraendert wurde
    // angezeigt wird
    update();
}

// Start, Stop und Clear Funktion
void GameWidget::startGame() {timer->start();}
void GameWidget::stopGame() {timer->stop();}
void GameWidget::clear() {setUniverseSize(universeSize);}

void GameWidget::newGeneration() {
    ca.evolve();        // evolve() von CAbase
    update();
}

// wenn die Maustaste geklickt worden ist, soll die Funktion ausgeführt werden
void GameWidget::mousePressEvent(QMouseEvent *event) {
    // 580 ist die Groeße die wir im mainwindow.ui festgelegt haben
    double cellGeometry = 580.00/universeSize;
    // hier wird die Position des Mauszeigers abgefragt
    int xPosition = event->x()/cellGeometry;
    int yPosition = event->y()/cellGeometry;
    // je nach dem ob die lebendig war oder nicht wird sie invertiert
    if (ca.getCell(xPosition, yPosition) == 0) {
        ca.setCell(xPosition, yPosition, 1);
    }
    else ca.setCell(xPosition, yPosition, 0);
    update();
}

// wenn die Maustaste geklickt worden ist, soll die Funktion ausgeführt werden
void GameWidget::mouseMoveEvent(QMouseEvent *event) {
    double cellGeometry = 580.00/universeSize;
    int xPosition = event->x()/cellGeometry;
    int yPosition = event->y()/cellGeometry;
    if (ca.getCell(xPosition, yPosition) == 0) {
        ca.setCell(xPosition, yPosition, 1);
    }
    update();
}

// wird ausgefuert wenn update() ausgefuehrt wurde
void GameWidget::paintEvent(QPaintEvent *)
{
    paintGrid();
    paintUniverse();
}

// auf das widget wird ein Raster gezeichnet, indem Linien horizontal und vertikal
// gezeichnet werden. Am Ende zeichnet es einen Rechteck am Rand.
void GameWidget::paintGrid()
{
    QPainter painter(this);
    QRect rec(0, 0, 580, 580);
    double cellGeometry = 580.00 / universeSize;
    for(double i = 0; i <= 580.00; i += cellGeometry) {
        painter.drawLine(i, 0, i, 580.00);
        painter.drawLine(0, i, 580.00, i);
    }
    painter.drawRect(rec);
}

// zeichnet die lebenden Zellen, indem es einen schwarz gefuellten Quadrat
// an die Position zeichnet
void GameWidget::paintUniverse() {
    QPainter painter(this);
    double cellGeometry = 580.00 / universeSize;
    for(int j = 0; j < universeSize; j++) {
        for(int i = 0; i < universeSize; i++) {
            if(ca.getCell(i, j) == 1) {
                // QRectF weil es double nimmt, somit praeziser
                QRectF rec(i * cellGeometry, j * cellGeometry, cellGeometry, cellGeometry);
                painter.fillRect(rec, Qt::black);                   // Zelle wird schwarz gefüllt
            }
        }
    }
}

void GameWidget::saveToFile() {
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Current Universe"), "",
            tr("Textfile (*.txt);;All Files (*)"));                 // Speicherdatei wird als *txt gespeichert

    QFile myFile(fileName);
    if (myFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QTextStream stream(&myFile);
            stream << universeSize << endl;                         // Spielfeldgröße wird gepeichert
            for (int j = 0; j < universeSize; j++) {
                for (int i = 0; i < universeSize; i++) {
                    stream << ca.getCell(i, j) << endl;             // komplettes Spielfeld wird mit 0 und 1 gespeichert
                }
            }
    }
    myFile.close();
}

void GameWidget::loadFromFile() {
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Load Saved Universe"), "",
            tr("Textfile (*.txt);;All Files (*)"));                 // *txt wird geladen
    QFile myFile(fileName);
    if (myFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream in(&myFile);
        QString line = in.readLine();                               // nimmt die erste Zeile
        setUniverseSize(line.toInt());                              // Spielfeldgröße wird gelesen und geladen
        int i = 0;
        // jede Zeile wird durchgegangen und zu seiner Position im Array hinzugefügt
        while(!in.atEnd()) {    
            QString line = in.readLine();
            ca.getCurrentWorld()[i] = line.toInt();                 // Spielfeld wird gelesen und geladen
            i++;
        }
    }
    myFile.close();
}
