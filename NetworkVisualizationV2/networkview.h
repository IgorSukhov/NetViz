#ifndef NETWORKVIEW_H
#define NETWORKVIEW_H

#include "node.h"
#include "edge.h"
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsSceneContextMenuEvent>

class Node;

class NetworkView : public QGraphicsView
{
public:
    NetworkView(QWidget *parent = nullptr);

    void addNode(qreal x, qreal y, QString nodeName, uint32_t id);
    void addEdge(uint32_t id1, uint32_t id2);

    void allignToGrid();

    QGraphicsLineItem *l;

    QVector<Node*> nodes;
    QVector<Edge*> edges;
private slots:
    void udateEdges();
private:
    qreal roundTo100(int n);

    // QWidget interface
protected:
    virtual void wheelEvent(QWheelEvent *event) override;



    // QWidget interface
protected:
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
};



#endif // NETWORKVIEW_H
