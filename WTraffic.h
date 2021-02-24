#ifndef W_TRAFFIC_H
#define W_TRAFFIC_H
#include <vector>
#include <chrono>
#include "Weaver.h"
using namespace std;
using namespace std::chrono;
using std::chrono::milliseconds;
class WTraffic
{
public:
	WTraffic();
	WTraffic(const WTraffic& w);
	~WTraffic();
	double rate()const;
	void setRate(double rate);
	size_t from()const;
	size_t to()const;
	void setFromAndTo(size_t from, size_t to);
	size_t keepTime()const;
	void setKeepTime(size_t millisecond);
	bool ready();
	bool isReady()const;
	bool start();
	bool isStart()const;
	bool block();
	bool isBlock()const;
	bool finish();
	bool isFinish()const;
	void setWavelengths(vector<WaveLength*> wavelengths);
	WTraffic setWavelength(WaveLength& wavelength);
	void setModel(size_t model);
	void setGrid(size_t grid);
private:
	enum TraffcStatus
	{
		NEW,
		READY,
		START,
		BLOCK,
		FINISH
	};
	size_t mFrom;
	size_t mTo;
	TraffcStatus mStatus = NEW;
	double mRate;
	size_t mKeepTime;// 保持时间 毫秒
	steady_clock::time_point mStartTime;// 开始时间
	steady_clock::time_point mFinishTime;// 完成时间
	size_t mModel;// 模式编号
	size_t mGrid;// 栅格编号
	vector<WaveLength*> mWavelengths;
};

#endif // !W_TRAFFIC_H
