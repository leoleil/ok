//
// Created by leoleil on 2020/12/24.
//

#ifndef WEAVER_PHYSICALNODE_H
#define WEAVER_PHYSICALNODE_H
#include <vector>
#include <fstream>
#include "WNode.h"
using namespace std;
// 端口
class WPort {
public:
	WPort() = default;
	explicit WPort(double capacity);
	void setCapacity(double capacity);
	double capacity() const;
	void occupy();
	void release();
	bool enable() const;
private:
	double mCapacity = 0;// 端口容量
	bool mEnable = true;//端口是否占用
};
class PhysicalNode : public WNode {
public:
	PhysicalNode() = default;
	PhysicalNode(string id, string name);
	PhysicalNode(string id, string name, double x, double y);
	~PhysicalNode();
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
	void extension(int size);// 扩容
	vector<WPort*> ports();// 获取端口情况
	void serialize(ofstream & ofs) const; // 序列化
	void deserialize(ifstream & ifs);// 反序列化
private:
	string mId; // 节点ID
	string mName; // 节点名称
	double mX = 0; // 节点经度
	double mY = 0;// 节点纬度
	double mCapacity = 0;// 节点容量
	size_t mPortNumber = 0;// 端口数量
	size_t mPortSize = 0;
	vector<WPort*> mPorts;
};


#endif //WEAVER_PHYSICALNODE_H
