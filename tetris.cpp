#include "tetris.h"

Tetris::Tetris(QWidget *parent): QWidget(parent){

    setStyleSheet("background-color: black");
    resize(450,940);

    started = true;
    DeleteLine = false;

    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 20; ++j)
            board[i][j] = 0;

    newFigure();

    timer.start(300, this);
}

void Tetris::keyPressEvent(QKeyEvent *event)
{
    int key = event -> key();

    if (key == Qt::Key_Left)
        check(figure, X - 1, Y);

    if (key == Qt::Key_Right)
        check(figure, X + 1, Y);

    if (key == Qt::Key_Up)
        check(figure.rotate(), X, Y);

    if (key == Qt::Key_Down)
        pixDown();

    QWidget::keyPressEvent(event);
}

void Tetris::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);

    if(started){
        for (int i = 0; i < Height; ++i) {
            for (int j = 0; j < Width; ++j) {
                int shape = board[j][Height - i - 1];
                if (shape != 0){
                    QPixmap pic("block.png");
                    pic = pic.scaled(40,40);
                    painter.drawImage( j * contentsRect().width() / Width + 1, i * contentsRect().height() / Height + 1, pic.toImage());
                }
            }
        }


            for (int i = 0; i < 4; ++i) {
                int x = X + figure.coords[i][0];
                int y = Y - figure.coords[i][1];
                QPixmap pic("block.png");
                pic = pic.scaled(40,40);
                painter.drawImage(x * contentsRect().width() / Width + 1,(Height - y - 1)* contentsRect().height() / Height + 1,   pic.toImage());

        }
    }
    else
        gameOver(painter);
}
void Tetris::timerEvent(QTimerEvent *event)
{
        Q_UNUSED(event);
        if (DeleteLine) {
            DeleteLine = false;
            newFigure();
        }
        else
            pixDown();
}

void Tetris::pixDown()
{
    if (!check(figure, X, Y - 1)){
        for (int i = 0; i < 4; i++) {
            int x = X + figure.coords[i][0];
            int y = Y - figure.coords[i][1];
             board[x][y] = figure.number_of_figure;
        }
        deleteLine();

        if (!DeleteLine)
            newFigure();
    }
}

void Tetris::deleteLine()
{
    for (int i = 0; i < Height - 1; i++) {
        bool lineIsFull = true;
        for (int j = 0; j < Width; j++) {
            if (board[j][i] == 0) {
                lineIsFull = false;
                break;
            }
        }

        if (lineIsFull) {
            for (int k = i; k < Height - 1; k++) {
                for (int j = 0; j < Width; j++)
                    board[j][k] = board[j][k + 1];
            }
            for (int j = 0; j < Width; j++)
                board[j][Height - 1]= 0;
        }
    }
    DeleteLine = true;
    //repaint();
}

void Tetris::newFigure()
{
    figure.randomizer();
    X = 5;
    Y = 18;
    if (!check(figure, X, Y)) {
        started = false;
        timer.stop();
    }
}

void Tetris::gameOver(QPainter &qp) {

    QString message = "Game Over";
    QFont font("Bauhaus 93", 30, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(message);

    qp.setPen(QColor(Qt:: white));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth / 2, -100, message);
}

bool Tetris::check(const Shape &Figure_N, int newX, int newY)
{
    for (int i = 0; i < 4; ++i) {
        int x = newX + Figure_N.coords[i][0];
        int y = newY - Figure_N.coords[i][1];
        if (x < 0 || x >= Width || y < 0 || y >= Height)
            return false;
        if (board[x][y] != 0)
            return false;
    }

    figure = Figure_N;
    X = newX;
    Y = newY;
    repaint();
    return true;
}

Shape Shape::rotate()
{
    if (number_of_figure == 5 )
        return *this;

    Shape result;
    result.number_of_figure = number_of_figure;
    for (int i = 0; i < 4; ++i) {
        result.coords[i][0] = -1 * coords[i][1];
        result.coords[i][1] = coords[i][0];
    }
    return result;
}
