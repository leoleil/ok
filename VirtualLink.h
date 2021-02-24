#ifndef WEAVER_VIRTUALLINK_H
#define WEAVER_VIRTUALLINK_H
#include <string>
#include <vector>
#include "FiberLink.h"
using namespace std;


// 虚拟映射
class VirtualMap {
public:
	size_t link;// 链路编号
	size_t fiber;// 光纤编号
	size_t core;// 纤芯编号
	size_t waverlength;// 波长编号
};
// 虚拟链路
class VirtualLink : public WLink<WaveLength> {
public:
	VirtualLink();
	~VirtualLink();
	void connect(WNode* fromNode, WNode* toNode) override;
	WNode* fromPtr() override;
	WNode* toPtr() override;
	void setLength(double length) override;
	double length() const override;
	double weight() const override;
	void setSize(size_t size) override;
	size_t size() const override;
	void setId(string id);
	string id() const override;
	void setName(string name);
	string name() const override;
	WaveLength& at(size_t i) override;
	void show() override;
	void setVirtualMap(VirtualMap virtualMap);
	void setVirtualMap(vector<VirtualMap> virtualMaps);
	void setWavelength(const WaveLength &w);
	vector<VirtualMap> virtualMaps();
private:
	string mName;// 链路名称
	string mId;// 链路Id
	double mRate;// 速率GHz
	double bandwith;// 链路带宽Gbps
	double mLength;// 链路长度Km
	WaveLength mWavelength;// 链路波长
	WNode * mFromNodePtr = nullptr;// 起点
	WNode * mToNodePtr = nullptr;// 终点
	vector<VirtualMap> mVirtualMaps;// 映射的资源
};
#endif //WEAVER_VIRTUALLINK_H
