#include "Simulator.h"


using namespace std::chrono;
using std::chrono::milliseconds;

void Simulator::begin(Weaver & weaver) {
	// 仿真时间
	steady_clock::time_point startTime = chrono::steady_clock::now();// 开始计时
	std::default_random_engine engineToPoisson(time(NULL));// 业务泊松分布引擎
	std::poisson_distribution<size_t> poisson(mPoissonLambda);
    mNowCount = 0;
    while(mNowCount < mCount){
        int number = poisson(engineToPoisson);// 产生业务数量
        mNum += number;
        makeNewTraffic(number, weaver.nodeSize());// 创建新业务
        resourceAllocation(weaver);// 资源分配
        releaseResource();
        mNowCount++;
    }
	show();
	// 记录仿真时间
	cout << "仿真时间（ms）：" << std::chrono::duration_cast<milliseconds>(chrono::steady_clock::now() - startTime).count() << endl;
}

Simulator & Simulator::setCount(int count) {
	mCount = count;
	return *this;
}

Simulator & Simulator::setPoissonLambda(int lambda) {
	mPoissonLambda = lambda;
	return *this;
}

Simulator & Simulator::setExponentialLambda(double lambda) {
	mExponentialLambda = lambda;
	return *this;
}

Simulator & Simulator::setThreadNum(size_t num) {
	THREAD_NUM = num;
	return *this;
}

void Simulator::show() {
	cout << "仿真情况" << endl;
	cout << "线程数量" << THREAD_NUM << endl;
	cout << "λ1:" << mPoissonLambda << endl;
	cout << "λ2:" << mExponentialLambda << endl;
	cout << "负载:" << mPoissonLambda / mExponentialLambda << endl;
	cout << "总业务数量:" << mNum << endl;
	cout << "阻塞业务数量:" << mBlockTrafficQueue.size() << endl;
	cout << "业务到来总响应时间" << mOverallResponseTime << endl;
	cout << "阻塞总响应时间" << mTrafficBlockOverallResponseTime << endl;
    cout << "成功总响应时间" << mTrafficSuccessOverallResponseTime << endl;
}

vector<WTraffic> &Simulator::getStartTrafficQueue() {
    return mStartTrafficQueue;
}

queue<WTraffic> &Simulator::getBlockTrafficQueue() {
    return mBlockTrafficQueue;
}

queue<WTraffic> &Simulator::getFinishiTrafficQueue() {
    return mFinishiTrafficQueue;
}

size_t Simulator::getTrafficNum() {
    return mNum;
}

size_t Simulator::getTrafficSuccessOverallResponseTime() {
    return mTrafficSuccessOverallResponseTime;
}

size_t Simulator::getTrafficBlockOverallResponseTime() {
    return mTrafficBlockOverallResponseTime;
}

size_t Simulator::getOverallResponseTime() {
    return mOverallResponseTime;
}

size_t Simulator::getNowCount() const {
    return mNowCount;
}

size_t Simulator::getCount() const {
    return mCount;
}

void Simulator::makeNewTraffic(size_t num, size_t size) {

	std::uniform_int_distribution<size_t> uniform(0, size - 1);
	std::uniform_real_distribution<double> uniformReal(MIN_RAT, MAX_RAT);
	std::exponential_distribution<double> exponential(mExponentialLambda);
	for (size_t i = 0; i < num; i++) {
		WTraffic traffic;
		size_t time = size_t(exponential(engineToExponential) * TIME_LIMIT);
		traffic.setKeepTime(time);
		size_t from = uniform(engineToUniform);
		size_t to = uniform(engineToUniform);
		while (from == to) {
			to = uniform(engineToUniform);
		}
		traffic.setFromAndTo(from, to);
		double rate = uniformReal(engineToUniform);
		traffic.setRate(rate);
		mNewTrafficQueue.push(traffic);
	}
}

void Simulator::resourceAllocation(Weaver& weaver) {
	// 业务到来响应时间
	steady_clock::time_point startTime = chrono::steady_clock::now();// 开始计时
	// 开启线程
	vector<thread> ts;
	for (size_t i = 0; i < THREAD_NUM; i++) {
		ts.push_back(thread(&Simulator::resoueceAllocationThread, this, ref(weaver), i));
	}
	for (auto& t : ts) {
		t.join();
	}
	mOverallResponseTime += std::chrono::duration_cast<milliseconds>(chrono::steady_clock::now() - startTime).count();// 业务到来响应时间计算
}

vector<WaveLength*> Simulator::findRote(const vector<VirtualNode*>& nodes, const vector<VirtualLink*>& links, WTraffic& traffic) {
	const size_t size = nodes.size();
	map<WNode*, size_t> indexMap;
	vector<vector<double>> matrix;// 矩阵

	// 初始化
	for (size_t i = 0; i < size; i++) {
		indexMap[nodes[i]] = i;
		vector<double> row;
		for (size_t j = 0; j < size; j++) {
			row.push_back(DBL_MAX);
		}
		matrix.push_back(row);
	}
	for (VirtualLink* link : links) {
		if (link->at(0).rate() >= traffic.rate()) {
			size_t from = indexMap[link->fromPtr()];
			size_t to = indexMap[link->toPtr()];
			double length = link->length();
			matrix[from][to] = length;
			matrix[to][from] = length;
		}
	}
	list<int> routIdList = dijkstra.find(matrix, traffic.from(), traffic.to(), DBL_MAX);
	// 找资源 第一次匹配原则
	vector<int> indexList;// 用例保存起点id + 终点id 起点+终点唯一
	vector<WaveLength*> result; // 结果
	int before = -1;
	for (int index : routIdList) {
		if (before == -1) {
			before = index;
			continue;
		}
		size_t at = before + index;
		indexList.push_back(at);
		before = index;
	}
	// 寻找时隙
	bool flag = true;//  寻找标记
	bool find = false;
	size_t model = 0;// 模式编号
	size_t grid = 0;// 栅格编号
	size_t gridSize = 0;
	double rate = traffic.rate();// 速率
	for (size_t i = 0; i < indexList.size(); i++) {
		// 遍历链路 用起点id + 终点id 进行匹配
		int linkCount = 0;
		for (VirtualLink* link : links) {
			size_t at = indexMap[link->fromPtr()] + indexMap[link->toPtr()];
			// 匹配id
			if (at == indexList[i]) {
				if (i == 0 && gridSize < link->at(0).size()) {
					gridSize = link->at(0).size();// 记录第一个链路的最大栅格数测试;
				}
				// 判断资源是否可用
				if (link->at(0).canOccupy(model, grid, rate)) {
					result.push_back(&link->at(0));// 资源可用则加入结果
					find = true;
					break;
				}
			}
			linkCount++;
		}
		if (find) {
			find = false;
			continue;
		}
		// 没找到可用资源
		// 清空结果调整资源
		result.clear();

		if (i == 0 && grid >= gridSize && linkCount == links.size()) {
			flag = false;
			break;
		}
		grid++;
		i = -1;
	}
	if (flag) {
		traffic.setModel(model);
		traffic.setGrid(grid);
		traffic.setWavelengths(result);
		traffic.ready();
		return result;
	}
	traffic.block();
	return vector<WaveLength*>();
}

void Simulator::releaseResource() {
	auto ite = mStartTrafficQueue.begin();
	while (ite != mStartTrafficQueue.end()) {
		if (ite->finish()) {
			mFinishiTrafficQueue.push(*ite);
			ite = mStartTrafficQueue.erase(ite);
		}
		else {
			ite++;
		}
	}
}

void Simulator::resoueceAllocationThread(Weaver & weaver, size_t threadNum) {
	new_queue_lock.lock();// 新业务锁
	while (!mNewTrafficQueue.empty()) {
		WTraffic w = mNewTrafficQueue.front();
		mNewTrafficQueue.pop();
		new_queue_lock.unlock();// 解开新业务锁
		// 业务计算响应时间
		steady_clock::time_point startTime = chrono::steady_clock::now();// 开始计时
		// 使用多线程模式
		for (size_t i = threadNum; i < weaver.virtualSlices().size(); i += THREAD_NUM) {
			findRote(weaver.virtualNodes(), weaver.virtualSlices()[i]->links, w);// 运行资源分配
			if (w.isBlock() && i >= weaver.virtualSlices().size() - THREAD_NUM) {
				block_queue_lock.lock();// 阻塞队列锁
				// 业务阻塞响应时间
				mTrafficBlockOverallResponseTime += std::chrono::duration_cast<milliseconds>(chrono::steady_clock::now() - startTime).count();
				mBlockTrafficQueue.push(w);
				block_queue_lock.unlock();// 解开阻塞队列锁
				break;
			}
			if (w.isReady()) {
				star_queue_lock.lock();// 开始队列锁
				// 业务成功响应时间
				mTrafficSuccessOverallResponseTime += std::chrono::duration_cast<milliseconds>(chrono::steady_clock::now() - startTime).count();
				w.start();
				mStartTrafficQueue.push_back(w);
				star_queue_lock.unlock();// 解开开始队列锁
				break;
			}
		}
		// 业务计算总响应时间
		//mTrafficOverallResponseTime += std::chrono::duration_cast<milliseconds>(chrono::steady_clock::now() - startTime).count();
		new_queue_lock.lock();// 新业务锁
	}
	new_queue_lock.unlock();// 解开新业务锁
}
