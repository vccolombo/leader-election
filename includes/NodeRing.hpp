#pragma once

#include "NodeBase.hpp"

class NodeRing : protected NodeBase<NodeRing> {
   private:
    uint32_t election = -1;

    NodeRing* neighbor;

   public:
    NodeRing(uint32_t id);
    void addNeighbor(NodeRing* node) override;
    void startElection();
    void receiveElectionMsg(uint32_t id);
    void receiveElectionConfirmation(uint32_t id);
    void finishElection();
};