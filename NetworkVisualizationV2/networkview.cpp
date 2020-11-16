#include "networkview.h"
#include <QDebug>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneContextMenuEvent>
#include <QMenu>
#include <QPoint>
#include <QPointF>
#include <QWheelEvent>
#include <QtMath>

NetworkView::NetworkView(QWidget *parent) : QGraphicsView(parent)
{
    QGraphicsScene *scene = new QGraphicsScene;
    setScene(scene);

    connect(scene,&QGraphicsScene::changed,[this]{for(Edge *e : edges) e->updateEdge();});
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

    Test();

}

void NetworkView::Test()
{
    static int y = 0;

    NetworkTopology *nt = new NetworkTopology;
    nt->Test1();

    for(size_t nodeNum = 0; nodeNum < nt->nodeCount; ++nodeNum)
    {
        Node *node = new Node(&nt->topologyDescription[nodeNum]);
        nodes.append(node);
        scene()->addItem(node);

        int x;
        if(node->nodeInfo->board_type == TYPE_REPE)
        {
            x = 0;
        }
        else if(node->nodeInfo->board_type == TYPE_FCB)
        {
            x = 100;
        }
        else if(node->nodeInfo->board_type == TYPE_DOP)
        {
            x = 200;
        }
        node->setPos(x,y);
        y+=100;
    }

    for(size_t edgeNum = 0; edgeNum < nt->edges.size(); ++edgeNum)
    {
        struct board *b1 = nt->edges[edgeNum].b1;
        struct board *b2 = nt->edges[edgeNum].b2;
        size_t b1p = nt->edges[edgeNum].port1;
        size_t b2p = nt->edges[edgeNum].port2;

        Node **n1;
        Node **n2;

        for(size_t portNum = 0; portNum < 4; ++portNum)
        {
            n1 = std::find_if(nodes.begin(), nodes.end(), [&portNum, &b1](const Node* value) { return value->nodeInfo == b1; });
            n2 = std::find_if(nodes.begin(), nodes.end(), [&portNum, &b2](const Node* value) { return value->nodeInfo == b2; });
        }
        if(n1 != nodes.end() || n2 != nodes.end())
        {
            Edge *edge = new Edge(*n1,b1p,*n2,b2p);
            edges.append(edge);
            scene()->addItem(edge);
            for(Node *n : nodes) edge->stackBefore(n);
        }

    }
}

//Node ** NetworkView::findNodeByLink(struct board *b)
//{

//    for(size_t portNum = 0; portNum < 4; ++portNum)
//    {
//        Node **n = std::find_if(nodes.begin(), nodes.end(), [&portNum, &b1](const Node* value) { return value->nodeInfo->p[portNum].node == b1; });

//    }
//    return n;
//}

//Node * NetworkView::addNode(qreal x, qreal y)
//{
//    //    Node **n = std::find_if(nodes.begin(),nodes.end(),[id](Node *n){return n->getId() == id;});
//    //    if(n != nodes.end())
//    //    {
//    //        qDebug() << "ID already exist";
//    //        return;
//    //    }
//    //    struct Node::nodeInfo_t info;
//    //    info.name = nodeName;
//    //    info.id = id;

//    Node *node = new Node;
//    nodes.append(node);
//    node->setPos(x,y);
//    scene()->addItem(node);
//    return node;
//}

void NetworkView::addEdge(uint32_t id1, uint32_t id2)
{
    //    Node **n1 = std::find_if(nodes.begin(),nodes.end(),[id1](Node *n){return n->getId() == id1;});
    //    Node **n2 = std::find_if(nodes.begin(),nodes.end(),[id2](Node *n){return n->getId() == id2;});
    //    if(n1 == nodes.end() || n2 == nodes.end())
    //    {
    //        qDebug() << "Unexpected ID of node";
    //        return;
    //    }

    //    Edge *edge = new Edge(*n1,*n2);
    //    edges.append(edge);
    //    scene()->addItem(edge);
    //    for(Node *n : nodes) edge->stackBefore(n);
}

void NetworkView::allignToGrid()
{
    for(Node *n : nodes)
    {
        n->setX(roundTo100(n->x()));
        n->setY(roundTo100(n->y()));
    }
}

qreal NetworkView::roundTo100(int n)
{
    if ( n / 10 % 10 < 5 )
        n = n / 100 * 100;
    else
        n = (n / 100 + 1) * 100;
    return n;
}

void NetworkView::udateEdges()
{
    for(Edge *e : edges) e->updateEdge();
}


void NetworkView::wheelEvent(QWheelEvent *event)
{
    qreal scaleFactor = qPow(2.0, event->delta() / 240.0); //How fast we zoom
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if(0.05 < factor && factor < 10) //Zoom factor limitation
        scale(scaleFactor, scaleFactor);

    //    scale(1,1);
    //    if(event->buttons() == Qt::MiddleButton)
    //    {

    //    }
}

//void NetworkView::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
//{
//   qDebug() << "contextMenuEvent";

//    QPointF pointf(event->scenePos());
//    QPoint point(pointf.x(),pointf.y());
//    QGraphicsItem *item = itemAt(point);
//    if(item)
//    {
//        //item->setSelected(true);
//        if(item->type() == Node::Type) qDebug() << "Node context menu";
//    }


//    //    qDebug() << (int)event->type();
//    //    if(event->type() == Node::Type)
//    //        qDebug() << "Node context menu";
//    //    QMenu menu("Node menu");

//    //    menu.addSeparator();
//    //    menu.addAction(tr("Informations"));
//    //    menu.addAction(tr("Options"));

//    //    QAction *action = menu.exec(QCursor::pos());
//    //    if(action == 0)
//    //        return;
//}

#include <QMessageBox>
void NetworkView::contextMenuEvent(QContextMenuEvent *event)
{
    QGraphicsItem *item = itemAt(event->pos());
    if(item)
    {
        if(item->type() == Node::Type)
        {
            QMenu menu("Node menu");
            menu.addSeparator();
            QAction *actionNodeInfo = menu.addAction(tr("Node info"));
            menu.addAction(tr("Node options"));
            connect(actionNodeInfo ,&QAction::triggered,[this]{QMessageBox::about(this,"Node","Hello node info");});
            QAction *action = menu.exec(QCursor::pos());
            if(action == 0) return;
        }
        else if(item->type() == Edge::Type)
        {
            QMenu *menu = new QMenu(this);
            menu->addAction(tr("Edge info"));
            menu->addAction(tr("Edge options"));
            QAction *action = menu->exec(QCursor::pos());
            if(action)
            {
                connect(action,&QAction::triggered,[&action]{qDebug() << action->text();});
            }
        }
    }
}





void NetworkView::mouseMoveEvent(QMouseEvent *event)
{
    static int i = 0;
    QGraphicsItem *item = itemAt(event->pos());
    if(item)
    {
        qDebug() << "item move" << ++i;
    }
    QGraphicsView::mouseMoveEvent(event);
}
