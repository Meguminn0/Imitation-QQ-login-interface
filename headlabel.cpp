#include "headlabel.h"

#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>

headLabel::headLabel(QWidget *parent) : QLabel(parent)
{

}

void headLabel::paintEvent(QPaintEvent *e)
{
    if (this->pixmap().isNull()) {
        return;
    }

    // 获取当前QLabel的大小
    QSize size = this->size();

    // 创建画家对象
    QPainter painter(this);

    // 开启抗锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // 创建一个与标签同样大小的椭圆区域
    QRect rect(0, 0, size.width(), size.height());
    QPainterPath path;
    path.addEllipse(rect);

    // 设置剪裁路径为椭圆
    painter.setClipPath(path);

    // 缩放图像以适应标签大小且保持宽高比
    QPixmap scaledPixmap = this->pixmap().scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 绘制图像至中心位置
    QPointF center(size.width() / 2, size.height() / 2);
    painter.drawPixmap(center - QPointF(scaledPixmap.width() / 2, scaledPixmap.height() / 2), scaledPixmap);
    painter.save();

    // 绘制一个圆角矩形作为图像的边框
    painter.setPen(QPen(QColor(69,134,247, 50), 4)); // 边框宽度为4像素
//        painter.setPen(QPen(QColor(0, 0, 0), 4)); // 边框宽度为4像素
    painter.setBrush(Qt::NoBrush); // 不填充内部区域
    painter.drawRoundedRect(rect, 50.0, 50.0); // 调整矩形区域使其内缩1像素，避免覆盖内部背景
    painter.restore();
}
