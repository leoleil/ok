#include "WTraffic.h"



WTraffic::WTraffic() {
}

WTraffic::WTraffic(const WTraffic & w) {
	mFrom = w.mFrom;
	mTo = w.mTo;
	mStatus = w.mStatus;
	mRate = w.mRate;
	mKeepTime = w.mKeepTime;// 保持时间 毫秒
	mStartTime = w.mStartTime;// 开始时间
	mModel = w.mModel;// 模式编号
	mGrid = w.mGrid;// 栅格编号
	for (WaveLength* w : w.mWavelengths) {
		mWavelengths.push_back(w);
	}
}


WTraffic::~WTraffic() {
}

void WTraffic::setRate(double rate) {
	mRate = rate;
}

size_t WTraffic::from()const {
	return mFrom;
}

size_t WTraffic::to()const {
	return mTo;
}

void WTraffic::setFromAndTo(size_t from, size_t to) {
	mFrom = from;
	mTo = to;
}

size_t WTraffic::keepTime()const {
	return mKeepTime;
}

void WTraffic::setKeepTime(size_t millisecond) {
	mKeepTime = millisecond;
}

double WTraffic::rate() const {
	return mRate;
}

bool WTraffic::ready() {
	if (mStatus != NEW && mStatus != BLOCK) {
		return false;
	}
	for (WaveLength* w : mWavelengths) {
		if (!w->canOccupy(mModel, mGrid, mRate)) {
			mStatus = BLOCK;
			return false;
		}
	}
	mStatus = READY;
	return true;
}

bool WTraffic::isReady()const {
	return (mStatus == READY);
}

bool WTraffic::start() {
	if (mStatus != READY) {
		return false;
	}
	for (WaveLength* w : mWavelengths) {
		w->occupyRes(mModel, mGrid, mRate);
	}
	mStartTime = chrono::steady_clock::now();// 开始计时
	mStatus = START;
	return true;
}

bool WTraffic::isStart()const {
	return (mStatus == START);
}

bool WTraffic::block() {
	if (mStatus != NEW) {
		return false;
	}
	mStatus = BLOCK;
	return true;
}

bool WTraffic::isBlock()const {
	return (mStatus == BLOCK);
}

bool WTraffic::finish() {
	milliseconds timeInterval = std::chrono::duration_cast<milliseconds>(chrono::steady_clock::now() - mStartTime);// 获取时间
	if (mStatus == START && timeInterval.count() > mKeepTime) {
		for (WaveLength* w : mWavelengths) {
			w->releaseRes(mModel, mGrid);
		}
		mStatus == FINISH;
		return true;
	}
	return false;
}

bool WTraffic::isFinish()const {
	return (mStatus == FINISH);
}

void WTraffic::setWavelengths(vector<WaveLength*> wavelengths) {
	mWavelengths = wavelengths;
}

WTraffic WTraffic::setWavelength(WaveLength & wavelength) {
	mWavelengths.push_back(&wavelength);
	return *this;
}

void WTraffic::setModel(size_t model) {
	mModel = model;
}

void WTraffic::setGrid(size_t grid) {
	mGrid = grid;
}
