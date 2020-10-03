#include "SimulateRing.hpp"

#include <vector>

#include "NodeRing.hpp"

void SimulateRing::run() {
    std::vector<NodeRing*> nodes;

    NodeRing* first = new NodeRing(0);
    nodes.push_back(first);
    NodeRing* previous = first;
    for (size_t i = 1; i < SimulateRing::N; i++) {
        NodeRing* next = new NodeRing(i);
        nodes.push_back(next);
        previous->addNeighbor(next);
        previous = next;
    }
    previous->addNeighbor(first);

    first->startElection();

    for (auto& node : nodes) {
        delete node;
    }
}