#ifndef TETRIS_H
#define TETRIS_H
#include <QWidget>
#include <QBasicTimer>
#include <QPainter>
#include <QKeyEvent>
#include "Shape.h"

class Tetris : public QWidget
{
    Q_OBJECT

public:
    Tetris(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void timerEvent(QTimerEvent *event);

public:

    static const int Height = 20;
    static const int Width = 10;
    int X;
    int Y;
    int board[Width][Height];

    void pixDown();
    void deleteLine();
    void newFigure();
    bool check(const Shape &newFigure, int newX, int newY);
    void gameOver(QPainter &);

    QBasicTimer timer;

    bool started;
    bool DeleteLine;

    Shape figure;
};

#endif
