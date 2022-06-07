#ifndef SHAPE_H
#define SHAPE_H


class Shape
{
public:
    void randomizer();
    Shape rotate();

    int number_of_figure;
    int coords[4][2];
    int figures[8][4][2] = {
                    { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } }, //
                    { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },// -|_
                    { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } }, // _|-
                    { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } }, // |
                    { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } }, // |-
                    { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } }, // квадрат
                    { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } }, // _|
                    { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }  // |_
    };

};
#endif // SHAPE_H
