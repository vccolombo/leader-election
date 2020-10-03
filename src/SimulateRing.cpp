#include "SimulateRing.hpp"

#include "NodeRing.hpp"

void SimulateRing::run() {
    NodeRing* first = new NodeRing(0);
    NodeRing* previous = first;
    for (size_t i = 1; i < SimulateRing::N; i++) {
        NodeRing* next = new NodeRing(i);
        previous->addNeighbor(next);
        previous = next;
    }
    previous->addNeighbor(first);

    first->startElection();
}