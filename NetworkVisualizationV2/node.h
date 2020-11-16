#ifndef NODE_H
#define NODE_H

#include <QGraphicsRectItem>
#include "topologytypes.h"


class Node : public QGraphicsRectItem
{
public:

    struct board *nodeInfo;

    Node(struct board *nodeInfo);
    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    QString text;
    // QGraphicsItem interface
public:
    enum { Type = UserType + 1 };
    int type() const override
    {
        return Type;
    }


};

#endif // NODE_H
