
#ifndef WEAVER_FIBER_H
#define WEAVER_FIBER_H
#include <vector>
#include <list>
#include <set>
#include <fstream>
using namespace std;
typedef struct {
    int x;// 模式编号
    int y;// 栅格编号
    int len;// 栅格数量
} occupy;
// 波长资源
class WaveLength {
public:
    WaveLength();
    WaveLength(double length, int modelSize, int size, double rate);
    WaveLength(const WaveLength& w);
    ~WaveLength();
    WaveLength& setLength(double length);
    double length() const;
    WaveLength& setModeSize(int size);
    int modeSize() const;
    WaveLength& setSize(int size);
    int size() const;
    WaveLength& setRate(double rate);
    double rate() const;
    WaveLength& setBandwidth(double bandwidth);
    double bandWidth() const;
    double grain() const;
    void show();
    bool canOccupy(size_t modelId, size_t gridId, double rate);
    bool occupyRes(int modelId, int gridId, double rate);
    bool releaseRes(int modelId, int gridId);
    bool** res();// 资源
    list<occupy> occupyList();
    void serialize(ofstream & ofs) const; // 序列化
    void deserialize(ifstream & ifs);// 反序列化
private:
    double mLength = 0;// 中心波长单位nm
    int mModeSize = 1;// 模式数量
    int mSize = 1;// 频隙数量
    double mRate = 0;// 速率单位GHz
    double mBandwidth = 0;// 带宽单位Gbps
    bool** mGrids = nullptr; // 频隙矩阵
    list<occupy> mOccupyList; // 栅格资源占用指示
    int mSatus = 0;// 波长状态 -1为隔离 0为空闲 1为工作
};
// 纤芯
class Core {
public:
    Core() = default;
    Core(const Core &c);
    void serialize(ofstream & ofs) const; // 序列化
    void deserialize(ifstream & ifs);// 反序列化
public:
    vector<WaveLength> wavelengths;// 工作波长
    vector<int> relateGroup;// 邻接纤芯
};
// 光纤
class Fiber {
public:
    Fiber();
    Fiber(double length, int coreSize, int modelSize, int waverSize);
    Fiber(const Fiber &fiber);
    Fiber& setLength(double length);
    double length() const;
    Fiber& setCoreSize(size_t size);
    size_t coreSize() const;
    Fiber& setModelSize(size_t size);
    size_t modelSize() const;
    Fiber& setWeaverSize(size_t size);
    size_t weaverSize() const;
    Fiber& setRate(double rate);
    double rate() const;
    Fiber& setBandwidth(double bandwidth);
    double bandwidth() const;
    Fiber& setRateSize(size_t rateSize);
    size_t rateSize() const;
    Core& at(size_t i);
    void show();
    void serialize(ofstream & ofs) const; // 序列化
    void deserialize(ifstream & ifs);// 反序列化
public:
    Core & operator[](const size_t i);
private:
    double mLength = 0;// 长度单位Km
    size_t mCoreSize = 1;// 纤芯数
    size_t mModelSize = 1;// 模式数量
    size_t mWaverSize = 1;// 波段数量
    double mRate = 0;// 速率单位Ghz
    double mBandwidth = 0;// 带宽Gbps
    size_t mRateSize = 1;// 频隙数量
    vector<Core> mCores;// 纤芯
};

#endif //WEAVER_FIBER_H
