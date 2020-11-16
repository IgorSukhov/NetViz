#ifndef NETWORKTOPOLOGY_H
#define NETWORKTOPOLOGY_H

#include <QByteArray>
#include <QPair>
#include <stdint.h>
#include "topologytypes.h"

class NetworkTopology
{

public:

    struct EdgeInfo_t
    {
        struct board* b1;
        size_t port1;
        struct board* b2;
        size_t port2;
    };

    NetworkTopology();
    ~NetworkTopology();
    bool parse(QByteArray topologyDescription);
    board *topologyDescription = nullptr;
    size_t nodeCount;

    QVector< EdgeInfo_t > edges;

    void Test1();

private:
    bool isGunidEqual(uint8_t gunid1[], uint8_t gunid2[]);
    bool tryConnect(struct board b1, int b1p, struct board b2, int b2p);
    void connectBoards(struct board *b1, struct board *b2);
    void connectPorts(struct board *b1, size_t b1p, struct board *b2, size_t b2p);
    void makeConnections(struct board *b, int boardsCount);
};

#endif // NETWORKTOPOLOGY_H
