#include "NodeRing.hpp"

#include <algorithm>
#include <cstdint>
#include <cstdio>

NodeRing::NodeRing(uint32_t id) { this->id = id; }

void NodeRing::addNeighbor(NodeRing* node) { this->neighbor = node; }

void NodeRing::startElection() {
    this->election = this->id;
    this->neighbor->receiveMsg(this->election, MessageType::ELECTION);
}

bool NodeRing::receiveMsg(uint32_t id, MessageType msgType) {
    if (this->failed) return false;

    if (msgType == MessageType::ELECTION) {
        this->receiveElectionMsg(id);
    } else if (msgType == MessageType::ELECTED) {
        this->receiveElectedMsg(id);
    }

    return true;
}

void NodeRing::receiveElectionMsg(uint32_t id) {
    // printf("I am %d and they want me to elect %d\n", this->id, id);

    if (id == this->id) {
        // Current node notices that it has been elected
        // and send a notification to the ring
        this->neighbor->receiveMsg(id, MessageType::ELECTED);
        return;
    }

    this->election = std::max(id, this->id);
    this->neighbor->receiveMsg(this->election, MessageType::ELECTION);
}

void NodeRing::receiveElectedMsg(uint32_t id) {
    this->finishElection();
    if (id != this->id) {
        this->neighbor->receiveMsg(id, MessageType::ELECTED);
    }
}

void NodeRing::finishElection() {
    this->leader = this->election;

    if (this->id == this->leader) {
        printf("I am %d and I am the new leader\n", this->id);
    } else {
        // printf("I am %d and my new leader is %d\n", this->id, this->leader);
    }
}