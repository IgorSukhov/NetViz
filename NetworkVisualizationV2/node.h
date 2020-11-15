#ifndef NODE_H
#define NODE_H

#include <QGraphicsRectItem>



class Node : public QGraphicsRectItem
{
public:

    struct nodeInfo_t
    {
        QString name;
        uint32_t id;
    };

    Node(nodeInfo_t nodeInfo);
    // QGraphicsItem interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    uint32_t getId();
private:
    nodeInfo_t info;

    // QGraphicsItem interface
public:
    enum { Type = UserType + 1 };
    int type() const override
    {
        return Type;
    }


};

#endif // NODE_H
