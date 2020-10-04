#include "SimulateBully.hpp"

#include <cstdio>
#include <vector>

#include "NodeBully.hpp"

void SimulateBully::run() {
    printf("Starting Bully election simulation\n");
    std::vector<NodeBully*> nodes;

    for (size_t i = 0; i < SimulateBully::N; i++) {
        NodeBully* next = new NodeBully(i);
        nodes.push_back(next);
    }
    for (auto& node : nodes) {
        for (auto& otherNode : nodes) {
            // if (node->getId() == otherNode->getId()) continue;
            node->addNeighbor(otherNode);
        }
    }
    nodes[SimulateBully::N - 1]->fail();

    nodes[0]->startElection();

    for (auto& node : nodes) {
        delete node;
    }
}