#include <QDebug>
#include "networktopology.h"

NetworkTopology::NetworkTopology()
{
    //Test1();
}

NetworkTopology::~NetworkTopology()
{
    delete[] topologyDescription;
}

bool NetworkTopology::parse(QByteArray msg)
{
    //TODO: implement message parsing

    return true;
}

void NetworkTopology::Test1()
{
    nodeCount = 5;
    topologyDescription = new board[nodeCount];

    topologyDescription[0] = {
        TYPE_REPE, //board_type
        {0,0,0,0,0,0}, //mac_addr
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, //gunid
        {{ PORT_TYPE_T1S, STATUS_ON, 0, 11, {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr }, //port_param
         { PORT_TYPE_100BASE, STATUS_ON, 0, 11, {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr }}
    };

    topologyDescription[1] = {
        TYPE_FCB,
        {0,0,0,0,0,0},
        {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {{ PORT_TYPE_T1S, STATUS_ON, 0, 11, {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_ON, 0, 11, {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr }}
    };

    topologyDescription[2] = {
        TYPE_FCB,
        {0,0,0,0,0,0},
        {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {{ PORT_TYPE_T1S, STATUS_ON, 0, 11, {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_ON, 0, 11, {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr }}
    };

    topologyDescription[3] = {
        TYPE_REPE,
        {0,0,0,0,0,0},
        {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {{ PORT_TYPE_100BASE, STATUS_ON, 0, 11, {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_ON, 0, 11, {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_1000BASE, STATUS_ON, 0, 11, {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr }}
    };

    topologyDescription[4] = {
        TYPE_REPE,
        {0,0,0,0,0,0},
        {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {{ PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_T1S, STATUS_OFF, 0, 11, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr },
         { PORT_TYPE_1000BASE, STATUS_ON, 0, 11, {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, nullptr }}
    };


    makeConnections(topologyDescription, nodeCount);

    //delete[] topologyDescription;
    //topologyDescription = nullptr;
}

void NetworkTopology::makeConnections(struct board *b, int boardsCount)
{
    for(int bn=0; bn<boardsCount-1; ++bn)
    {
        for(int bm=bn+1; bm<boardsCount; ++bm)
        {
            connectBoards(&b[bn], &b[bm]);
        }
    }
}

void NetworkTopology::connectBoards(board *b1, board *b2)
{
    for(int p1=0;p1<4;++p1)
    {
        for(int p2=0;p2<4;++p2)
        {
            connectPorts(b1,p1,b2,p2);
        }
    }
}

void NetworkTopology::connectPorts(struct board *b1, size_t b1p, struct board *b2, size_t b2p)
{
    if(b1->p[b1p].ps != STATUS_ON) return;
    if(b2->p[b2p].ps != STATUS_ON) return;

    bool b1Tob2 = isGunidEqual(b1->p[b1p].gunid, b2->gunid);
    bool b2Tob1 = isGunidEqual(b2->p[b2p].gunid, b1->gunid);


    if( b1Tob2 && b2Tob1 )
    {
        if(b1->p[b1p].node != nullptr) qDebug() << "Error: assign to assigned port";
        if(b2->p[b2p].node != nullptr) qDebug() << "Error: assign to assigned port";

        if(b1->p[b1p].pt != b2->p[b2p].pt) qDebug() << "Error: different connection types at ports";
        b1->p[b1p].node = b2;
        b2->p[b2p].node = b1;

        struct EdgeInfo_t edge = { b1, b1p, b2, b2p};
        edges.append(edge);

        //qDebug() << "Connection done: " << (uint8_t)b1->gunid[0] << b1p << (uint8_t)b2->gunid[0] << b2p;
    }
}

bool NetworkTopology::isGunidEqual(uint8_t gunid1[16], uint8_t gunid2[16])
{
    for(int i=0; i<16; ++i)
    {
        if(gunid1[i] != gunid2[i]) return false;
    }
    return true;
}
