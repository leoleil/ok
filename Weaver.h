//
// Created by leoleil on 2020/12/27.
//

#ifndef WEAVER_WEAVER_H
#define WEAVER_WEAVER_H
#include <vector>
#include <set>
#include "FiberLink.h"
#include "PhysicalNode.h"
#include "VirtualLink.h"
#include "VirtualNode.h"
using namespace std;

class WGraph {
public:
	// 波长 子粒度 速率 一致则分为同一个图分区
	int size;// 波长可分的粒度
	double waveLength;// 波长
	set<WNode*> nodeSet;// 标记存在节点
	vector<VirtualLink*> links;// 链路数组
};
class Weaver {
public:
	Weaver() = default;
	~Weaver();
	vector<PhysicalNode*> physicalNodes();
	vector<FiberLink*> fiberLinks();
	void show();
	PhysicalNode* addNode();
	PhysicalNode* addNode(string name, string id, double x, double y);
	FiberLink* addLink();
	FiberLink* addLink(string name, string id, double length, size_t size);
	FiberLink* addLink(string name, string id, double length, size_t size, size_t from, size_t to);
	void deleteNode(int i);
	void deleteLink(int i);
	void connect(size_t node1, size_t node2, size_t link);
	PhysicalNode& getNode(size_t i)const;
	FiberLink& getLink(size_t i)const;
	size_t nodeSize()const;
	size_t linkSize()const;
	void virtualMap();// 虚拟化
	vector<WGraph*>& virtualSlices();// 获取虚拟化切片
	vector<VirtualNode*>& virtualNodes();// 获取虚拟节点
    vector<VirtualLink*>& virtualLinks();// 获取虚拟节点
	void serialize(ofstream & ofs) const; // 序列化
	void deserialize(ifstream & ifs);// 反序列化
	double resource() const;// 获取网络资源数目
private:
	vector<PhysicalNode*> mPhysicalNodes;// 物理节点
	vector<FiberLink*> mFiberLinks;// 物理链路
	vector<VirtualNode*> mVirtualNodes;// 虚拟节点
	vector<VirtualLink*> mVirtualLinks;// 虚拟链路
	vector<WGraph*> mGraphSlice;// 虚拟的图切片
private:
	// 虚拟化算法
	void fiberLinkToVirtualLink(FiberLink &link, size_t index);
	void fiberToVirtualLink(Fiber &fiber, const size_t linkId, const size_t fiberId);
	void fiberCoreToVirtualLink(Core &core, const size_t linkId, const size_t fiberId, const size_t coreId);
	void virtualLinkToGraphs(VirtualLink& link);
	void graphAddLink(WGraph& graph, VirtualLink& link);
};


#endif //WEAVER_WEAVER_H
