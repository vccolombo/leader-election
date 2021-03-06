#pragma once

#include "NodeBase.hpp"

class NodeRing : protected NodeBase<NodeRing> {
   private:
    uint32_t election = -1;
    NodeRing* neighbor;

    void receiveElectionMsg(uint32_t id);
    void receiveElectedMsg(uint32_t id);
    void finishElection() override;

   public:
    NodeRing(uint32_t id);
    void addNeighbor(NodeRing* node) override;
    void startElection() override;
    bool receiveMsg(uint32_t id, MessageType msgType) override;
};