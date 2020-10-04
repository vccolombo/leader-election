#pragma once

#include <cstdint>

template <typename NodeType>
class NodeBase {
   protected:
    uint32_t id;
    uint32_t leader = -1;
    bool failed = false;

    virtual void finishElection() = 0;

   public:
    enum class MessageType { ELECTION, ELECTED };
    virtual void addNeighbor(NodeType* node) = 0;
    virtual void startElection() = 0;
    virtual bool receiveMsg(uint32_t id, MessageType msgType) = 0;

    void fail() { this->failed = true; }
};