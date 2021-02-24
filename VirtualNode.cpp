//
// Created by leoleil on 2020/12/24.
//
#include <iostream>
#include <utility>
#include "VirtualNode.h"

void VirtualNode::show() const {
	cout << "VIRTUAL NODE:" << mName << " MAP TO<" << mMapNodePtr->name() << ">" << endl;
}

void VirtualNode::mapTo(WNode *node) {
	mMapNodePtr = node;
}

WNode * VirtualNode::mapNode() const {
	return mMapNodePtr;
}

VirtualNode::VirtualNode() {

}

VirtualNode::VirtualNode(WNode * node) {
	mName = node->name();
	mId = "V_Node";
	mMapNodePtr = node;
	mX = node->x();// 节点经度
	mY = node->y();// 节点纬度
	mCapacity = node->capacity();// 节点容量
	mPortNumber = node->portNumber();// 端口数量
}

VirtualNode::VirtualNode(const VirtualNode & node) {
	mId = node.mName; // 节点ID
	mName = node.mName; // 节点名称
	mX = node.mX; // 节点经度
	mY = node.mY;// 节点纬度
	mCapacity = node.mCapacity;// 节点容量
	mPortNumber = node.mPortNumber;// 端口数量
	mMapNodePtr = node.mMapNodePtr; // 映射节点
}
void VirtualNode::setId(string id)
{
	mId = std::move(id);
}

string VirtualNode::id() const {
	return mId;
}

void VirtualNode::setName(string name) {
	mName = std::move(name);
}

string VirtualNode::name() const {
	return mName;
}

double VirtualNode::x() const {
	return mX;
}

double VirtualNode::y() const {
	return mY;
}

void VirtualNode::move(double x, double y) {
	mX = x;
	mY = y;
}

void VirtualNode::setCapacity(double capacity) {
	mCapacity = capacity;
}

double VirtualNode::capacity() const {
	return mCapacity;
}

void VirtualNode::setPortNumber(size_t portNumber) {
	mPortNumber = portNumber;
}

size_t VirtualNode::portNumber() const {
	return mPortNumber;
}
