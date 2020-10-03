#include "NodeRing.hpp"

#include <cstdint>
#include <cstdio>

NodeRing::NodeRing(uint32_t id) { this->id = id; }

void NodeRing::addNeighbor(NodeRing* node) { this->neighbor = node; }

void NodeRing::startElection() {
    this->election = this->id;
    this->neighbor->receiveElectionMsg(this->election);
}

void NodeRing::receiveElectionMsg(uint32_t id) {
    printf("I am %d and they want me to elect %d\n", this->id, id);
    if (id == this->id) {
        this->neighbor->receiveElectionConfirmation(id);
        return;
    }
    this->election = std::max(id, this->id);
    this->neighbor->receiveElectionMsg(this->election);
}

void NodeRing::receiveElectionConfirmation(uint32_t id) {
    this->finishElection();
    if (id != this->id) {
        this->neighbor->receiveElectionConfirmation(id);
    }
}

void NodeRing::finishElection() {
    this->leader = this->election;
    this->election = -1;

    if (this->id == this->leader) {
        printf("I am %d and I am the new leader\n", this->id);
    } else {
        printf("I am %d and my new leader is %d\n", this->id, this->leader);
    }
}