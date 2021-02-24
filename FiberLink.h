//
// Created by leoleil on 2020/12/27.
//

#ifndef WEAVER_FIBERLINK_H
#define WEAVER_FIBERLINK_H
#include <vector>
#include "WLink.h"
#include "Fiber.h"
using namespace std;
class FiberLink : public WLink<Fiber> {
public:
	FiberLink() = default;
	FiberLink(string id, string name, double length, int size);
	FiberLink(double length, int size);
	FiberLink(const FiberLink &link);
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
	Fiber& at(size_t i) override;
	void show() override;
	void serialize(ofstream & ofs) const; // 序列化
	void deserialize(ifstream & ifs);// 反序列化
public:
	Fiber & operator[](const unsigned int index);

private:
	WNode * mFromNodePtr = nullptr;
	WNode* mToNodePtr = nullptr;
	string mName = "link";
	string mId = "link";
	double mLength = 0;
	size_t mSize = 1;
	vector<Fiber> mFibers;
};


#endif //WEAVER_FIBERLINK_H
