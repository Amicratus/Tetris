#include "Shape.h"
#include <QRandomGenerator>

void Shape::randomizer()
{
    int figure = QRandomGenerator::global()->generate() % 7 + 1;
        for (int i = 0; i < 4 ; ++i) {
            for (int j = 0; j < 2; ++j)
                coords[i][j] = figures[figure][i][j];
        }
        number_of_figure = figure;
}
