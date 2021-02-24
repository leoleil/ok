//
// Created by leoleil on 2020/12/24.
//

#include "Fiber.h"
#include <iostream>

WaveLength::WaveLength() {
    mLength = 1530;// 中心波长 默认1530 nm
    mModeSize = 1;// 模式数量
    mSize = 1;// 频隙数量
    mRate = 100;// 速率默认100GHz
    mBandwidth = 0;// 带宽100Gbps
    mGrids = new bool*[mModeSize];
    for (int i = 0; i < mModeSize; i++) {
        mGrids[i] = new bool[mSize];
        for (int j = 0; j < mSize; j++) {
            mGrids[i][j] = false;
        }
    }
}

WaveLength::WaveLength(double length, int modelSize, int size, double rate) : mLength(length), mModeSize(modelSize), mSize(size), mRate(rate) {
    mGrids = new bool*[mModeSize];
    for (int i = 0; i < mModeSize; i++) {
        mGrids[i] = new bool[mSize];
        for (int j = 0; j < mSize; j++) {
            mGrids[i][j] = false;
        }
    }
}

WaveLength::WaveLength(const WaveLength & w) {
    mLength = w.mLength;// 波长
    mModeSize = w.mModeSize;// 模式数量
    mSize = w.mSize;// 栅格数量
    mRate = w.mRate;// 速率
    mBandwidth = w.mBandwidth;// 带宽
    mOccupyList = w.mOccupyList; // 栅格资源占用指示
    mGrids = new bool*[mModeSize];// 栅格矩阵
    for (int i = 0; i < mModeSize; i++) {
        mGrids[i] = new bool[mSize];
        for (int j = 0; j < mSize; j++) {
            mGrids[i][j] = w.mGrids[i][j];
        }
    }
}

WaveLength::~WaveLength() {
    for (int i = 0; i < mModeSize; i++) {
        delete[] mGrids[i];
    }
    delete[] mGrids;
}

WaveLength &WaveLength::setLength(double length) {
    mLength = length;
    return *this;
}

double WaveLength::length() const {
    return mLength;
}

WaveLength &WaveLength::setModeSize(int size) {
    if (size == 0) {
        return *this;
    }
    for (int i = 0; i < mModeSize; i++) {
        delete[] mGrids[i];
    }
    delete[] mGrids;
    mModeSize = size;
    mGrids = new bool*[mModeSize];
    for (int i = 0; i < mModeSize; i++) {
        mGrids[i] = new bool[mSize];
    }
    return *this;
}

int WaveLength::modeSize() const {
    return mModeSize;
}

WaveLength &WaveLength::setSize(int size) {
    if (size == 0) {
        return *this;
    }
    for (int i = 0; i < mModeSize; i++) {
        delete[] mGrids[i];
    }
    delete[] mGrids;
    mSize = size;
    mGrids = new bool*[mModeSize];
    for (int i = 0; i < mModeSize; i++) {
        mGrids[i] = new bool[mSize];
    }
    return *this;
}

int WaveLength::size() const {
    return mSize;
}

WaveLength &WaveLength::setRate(double rate) {
    mRate = rate;
    return *this;
}

double WaveLength::rate() const {
    return mRate;
}

WaveLength &WaveLength::setBandwidth(double bandwidth) {
    mBandwidth = bandwidth;
    return *this;
}

double WaveLength::bandWidth() const {
    return mBandwidth;
}

double WaveLength::grain() const {
    return mRate / mSize;
}

void WaveLength::show() {
    cout << "WAVE LENGTH INFO " << "LENGTH:" << mLength << " MODEL:" << mModeSize << endl;
    for (int i = 0; i < mModeSize; i++) {
        for (int j = 0; j < mSize; j++) {
            cout << mGrids[i][j];
        }
        cout << endl;
    }
}

bool WaveLength::canOccupy(size_t modelId, size_t gridId, double rate) {
    // 资源检查
    if (modelId >= mModeSize) {
        return false;
    }
    if (gridId >= mSize) {
        return false;
    }
    int len = ceil(rate / grain());
    if (gridId + len > mSize) {
        return false;
    }
    // 连续检测
    for (size_t i = 0; i < len; i++) {
        if (mGrids[modelId][gridId + i]) {
            return false;
        }
    }
    return true;
}

bool WaveLength::occupyRes(int modelId, int gridId, double rate) {
    // 资源检查
    if (modelId >= mModeSize || modelId < 0) {
        return false;
    }
    if (gridId >= mSize || gridId < 0) {
        return false;
    }
    int len = ceil(rate / grain());
    if (gridId + len > mSize) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (mGrids[modelId][gridId + i]) {
            return false;
        }
    }
    // 资源占用
    occupy occ;
    occ.x = modelId;
    occ.y = gridId;
    occ.len = len;
    for (int i = 0; i < len; i++) {
        mGrids[modelId][gridId + i] = true;
    }
    mOccupyList.push_back(occ);
    return true;
}

bool WaveLength::releaseRes(int modelId, int gridId) {
    for (auto item = mOccupyList.begin(); item != mOccupyList.end(); item++) {
        if (item->x == modelId && item->y == gridId) {
            for (int i = gridId; i < gridId + item->len; i++) {
                mGrids[modelId][i] = false;// 释放资源
            }
            mOccupyList.erase(item);
            return true;
        }
    }
    return false;
}

bool ** WaveLength::res()
{
    return mGrids;
}

list<occupy> WaveLength::occupyList()
{
    return mOccupyList;
}

void WaveLength::serialize(ofstream & ofs) const {
    ofs << mLength << endl;
    ofs << mModeSize << endl;
    ofs << mSize << endl;
    ofs << mRate << endl;
    ofs << mBandwidth << endl;
    ofs << mSatus << endl;
}

void WaveLength::deserialize(ifstream & ifs) {
    for (int i = 0; i < mModeSize; i++) {
        delete[] mGrids[i];
    }
    delete[] mGrids;
    ifs >> mLength >> mModeSize >> mSize >> mRate >> mBandwidth >> mSatus;
    mGrids = new bool*[mModeSize];
    for (int i = 0; i < mModeSize; i++) {
        mGrids[i] = new bool[mSize];
        for (int j = 0; j < mSize; j++) {
            mGrids[i][j] = false;
        }
    }
}

Fiber::Fiber() {
    for (int i = 0; i < mCoreSize; i++) {
        Core c;
        for (int j = 0; j < mWaverSize; j++) {
            WaveLength w(1525 + j, mModelSize, 1, 100);
            c.wavelengths.push_back(w);
        }
        mCores.push_back(c);
    }
}

Fiber::Fiber(double length, int coreSize, int modelSize, int waverSize) : mLength(length), mCoreSize(coreSize), mModelSize(modelSize), mWaverSize(waverSize) {
    for (int i = 0; i < mCoreSize; i++) {
        Core c;
        for (int j = 0; j < mWaverSize; j++) {
            WaveLength w(1525 + j, mModelSize, 1, mRate);
            c.wavelengths.push_back(w);
        }
        mCores.push_back(c);
    }
}

Fiber::Fiber(const Fiber & fiber) {
    mLength = fiber.mLength;// 长度单位Km
    mCoreSize = fiber.mCoreSize;// 纤芯数
    mModelSize = fiber.mModelSize;// 模式数量
    mWaverSize = fiber.mWaverSize;// 波段数量
    mRate = fiber.mRate;// 速率单位Ghz
    mBandwidth = fiber.mBandwidth;// 带宽Gbps
    for (Core c : fiber.mCores) {
        mCores.push_back(c);
    }
}

Fiber & Fiber::setLength(double length) {
    mLength = length;
    return *this;
}

double Fiber::length() const {
    return mLength;
}

Fiber &Fiber::setCoreSize(size_t size) {
    mCoreSize = size;
    mCores.clear();
    for (int i = 0; i < mCoreSize; i++) {
        Core c;
        for (int j = 0; j < mWaverSize; j++) {
            WaveLength w(1525 + j, mModelSize, mRateSize, mRate);
            c.wavelengths.push_back(w);
        }
        mCores.push_back(c);
    }
    return *this;
}

size_t  Fiber::coreSize() const {
    return mCoreSize;
}

Fiber &Fiber::setModelSize(size_t size) {
    mModelSize = size;
    for (auto & c : mCores) {
        for (auto & w : c.wavelengths) {
            w.setModeSize(size);
        }
    }
    return *this;
}

size_t Fiber::modelSize() const {
    return mModelSize;
}

Fiber &Fiber::setWeaverSize(size_t size) {
    mWaverSize = size;
    mCores.clear();
    for (int i = 0; i < mCoreSize; i++) {
        Core c;
        for (int j = 0; j < mWaverSize; j++) {
            WaveLength w(1525 + j, mModelSize, mRateSize, mRate);
            c.wavelengths.push_back(w);
        }
        mCores.push_back(c);
    }
    return *this;
}

size_t Fiber::weaverSize() const {
    return mWaverSize;
}

Fiber &Fiber::setRate(double rate) {
    mRate = rate;
    for (auto & c : mCores) {
        for (auto & w : c.wavelengths) {
            w.setRate(rate);
        }
    }
    return *this;
}

double Fiber::rate() const {
    return mRate;
}

Fiber &Fiber::setBandwidth(double bandwidth) {
    mBandwidth = bandwidth;
    return *this;
}

double Fiber::bandwidth() const {
    return mBandwidth;
}

Fiber &Fiber::setRateSize(size_t rateSize) {
    mRateSize = rateSize;
    for (auto& c : mCores) {
        for (auto& w : c.wavelengths) {
            w.setSize(mRateSize);
        }
    }
    return *this;
}

size_t Fiber::rateSize() const {
    return mRateSize;
}

Core & Fiber::at(size_t i) {
    return mCores.at(i);
}

void Fiber::show()
{
    cout << "FIBER INFO" << " CORE:" << mCoreSize << " MODEL:" << mModelSize << " WAVE:" << mWaverSize << endl;
}

void Fiber::serialize(ofstream & ofs) const {
    ofs << mLength << endl;
    ofs << mCoreSize << endl;
    ofs << mModelSize << endl;
    ofs << mWaverSize << endl;
    ofs << mRate << endl;
    ofs << mBandwidth << endl;
    ofs << mCores.size() << endl;
    for (auto& c : mCores) {
        c.serialize(ofs);
    }
}

void Fiber::deserialize(ifstream & ifs) {
    ifs >> mLength >> mCoreSize >> mModelSize >> mWaverSize >> mRate >> mBandwidth;
    size_t size;
    ifs >> size;
    mCores.clear();
    for (size_t i = 0; i < size; i++) {
        Core c;
        c.deserialize(ifs);
        mCores.push_back(c);
    }
}

Core & Fiber::operator[](const size_t i) {
    return mCores.at(i);
}

Core::Core(const Core & c) {
    for (auto w : c.wavelengths) {
        wavelengths.push_back(w);
    }
    relateGroup = c.relateGroup;
}

void Core::serialize(ofstream & ofs) const {
    //vector<WaveLength> wavelengths;// 工作波长
    //vector<size_t> relateGroup;// 邻接纤芯
    ofs << wavelengths.size() << endl;
    for (auto& w : wavelengths) {
        w.serialize(ofs);
    }
    ofs << relateGroup.size() << endl;
    for (size_t i : relateGroup) {
        ofs << i << endl;
    }
}

void Core::deserialize(ifstream & ifs) {
    wavelengths.clear();
    size_t size;
    ifs >> size;
    for (size_t i = 0; i < size; i++) {
        WaveLength w;
        w.deserialize(ifs);
        wavelengths.push_back(w);
    }
    relateGroup.clear();
    ifs >> size;
    for (size_t i = 0; i < size; i++) {
        size_t id;
        ifs >> id;
        relateGroup.push_back(id);
    }
}
