#pragma once
#include <vector>
#include <list>
using namespace std;
// D算法
template <typename T>
class DAlgorithm {
public:
	list<int> find(const vector<vector<T>> matrix, const unsigned int from, const unsigned int to, const T MXA_VALUE);
};

template<typename T>
list<int> DAlgorithm<T>::find(const vector<vector<T>> matrix, const unsigned int from, const unsigned int to, const T MAX_VALUE) {
	const unsigned int size = matrix.size();
	auto* distance = new T[size];// 距离
	auto* find = new bool[size];// 标记
	auto* prev = new int[size];// 前驱节点
	// 初始化
	for (unsigned int i = 0; i < size; i++) {
		find[i] = false;
		distance[i] = matrix[from][i];
		if (matrix[from][i] == MAX_VALUE || i == from) {
			prev[i] = -1;
		}
		else {
			prev[i] = from;
		}
	}
	find[from] = true;
	distance[from] = 0;
	int now = from;// 当前节点
	int before;// 上一个节点
	for (unsigned int i = 0; i < size; i++) {
		before = now;
		//寻找当前的最短路径
		//即在为获取最短路径的顶点中，找到离起点最近的顶点（k）
		T min = MAX_VALUE;
		for (unsigned int j = 0; j < size; j++) {
			if (!find[j] && distance[j] < min) {
				min = distance[j];
				now = j;
			}
		}
		if (now == before) {
			break;//没有新节点的情况
		}
		//标记"节点now"为已经获取到最短路径
		find[now] = true;
		//修正当前最短路径和前驱节点
		for (unsigned int j = 0; j < size; j++) {
			if (find[j]) {
				continue;
			}
			T tmp = (matrix[now][j] == MAX_VALUE ? MAX_VALUE : (min + matrix[now][j]));
			if (tmp < distance[j]) {
				distance[j] = tmp;
				prev[j] = now;
			}
		}
	}
	list<int> route;
	int index = to;
	while (prev[to] != -1 && index != -1) {
		route.push_front(index);
		index = prev[index];
	}
	delete[] prev;
	delete[] find;
	delete[] distance;
	return route;
}
