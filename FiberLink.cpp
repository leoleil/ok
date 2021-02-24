//
// Created by leoleil on 2020/12/27.
//

#include "FiberLink.h"
#include <utility>
#include <iostream>

FiberLink::FiberLink(string id, string name, double length, int size) : mId(std::move(id)), mName(std::move(name)), mLength(length), mSize(size) {
	for (int i = 0; i < mSize; i++) {
		mFibers.push_back(Fiber().setLength(mLength));
	}
}

FiberLink::FiberLink(double length, int size) : mLength(length), mSize(size) {
	for (int i = 0; i < mSize; i++) {
		Fiber f;
		f.setLength(mLength);
		f.setCoreSize(1);
		mFibers.push_back(f);
	}
}

FiberLink::FiberLink(const FiberLink & link) {
	mFromNodePtr = link.mFromNodePtr;
	mToNodePtr = link.mToNodePtr;
	mName = link.mName;
	mId = link.mId;
	mLength = link.mLength;
	mSize = link.mSize;
	for (auto f : link.mFibers) {
		mFibers.push_back(f);
	}
}

void FiberLink::connect(WNode *fromNode, WNode *toNode) {
	mFromNodePtr = fromNode;
	mToNodePtr = toNode;
}

WNode *FiberLink::fromPtr() {
	return mFromNodePtr;
}

WNode *FiberLink::toPtr() {
	return mToNodePtr;
}

void FiberLink::setLength(double length) {
	mLength = length;
	for (auto & mFiber : mFibers) {
		mFiber.setLength(length);
	}
}

double FiberLink::length() const {
	return mLength;
}

double FiberLink::weight() const {
	return mLength;
}

void FiberLink::setSize(size_t size) {
	mSize = size;
	mFibers.clear();
	for (int i = 0; i < mSize; i++) {
		mFibers.push_back(Fiber().setLength(mLength));
	}
}

size_t FiberLink::size() const {
	return mSize;
}

void FiberLink::setId(string id)
{
	mId = std::move(id);
}

string FiberLink::id() const {
	return mId;
}

void FiberLink::setName(string name)
{
	mName = std::move(name);
}

string FiberLink::name() const {
	return mName;
}

Fiber &FiberLink::at(size_t i) {
	return mFibers.at(i);
}

void FiberLink::show() {
	cout << "FIBER LINK:" << mName << " LENGTH:" << mLength << " SIZE:" << mSize;
	if (mFromNodePtr != nullptr && mToNodePtr != nullptr) {
		cout << " CONNECT:<" << mFromNodePtr->name() << "," << mToNodePtr->name() << ">" << endl;
	}
	else {
		cout << " NO CONNECT!" << endl;
	}
}

void FiberLink::serialize(ofstream & ofs) const {
	ofs << mName.size() << endl;
	ofs << mName.c_str() << endl;
	ofs << mId.size() << endl;
	ofs << mId.c_str() << endl;
	ofs << mLength << endl;
	ofs << mSize << endl;
	ofs << mFibers.size() << endl;
	for (auto& f : mFibers) {
		f.serialize(ofs);
	}
}

void FiberLink::deserialize(ifstream & ifs) {
	char* buf = new char[1024];
	size_t size = 0;
	ifs >> size;
	ifs >> buf;
	mName = buf;
	ifs >> size;
	ifs >> buf;
	mId = buf;
	ifs >> mLength;
	ifs >> mSize;
	ifs >> size;
	mFibers.clear();
	for (size_t i = 0; i < size; i++) {
		Fiber f;
		f.deserialize(ifs);
		mFibers.push_back(f);
	}
	delete[] buf;
}

Fiber & FiberLink::operator[](const unsigned int index) {
	return mFibers[index];
}
