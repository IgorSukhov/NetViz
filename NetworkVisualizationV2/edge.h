#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsLineItem>
#include "node.h"

class Edge : public QGraphicsLineItem
{
public:

    struct edgeInfo_t
    {
        QString name;

    };

    Edge(Node *n1, size_t n1p, Node *n2, size_t n2p);
    void setText(QString text);
    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void updateEdge();
private:
    Node *node1;
    size_t node1port;
    Node *node2;
    size_t node2port;
    QRectF getRect();
    QString m_text;
    QGraphicsTextItem *textItem;

public:
    enum { Type = UserType + 2 };
    int type() const override
    {
        return Type;
    }

};

#endif // EDGE_H
