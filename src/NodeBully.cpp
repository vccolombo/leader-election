#include "NodeBully.hpp"

#include <cstdint>
#include <cstdio>

NodeBully::NodeBully(uint32_t id) { this->id = id; }

void NodeBully::addNeighbor(NodeBully* node) {
    this->neighbors.push_back(node);
}

void NodeBully::startElection() { this->sendElectionMsgToAll(); }

bool NodeBully::receiveMsg(uint32_t id, MessageType msgType) {
    if (this->failed) return false;

    if (msgType == MessageType::ELECTION) {
        this->sendElectionMsgToAll();
    } else if (msgType == MessageType::ELECTED) {
        this->leader = id;
        this->finishElection();
    }

    return true;
}

void NodeBully::sendElectionMsgToAll() {
    for (const auto neighbor : this->neighbors) {
        if (bullied) return;
        if (neighbor->id > this->id) {
            this->sendElectionMsg(neighbor);
        }
    }
}

void NodeBully::sendElectionMsg(NodeBully* neighbor) {
    bool response = neighbor->receiveMsg(this->id, MessageType::ELECTION);
    if (!response) {
        // Timeout, so this is the new leader
        // Notice this is only working if only the previous leader failed
        // So if other nodes fail the current node might wrongly think that it
        // is the new leader

        sendElectedMsgs();
    } else {
        this->bullied = true;
    }
}

void NodeBully::sendElectedMsgs() {
    for (const auto neighbor : this->neighbors) {
        neighbor->receiveMsg(this->id, MessageType::ELECTED);
    }
}

void NodeBully::finishElection() {
    this->bullied = false;

    if (this->id == this->leader) {
        printf("I am %d and I am the new leader\n", this->id);
    } else {
        // printf("I am %d and my new leader is %d\n", this->id, this->leader);
    }
}