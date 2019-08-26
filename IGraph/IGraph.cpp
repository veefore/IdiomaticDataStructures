#include "IGraph.h"
#include "C:\Users\nolme\Repositories\vigilant-potato\unit_test.h"
#include <iostream>

#ifndef __IGRAPH__CPP__
#define __IGRAPH__CPP__

void graphRunTests();

int main() {
	graphRunTests();
}

void graphRunTests() {

	//CREATION
	//Test #1. Create and fill graph.
	//Test #2. Create and fill oriented graph.

	unit_test graph_ut("Graph");

	//SHORTESTPATH
	//Test #1. No such vertices.
	//Test #2. No path between vertices.
	//Test #3. One path, unweighted graph.
	//Test #4. One path, unweighted orgraph.
	//Test #5. One path, weighted orgraph.
	//Test #6. Many paths, unweighted orgraph.
	//Test #7. Many paths, weighted orgraph.


	struct userdeftype {
		double value;

		userdeftype(double value = 0) : value(value) {}

		bool operator<(const userdeftype &obj) const {
			return this->value < obj.value;
		}

		bool operator==(const userdeftype &obj) const {
			return this->value == obj.value;
		}

		static bool areEqual(const userdeftype &obj1, const userdeftype &obj2) {
			return obj1.operator==(obj2);
		};

		static bool lessThan(const userdeftype &obj1, const userdeftype &obj2) {
			return obj1.operator<(obj2);
		};

		bool operator>(const userdeftype &obj) const {
			return this->value > obj.value;
		}

		bool operator>=(const userdeftype &obj) const {
			return this->value >= obj.value;
		}

		userdeftype operator=(const userdeftype &obj) {
			this->value = obj.value;
			return *this;
		}

		userdeftype operator+ (const userdeftype &obj) {
			return userdeftype(this->value + obj.value);
		}
	};

	//CREATION
	//Test #1. Create and fill unweighted graph.
	//Test #2. Create and fill oriented graph.

	unit_test graph_creation("Graph::constructor()");

	//Test #1. Create and fill unweighted graph.
	graph_creation.add_test([]() {
		Graph<char, void> graph(false);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'a');
		}

		for (int i = 0; i < n; i++)
			for (int j = i + 1; j < n; j++)
				graph.addEdge(i, j);

		return graph.getData(47) == 'a';
	});

	//Test #2. Create and fill oriented graph.
	graph_creation.add_test([]() {
		Graph<char, userdeftype> graph(true);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'b');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph.addEdge(i, j, userdeftype(i + j));

		return graph.getData(47) == 'b' && graph.getWeight(17, 99) == 116 && graph.getIsOriented();
	});

	graph_ut.add_group_test(graph_creation);


	//SHORTESTPATH
	//Test #1. No such vertices.
	//Test #2. No path between vertices.
	//Test #3. One path, unweighted graph.
	//Test #4. One path, weighted orgraph.
	//Test #5. Many paths, unweighted orgraph.
	//Test #6. Many paths, weighted orgraph.

	unit_test graph_sh_path("Graph::shortestPath()");

	//Test #1. No such vertices.
	graph_sh_path.add_test([]() {
		Graph<char, userdeftype> graph(true);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'b');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph.addEdge(i, j, userdeftype(i + j));

		bool flag = false;
		try {
			graph.shortestPath(100, -70, userdeftype(0), userdeftype(10000));
		}
		catch (BadExecutionException e) {
			flag = true;
		}

		return flag;
	});

	//Test #2. No path between vertices.
	graph_sh_path.add_test([]() {
		Graph<char, userdeftype> graph(true);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'b');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph.addEdge(i, j, userdeftype(i + j));

		graph.removeVertex(88);
		graph.addVertex(88, 'a');

		return graph.shortestPath(73, 88, userdeftype(0), userdeftype(10000)) == userdeftype(10000);
	});

	//Test #3. One path, unweighted graph.
	graph_sh_path.add_test([]() {
		Graph<char, void> graph(false);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'b');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph.addEdge(i, j);

		graph.removeVertex(88);
		graph.addVertex(88, 'a');
		graph.addEdge(73, 88);

		return graph.shortestPath(74, 88) == 2;
	});

	//Test #4. One path, unweighted orgraph.
	graph_sh_path.add_test([]() {
		Graph<char, void> graph(true);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'b');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph.addEdge(i, j);

		graph.removeVertex(88);
		graph.addVertex(88, 'a');
		graph.addEdge(73, 88);

		return graph.shortestPath(73, 88) == 1;
	});

	//Test #5. Many paths, unweighted orgraph.
	graph_sh_path.add_test([]() {
		Graph<char, void> graph(true);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'b');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph.addEdge(i, j);

		graph.removeVertex(88);
		graph.addVertex(88, 'a');
		graph.addEdge(73, 88);
		graph.addEdge(23, 88);
		graph.addEdge(99, 88);
		graph.addEdge(53, 88);

		return graph.shortestPath(75, 88) == 2;
	});

	//Test #6. Many paths, weighted orgraph.
	graph_sh_path.add_test([]() {
		Graph<char, userdeftype> graph(true);
		int n = 100;
		for (int i = 0; i < n; i++) {
			graph.addVertex(i, 'b');
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				graph.addEdge(i, j, userdeftype(i + j));

		graph.removeVertex(88);
		graph.addVertex(88, 'a');
		graph.addEdge(79, 88, userdeftype(11));
		graph.addEdge(76, 88, userdeftype(1));
		graph.addEdge(99, 88, userdeftype(782));
		graph.addEdge(45, 88, userdeftype(3000));

		return graph.shortestPath(99, 88, userdeftype(0), userdeftype(10000)) == userdeftype(176);
	});

	graph_ut.add_group_test(graph_sh_path);

	graph_ut.run();
}


#endif
