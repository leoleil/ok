//
// Created by leoleil on 2020/12/23.
//

#ifndef WEAVER_WLINK_H
#define WEAVER_WLINK_H
#include <string>
#include "WNode.h"
using namespace std;
template <class T>
class WLink {
public:
	virtual void connect(WNode* fromNode, WNode* toNode) = 0;
	virtual WNode* fromPtr() = 0;
	virtual WNode* toPtr() = 0;
	virtual void show() = 0;
	virtual void setLength(double length) = 0;
	virtual double length() const = 0;
	virtual double weight() const = 0;
	virtual void setSize(size_t size) = 0;
	virtual size_t size() const = 0;
	virtual string id() const = 0;
	virtual string name() const = 0;
	virtual T& at(size_t i) = 0;
};


#endif //WEAVER_WLINK_H
