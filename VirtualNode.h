//
// Created by leoleil on 2020/12/24.
//

#ifndef WEAVER_VIRTUALNODE_H
#define WEAVER_VIRTUALNODE_H
#include "WNode.h"
using namespace std;
class VirtualNode : public WNode {
public:
	VirtualNode();
	VirtualNode(WNode* node);
	VirtualNode(const VirtualNode &node);
	void setId(string id) override;
	string id() const override;
	void setName(string name) override;
	string name() const override;
	double x() const override;
	double y() const override;
	void move(double x, double y) override;
	void setCapacity(double capacity) override;
	double capacity() const override;
	void setPortNumber(size_t portNumber) override;
	size_t portNumber() const override;
	void show() const override;
	void mapTo(WNode* node);
	WNode* mapNode() const;
private:
	string mId; // 节点ID
	string mName; // 节点名称
	double mX = 0; // 节点经度
	double mY = 0;// 节点纬度
	double mCapacity = 0;// 节点容量
	size_t mPortNumber = 0;// 端口数量
	WNode* mMapNodePtr = nullptr; // 映射节点
};


#endif //WEAVER_VIRTUALNODE_H
