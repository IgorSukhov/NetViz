#ifndef NETWORKTOPOLOGY_H
#define NETWORKTOPOLOGY_H

#include <stdint.h>
#include "topologytypes.h"

class NetworkTopology
{




public:
    NetworkTopology();
private:
    bool isGunidEqual(uint8_t gunid1[], uint8_t gunid2[]);
    bool tryConnect(board b1, int b1p, board b2, int b2p);
    void connectBoards(board &b1, board &b2);
    void connectPorts(board &b1, int b1p, board &b2, int b2p);
    void makeConnections(board *b, int boardsCount);
    void Test1();
};

#endif // NETWORKTOPOLOGY_H
