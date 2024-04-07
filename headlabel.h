/******************************************************
 *
 * @file            headlabel.h
 * @briefly         override Qlabel for user avatar
 *
 * @author          Meguminn0
 * @date            2024/04/06
 * @history
 *
********************************************************/

#ifndef HEADLABEL_H
#define HEADLABEL_H

#include <QLabel>

class headLabel : public QLabel
{
public:
    headLabel(QWidget *parent);

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // HEADLABEL_H
