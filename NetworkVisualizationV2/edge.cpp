#include "edge.h"

#include <QPainter>
#include <QDebug>
#include <QGraphicsScene>

Edge::Edge(Node *n1, size_t n1p, Node *n2, size_t n2p) : node1(n1), node1port(n1p), node2(n2), node2port(n2p)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setPen(QPen(QBrush(Qt::green),5));
    if(n1->nodeInfo->p[n1p].pt == PORT_TYPE_T1S)
    {
        setPen(QPen(QBrush(Qt::blue),5));
        textItem = new QGraphicsTextItem("T1S", this);
    }
    else if(n1->nodeInfo->p[n1p].pt == PORT_TYPE_100BASE)
    {
        setPen(QPen(QBrush(Qt::green),5));
        textItem = new QGraphicsTextItem("100BASE", this);
    }
    else if(n1->nodeInfo->p[n1p].pt == PORT_TYPE_1000BASE)
    {
        setPen(QPen(QBrush(Qt::green),5));
        textItem = new QGraphicsTextItem("1000BASE", this);
    }

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
