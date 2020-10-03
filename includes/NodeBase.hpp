#pragma once

#include <cstdint>
#include <vector>

template <typename NodeType>
class NodeBase {
   protected:
    uint32_t id;

    uint32_t leader = -1;

   public:
    virtual void addNeighbor(NodeType* node) = 0;
    virtual void startElection() = 0;
};