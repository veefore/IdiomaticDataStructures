#ifndef __IGRAPH__H__
#define __IGRAPH__H__

#include <utility>
#include <map>
#include <queue>
#include "C:\Users\nolme\Repositories\vigilant-potato\Exception\Exception\BadExecutionException.h"

using namespace std;

template <typename TData>
struct Vertex {
	TData data;
	int index;

public:
	Vertex() : index(-1) {}

	Vertex(int index, const TData &data) : index(index), data(data) {}
};

template <typename TData, typename TWeight = void>
class Graph {
	bool isOriented;
	map<int, Vertex<TData>> vertices;
	map<int, map<int, TWeight>> table;

	struct Comparator{
		int operator() (const pair<int, TWeight> &pair1, const pair<int, TWeight> &pair2) {
			return pair1.second < pair2.second;
		}
	};

public:
	Graph(bool isOriented) : isOriented(isOriented), table(map<int, map<int, TWeight>>()) {}

	bool getIsOriented() { return isOriented; }

	void addVertex(int index, const TData &data);

	void removeVertex(int index);

	void addEdge(int vertex1, int vertex2, const TWeight &weight);

	void removeEdge(int vertex1, int vertex2);

	TData getData(int index);

	TWeight getWeight(int vertex1, int vertex2);

	TWeight shortestPath(int vertex1, int vertex2, const TWeight &infWeight, const TWeight &zeroWeight) const;
};

template <typename TData>
class Graph<TData, void> {
	bool isOriented;
	map<int, Vertex<TData>> vertices;
	map<int, map<int, bool>> table;

public:
	Graph(bool isOriented) : isOriented(isOriented), table(map<int, map<int, bool>>()) {}

	bool getIsOriented() { return isOriented; }

	void addVertex(int index, const TData &data);

	void removeVertex(int index);

	void addEdge(int vertex1, int vertex2);

	void removeEdge(int vertex1, int vertex2);

	TData getData(int index);

	int shortestPath(int vertex1, int vertex2) const;
};

template <typename TData, typename TWeight>
void Graph<TData, TWeight>::addVertex(int index, const TData &data) {
	if (vertices.find(index) != vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::addVertex().", "Vertex with a such index already exists.");

	Vertex<TData> vertex(index, data);
	vertices[index] = vertex;
	map<int, TWeight> m;
	table[index] = m;
}

template <typename TData, typename TWeight>
void Graph<TData, TWeight>::removeVertex(int index) {
	if (vertices.find(index) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::removeVertex().", "No vertex with such index to remove.");

	vertices.erase(index);
	if (!this->isOriented)
		for (auto itr = table[index].begin(); itr != table[index].end(); itr++)
			table[itr->first].erase(index);
	else
		for (auto itr = vertices.begin(); itr != vertices.end(); itr++)
			table[itr->second.index].erase(index);
	table.erase(index);
}

template <typename TData, typename TWeight>
void Graph<TData, TWeight>::addEdge(int vertex1, int vertex2, const TWeight &weight) {
	if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::addEdge().", "One of the vertexes is absent.");

	table[vertex1][vertex2] = weight;
	if (!this->isOriented) {
		table[vertex2][vertex1] = weight;
	}
}

template <typename TData, typename TWeight>
void Graph<TData, TWeight>::removeEdge(int vertex1, int vertex2) {
	if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::removeEdge().", "One of the vertexes is absent.");

	table[vertex1].erase(vertex2);
	if (!this->isOriented) {
		table[vertex2].erase(vertex1);
	}
}

template <typename TData, typename TWeight>
TData Graph<TData, TWeight>::getData(int index) {
	if (vertices.find(index) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::getData().", "No vertex with such index.");

	return vertices[index].data;
}

template <typename TData, typename TWeight>
TWeight Graph<TData, TWeight>::getWeight(int vertex1, int vertex2) {
	if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::getWeight().", "One of the vertexes is absent.");

	return table[vertex1][vertex2];
}

template <typename TData, typename TWeight>
TWeight Graph<TData, TWeight>::shortestPath(int vertex1, int vertex2, const TWeight &zeroWeight, const TWeight &infWeight) const {
	if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::shortestPath().", "One of the vertexes is absent.");

	priority_queue<pair<int, TWeight>, vector<pair<int, TWeight>>, Comparator> priorityQueue;
	map<int, TWeight> distances;
	for (auto itr = vertices.begin(); itr != vertices.end(); itr++) {
		distances[(*itr).first] = infWeight;
	}

	priorityQueue.push({ vertex1, zeroWeight });
	distances[vertex1] = zeroWeight;

	while (!priorityQueue.empty()) {
		int cur = priorityQueue.top().first;
		priorityQueue.pop();


		auto begin = table.find(cur);
		if (begin != table.end())
			for (auto itr = (*begin).second.begin(); itr != (*begin).second.end(); itr++) {
				int adj = itr->first;
				TWeight weight = itr->second;

				if (distances[adj] > distances[cur] + weight) {
					distances[adj] = distances[cur] + weight;
					priorityQueue.push({ adj, distances[adj] });
				}
			}
	}
	return distances[vertex2];
}





template <typename TData>
void Graph<TData, void>::addVertex(int index, const TData &data) {
	if (vertices.find(index) != vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::addVertex().", "Vertex with a such index already exists.");

	Vertex<TData> vertex(index, data);
	vertices[index] = vertex;
	map<int, bool> m;
	table[index] = m;
}

template <typename TData>
void Graph<TData, void>::removeVertex(int index) {
	if (vertices.find(index) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::removeVertex().", "No vertex with such index to remove.");

	vertices.erase(index);
	if (!this->isOriented) {
		for (auto itr = table[index].begin(); itr != table[index].end(); itr++)
			if (itr->first != index)
				table[itr->first].erase(index);
	}
	else
		for (auto itr = vertices.begin(); itr != vertices.end(); itr++)
			table[itr->second.index].erase(index);
	table.erase(index);
}

template <typename TData>
void Graph<TData, void>::addEdge(int vertex1, int vertex2) {
	if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::addEdge().", "One of the vertexes is absent.");

	table[vertex1][vertex2] = true;
	if (!this->isOriented) {
		table[vertex2][vertex1] = true;
	}
}

template <typename TData>
void Graph<TData, void>::removeEdge(int vertex1, int vertex2) {
	if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) = vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::removeEdge().", "One of the vertexes is absent.");

	table[vertex1].erase(vertex2);
	if (!this->isOriented) {
		table[vertex2].erase(vertex1);
	}
}

template <typename TData>
TData Graph<TData, void>::getData(int index) {
	if (vertices.find(index) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::getData().", "No vertex with such index.");

	return vertices[index].data;
}

template <typename TData>
int Graph<TData, void>::shortestPath(int vertex1, int vertex2) const {
	if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end())
		throw BadExecutionException("BadExecutionException thrown at Graph::shortestPath().", "One or more of the vertexes is absent.");

	queue<pair<int, int>> queue;
	map<int, bool> visited;
	for (auto itr = vertices.begin(); itr != vertices.end(); itr++)
		visited[itr->first] = false;
	queue.push({ vertex1, 0 });

	int answer = -1;

	while (!queue.empty()) {
		int index = queue.front().first;
		int path = queue.front().second;
		queue.pop();
		if (visited[index] == true)
			continue;
		visited[index] = true;

		auto begin = table.find(index);
		if (begin != table.end())
			for (auto itr = (*begin).second.begin(); itr != (*begin).second.end(); itr++) {
				if (itr->first == vertex2) {
					answer = path + 1;
					visited[vertex2] = true;
					break;
				}
				if (visited[itr->first] == false) {
					queue.push(make_pair(itr->first, path + 1));
				}
			}

		if (visited[vertex2] == true)
			break;
	}
	return answer;
}

#endif
