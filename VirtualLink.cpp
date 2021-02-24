#include "VirtualLink.h"


VirtualLink::VirtualLink() {
}


VirtualLink::~VirtualLink() {
}

void VirtualLink::connect(WNode * fromNode, WNode * toNode) {
	mFromNodePtr = fromNode;
	mToNodePtr = toNode;
}

WNode * VirtualLink::fromPtr() {
	return mFromNodePtr;
}

WNode * VirtualLink::toPtr() {
	return mToNodePtr;
}

void VirtualLink::setLength(double length) {
	mLength = length;
}

double VirtualLink::length() const
{
	return mLength;
}

double VirtualLink::weight() const {
	return mLength;
}

void VirtualLink::setSize(size_t size) {
}

size_t VirtualLink::size() const {
	return 1;
}

void VirtualLink::setId(string id) {
	mId = id;
}

string VirtualLink::id() const {
	return mId;
}

void VirtualLink::setName(string name) {
	mName = name;
}

string VirtualLink::name() const
{
	return mName;
}

WaveLength & VirtualLink::at(size_t i) {
	return mWavelength;
}

void VirtualLink::show() {
}

void VirtualLink::setVirtualMap(VirtualMap virtualMap) {
	mVirtualMaps.clear();
	mVirtualMaps.push_back(virtualMap);
}

void VirtualLink::setVirtualMap(vector<VirtualMap> virtualMaps) {
	mVirtualMaps = virtualMaps;
}

void VirtualLink::setWavelength(const WaveLength &w) {
	mWavelength = w;
	mRate = w.rate();
}

vector<VirtualMap> VirtualLink::virtualMaps() {
	return mVirtualMaps;
}
