//
// Created by leoleil on 2020/12/27.
//

#include "Weaver.h"

#include <utility>
#include <istream>
PhysicalNode *Weaver::addNode() {
    auto* pItem = new PhysicalNode();
    mPhysicalNodes.push_back(pItem);
    return pItem;
}

PhysicalNode *Weaver::addNode(string name, string id, double x, double y) {
    auto* pItem = new PhysicalNode(std::move(id), std::move(name), x, y);
    mPhysicalNodes.push_back(pItem);
    return pItem;
}

FiberLink *Weaver::addLink() {
    auto* pItem = new FiberLink();
    mFiberLinks.push_back(pItem);
    return pItem;
}

FiberLink *Weaver::addLink(string name, string id, double length, size_t size) {
    auto* pItem = new FiberLink(std::move(id), std::move(name), length, size);
    mFiberLinks.push_back(pItem);
    return pItem;
}

FiberLink * Weaver::addLink(string name, string id, double length, size_t size, size_t from, size_t to) {
    auto* pItem = new FiberLink(std::move(id), std::move(name), length, size);
    pItem->connect(mPhysicalNodes.at(from), mPhysicalNodes.at(to));
    mFiberLinks.push_back(pItem);
    return pItem;
}

void Weaver::deleteNode(int i) {
    delete mPhysicalNodes.at(i);
    mPhysicalNodes.erase(mPhysicalNodes.begin() + i);
}

void Weaver::deleteLink(int i) {
    delete mFiberLinks.at(i);
    mFiberLinks.erase(mFiberLinks.cbegin() + i);
}

void Weaver::connect(size_t node1, size_t node2, size_t link) {
    mFiberLinks[link]->connect(mPhysicalNodes[node1], mPhysicalNodes[node2]);
}

PhysicalNode & Weaver::getNode(size_t i) const {
    return *mPhysicalNodes.at(i);
}

FiberLink & Weaver::getLink(size_t i) const {
    return *mFiberLinks.at(i);
}

size_t Weaver::nodeSize() const {
    return mPhysicalNodes.size();
}

size_t Weaver::linkSize() const {
    return mFiberLinks.size();
}

void Weaver::virtualMap() {
    // 创建虚拟节点
    for (auto* iPtr : mPhysicalNodes) {
        auto* vNode = new VirtualNode(iPtr);
        mVirtualNodes.push_back(vNode);
    }
    // 构建虚拟链路
    for (size_t i = 0; i < mFiberLinks.size(); i++) {
        fiberLinkToVirtualLink(*mFiberLinks[i], i);
    }
    // 构建虚拟切片
    for (size_t i = 0; i < mVirtualLinks.size(); i++) {
        virtualLinkToGraphs(*mVirtualLinks[i]);
    }
}

vector<WGraph*>& Weaver::virtualSlices() {
    return mGraphSlice;
}

vector<VirtualNode*>& Weaver::virtualNodes() {
    return mVirtualNodes;
}

vector<VirtualLink *> &Weaver::virtualLinks() {
    return mVirtualLinks;
}

void Weaver::serialize(ofstream & ofs) const {
    size_t size = mPhysicalNodes.size();
    ofs << size << endl;
    for (auto* ptr : mPhysicalNodes) {
        ptr->serialize(ofs);
    }
    size = mFiberLinks.size();
    ofs << size << endl;
    for (size_t i = 0; i < mFiberLinks.size(); i++) {
        mFiberLinks[i]->serialize(ofs);
        bool haveNode = true;// 判断有无节点连接
        if (mFiberLinks[i]->fromPtr() == nullptr || mFiberLinks[i]->toPtr() == nullptr) {
            haveNode = false;
        }
        if (haveNode) {
            size_t from = 0;
            size_t to = 0;
            size_t find = 0;
            for (size_t j = 0; j < mPhysicalNodes.size() && find < 2; j++) {
                if (mPhysicalNodes[j] == mFiberLinks[i]->fromPtr()) {
                    from = j;
                    find++;
                }
                if (mPhysicalNodes[j] == mFiberLinks[i]->toPtr()) {
                    to = j;
                    find++;
                }
            }
            ofs << haveNode << endl;
            ofs << from << endl;
            ofs << to << endl;
        }
        else {
            ofs << haveNode << endl;
        }

    }

}

void Weaver::deserialize(ifstream & ifs) {
    size_t size = 0;
    ifs >> size;
    for (size_t i = 0; i < size; i++) {
        PhysicalNode* nPtr = new PhysicalNode();
        nPtr->deserialize(ifs);
        mPhysicalNodes.push_back(nPtr);
    }
    ifs >> size;
    for (size_t i = 0; i < size; i++) {
        FiberLink* lPtr = new FiberLink();
        lPtr->deserialize(ifs);
        bool haveNode = true;
        ifs >> haveNode;
        if (haveNode) {
            size_t from;
            size_t to;
            ifs >> from >> to;
            lPtr->connect(mPhysicalNodes.at(from), mPhysicalNodes.at(to));
        }
        mFiberLinks.push_back(lPtr);
    }
}

double Weaver::resource() const {
    double res = 0;
    for (auto* link : mVirtualLinks) {
        res += link->at(0).rate();
    }
    return res;
}

void Weaver::fiberLinkToVirtualLink(FiberLink & link, size_t index) {
    for (size_t i = 0; i < link.size(); i++) {
        fiberToVirtualLink(link[i], index, i);
    }
}

void Weaver::fiberToVirtualLink(Fiber & fiber, const size_t linkId, const size_t fiberId) {
    for (size_t i = 0; i < fiber.coreSize(); i++) {
        fiberCoreToVirtualLink(fiber[i], linkId, fiberId, i);
    }
}

void Weaver::fiberCoreToVirtualLink(Core & core, const size_t linkId, const size_t fiberId, const size_t coreId) {
    for (size_t i = 0; i < core.wavelengths.size(); i++) {
        auto* vLink = new VirtualLink();
        vLink->setId(mFiberLinks.at(linkId)->id());
        vLink->setName(mFiberLinks.at(linkId)->name());
        vLink->setLength(mFiberLinks.at(linkId)->length());
        vLink->setWavelength(core.wavelengths.at(i));
        //找寻节点
        auto* fromPtr = mFiberLinks.at(linkId)->fromPtr();
        auto* toPtr = mFiberLinks.at(linkId)->toPtr();
        WNode* vFromPtr = nullptr;
        WNode* vToPtr = nullptr;
        for (auto* nodePtr : mVirtualNodes) {
            if (nodePtr->mapNode() == fromPtr) {
                vFromPtr = nodePtr;
            }
            if (nodePtr->mapNode() == toPtr) {
                vToPtr = nodePtr;
            }
        }
        VirtualMap vMap;
        vMap.link = linkId;
        vMap.fiber = fiberId;
        vMap.core = coreId;
        vMap.waverlength = i;
        vLink->setVirtualMap(vMap);
        vLink->connect(vFromPtr, vToPtr);
        mVirtualLinks.push_back(vLink);
    }
}

void Weaver::virtualLinkToGraphs(VirtualLink & link) {
    for (WGraph* g : mGraphSlice) {
        if (g->waveLength == link.at(0).length() && g->size == link.at(0).size()) {
            graphAddLink(*g, link);
            return;
        }
    }
    WGraph* g = new WGraph();
    g->waveLength = link.at(0).length();
    g->size = link.at(0).size();
    g->links.push_back(&link);
    g->nodeSet.insert(link.fromPtr());
    g->nodeSet.insert(link.toPtr());
    mGraphSlice.push_back(g);
}

void Weaver::graphAddLink(WGraph & graph, VirtualLink & link) {
    graph.links.push_back(&link);
    graph.nodeSet.insert(link.fromPtr());
    graph.nodeSet.insert(link.toPtr());
}

vector<PhysicalNode *> Weaver::physicalNodes() {
    return mPhysicalNodes;
}

vector<FiberLink *> Weaver::fiberLinks() {
    return mFiberLinks;
}

void Weaver::show() {
    for (auto item : mPhysicalNodes) {
        item->show();
    }
    for (auto item : mFiberLinks) {
        item->show();
    }
}

Weaver::~Weaver() {
    for (auto item : mPhysicalNodes) {
        delete item;
    }
    for (auto item : mFiberLinks) {
        delete item;
    }
    for (auto item : mVirtualNodes) {
        delete item;
    }
    for (auto item : mVirtualLinks) {
        delete item;
    }
    for (auto item : mGraphSlice) {
        delete item;
    }
}
