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

    Edge(Node *n1, Node *n2);
    void setText(QString text);
    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void updateEdge();
private:
    Node *node1;
    Node *node2;
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
