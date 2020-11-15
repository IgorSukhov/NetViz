#include "node.h"

#include <QPainter>
#include <QDebug>

Node::Node(Node::nodeInfo_t nodeInfo) : info(nodeInfo)
{
    setRect(-25,-25,50,50);
    setBrush(Qt::white);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}




void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter,option,widget);
    //painter->drawRect(10,10,10,10);
    painter->drawText(QRectF(-23,-23,46,14), info.name);
}

uint32_t Node::getId()
{
    return info.id;
}



