//
// Created by leoleil on 2020/12/23.
//

#ifndef WEAVER_WNODE_H
#define WEAVER_WNODE_H
#include <string>
#include <utility>
using namespace std;
class WNode {
public:
	virtual void setId(string id) = 0;
	virtual string id() const = 0;
	virtual void setName(string name) = 0;
	virtual string name() const = 0;
	virtual double x() const = 0;
	virtual double y() const = 0;
	virtual void move(double x, double y) = 0;
	virtual void setCapacity(double capacity) = 0;
	virtual double capacity() const = 0;
	virtual void setPortNumber(size_t portNumber) = 0;
	virtual size_t portNumber() const = 0;
	virtual void show() const = 0; // 显示方法
};



#endif //WEAVER_WNODE_H
