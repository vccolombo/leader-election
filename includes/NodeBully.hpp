#pragma once

#include <vector>

#include "NodeBase.hpp"

class NodeBully : public NodeBase<NodeBully> {
   private:
    std::vector<NodeBully*> neighbors;
    bool bullied = false;

    void sendElectionMsgToAll();
    void sendElectionMsg(NodeBully* neighbor);
    void sendElectedMsgs();
    void finishElection() override;

   public:
    NodeBully(uint32_t id);
    void addNeighbor(NodeBully* node) override;
    void startElection() override;
    bool receiveMsg(uint32_t id, MessageType msgType) override;
};