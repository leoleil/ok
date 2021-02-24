//
// Created by leoleil on 2020/12/24.
//

#include "PhysicalNode.h"
#include <iostream>
#include <utility>

void PhysicalNode::show() const {
	cout << "NODE:" << name() << "<lat:" << x() << ",lon:" << y() << ">" << endl;
}


PhysicalNode::~PhysicalNode() {
	for (auto item : mPorts) {
		delete item;
	}
}

void PhysicalNode::setId(string id) {
	mId = std::move(id);
}

string PhysicalNode::id() const {
	return mId;
}

void PhysicalNode::setName(string name) {
	mName = std::move(name);
}

string PhysicalNode::name() const {
	return mName;
}

double PhysicalNode::x() const {
	return mX;;
}

double PhysicalNode::y() const
{
	return mY;
}

void PhysicalNode::move(double x, double y) {
	mX = x;
	mY = y;
}

void PhysicalNode::setCapacity(double capacity) {
	mCapacity = capacity;
}

double PhysicalNode::capacity() const {
	return mCapacity;
}

void PhysicalNode::setPortNumber(size_t portNumber) {
	mPortNumber = portNumber;
}

size_t PhysicalNode::portNumber() const {
	return mPortNumber;
}

void PhysicalNode::extension(int size) {
	if (size > mPortSize) {
		for (int i = mPortSize; i < size; i++) {
			auto* port = new WPort();
			mPorts.push_back(port);
		}
		mPortSize = size;
	}
}

vector<WPort *> PhysicalNode::ports() {
	return mPorts;
}
// 节点的序列化
// 目前不序列化端口
void PhysicalNode::serialize(ofstream & ofs) const {
	vector<WPort*> mPorts;
	size_t size = 0;// 计算对象大小
	size += mId.length() + sizeof(size_t);
	size += mName.length() + sizeof(size_t);
	size += sizeof(double) * 2;
	size += sizeof(size_t) * 2;
	ofs << size << endl;
	ofs << mId.length() << endl;
	ofs << mId.c_str() << endl;
	ofs << mName.length() << endl;
	ofs << mName.c_str() << endl;
	ofs << mX << endl;
	ofs << mY << endl;
	ofs << mCapacity << endl;
	ofs << mPortNumber << endl;
}

void PhysicalNode::deserialize(ifstream & ifs) {
	size_t size = 0;
	ifs >> size;
	char* buf = new char[size];
	ifs >> size;
	ifs >> buf;
	mId = buf;
	ifs >> size;
	ifs >> buf;
	mName = buf;
	ifs >> mX >> mY >> mCapacity >> mPortNumber;
	delete[] buf;
}

PhysicalNode::PhysicalNode(string id, string name, double x, double y) : mId(std::move(id)), mName(std::move(name)), mX(x), mY(y) {

}

PhysicalNode::PhysicalNode(string id, string name) : mId(std::move(id)), mName(std::move(name)) {

}

WPort::WPort(double capacity) {
	mCapacity = capacity;
}

void WPort::setCapacity(double capacity) {
	mCapacity = capacity;
}

double WPort::capacity() const {
	return mCapacity;
}

void WPort::occupy() {
	mEnable = false;
}

void WPort::release() {
	mEnable = true;
}

bool WPort::enable() const {
	return mEnable;
}
