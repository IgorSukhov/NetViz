#include "node.h"

#include <QPainter>
#include <QDebug>

Node::Node(board *nodeInfo)  : nodeInfo(nodeInfo)
{
    setRect(-25,-25,50,50);
    setBrush(Qt::white);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    if(nodeInfo->board_type == TYPE_REPE) text = "KCE";
    if(nodeInfo->board_type == TYPE_FCB) text = "FCB";
    if(nodeInfo->board_type == TYPE_DOP) text = "DOP";
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsRectItem::paint(painter,option,widget);
    painter->drawText(QRectF(-23,-23,46,14), text);
}




