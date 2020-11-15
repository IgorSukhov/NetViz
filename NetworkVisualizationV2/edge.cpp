#include "edge.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>

Edge::Edge(Node *n1, Node *n2) : node1(n1), node2(n2)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(QBrush(Qt::green),5));
    textItem = new QGraphicsTextItem("T1S", this);
}

void Edge::setText(QString text)
{
    textItem->setPlainText(text);
}

void Edge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QGraphicsLineItem::paint(painter, option, widget);
    painter->setBrush(QColor(Qt::white));
     painter->setPen(QColor(Qt::white));
    QRectF tbr = textItem->boundingRect();
    tbr.moveCenter(getRect().center());
    painter->drawRect(tbr);
}

void Edge::updateEdge()
{
    setLine(QLineF(node1->pos(),node2->pos()));
    QPointF cbr = textItem->boundingRect().center();
    QPointF cl = getRect().center();
    textItem->setPos(cl-cbr);
}

QRectF Edge::getRect()
{
    return QRectF(node1->pos(),node2->pos());
}
