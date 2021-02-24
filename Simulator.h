#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <vector>
#include <queue>
#include <list>
#include <mutex>
#include <thread>
#include <random>
#include <time.h>
#include <iomanip>
#include <map>
#include <iostream>
#include <chrono>
#include "Weaver.h"
#include "DAlgorithm.hpp"
#include "WTraffic.h"
#define TIME_LIMIT 1000
#define MIN_RAT 12.5
#define MAX_RAT 100



using namespace std;

class Simulator {
public:
	void begin(Weaver& weaver);
	Simulator& setCount(int count);
	Simulator& setPoissonLambda(int lambda);
	Simulator& setExponentialLambda(double lambda);
	Simulator& setThreadNum(size_t num);
	void show();
    vector<WTraffic>& getStartTrafficQueue();
    queue<WTraffic>& getBlockTrafficQueue();
    queue<WTraffic>& getFinishiTrafficQueue();
    size_t getTrafficNum();
    size_t getTrafficSuccessOverallResponseTime();
    size_t getTrafficBlockOverallResponseTime();
    size_t getOverallResponseTime();
    size_t getNowCount() const;
    size_t getCount() const;
private:
	mutex new_queue_lock;
	mutex block_queue_lock;
	mutex star_queue_lock;
    double mExponentialLambda = 0.1;// 指数分布参数
    size_t mPoissonLambda = 1;// 泊松分布参数
    size_t THREAD_NUM = 1;// 线程数量
    size_t mCount = 1;// 循环次数
    size_t mNowCount = 0;// 现在循环到了哪里
	DAlgorithm<double> dijkstra;
	vector<WTraffic> mTraffices;
	queue<WTraffic> mNewTrafficQueue;// 新产生业务队列
	vector<WTraffic> mStartTrafficQueue;// 开始业务队列
	queue<WTraffic> mBlockTrafficQueue;// 阻塞业务队列
	queue<WTraffic> mFinishiTrafficQueue;// 完成业务队列
	size_t mNum = 0;// 业务总数
	size_t mTrafficSuccessOverallResponseTime = 0;// 业务成功响应时间
	size_t mTrafficBlockOverallResponseTime = 0;// 业务阻塞响应时间
	size_t mOverallResponseTime = 0;// 业务到来总响应时间

	std::default_random_engine engineToUniform = std::default_random_engine(time(NULL));// 业务均匀引擎
	std::default_random_engine engineToUniform2 = std::default_random_engine(time(NULL));// 业务均匀引擎
	std::default_random_engine engineToExponential = std::default_random_engine(time(NULL));// 业务指数分布引擎 表示业务持续时间

	void makeNewTraffic(size_t num, size_t size);// 产生新业务
	void resourceAllocation(Weaver& weaver);// 资源分配
	vector<WaveLength*> findRote(const vector<VirtualNode*>& nodes, const vector<VirtualLink*>& links, WTraffic& traffic);// 找路由
	void releaseResource();// 释放资源
	void resoueceAllocationThread(Weaver& weaver, size_t threadNum);// 资源分配线程
};

#endif // !SIMULATOR_H
