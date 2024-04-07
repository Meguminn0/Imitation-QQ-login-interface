/******************************************************
 *
 * @file            loginwidget.h
 * @briefly         Login Widget
 *
 * @author          Meguminn0
 * @date            2024/04/05
 * @history
 *
********************************************************/

#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_Btn_min_clicked();
    void on_Btn_close_clicked();

private:
    void init();

private:
    Ui::LoginWidget *ui;
    bool m_readyMove;   /* mark widget is ready to move */
    QPoint m_currentPos;    /* the widget current pos in the window */
    QPoint m_mouseStartPoint;
};
#endif // LOGINWIDGET_H
