#include <algorithm>
#include <queue>
#include <vector>
#include <iostream>
#include <tuple>
#include <numeric>
#include <unordered_set>


using namespace std;

typedef vector<int> intVec;
typedef vector<vector<int>> AdjacencyList;
typedef vector<vector<int>> Matrix;

typedef tuple<int, int, int> Edge;


void printAdjList(AdjacencyList& adj_list) {
	for (auto vec: adj_list) {
		cout << "[";
		for (int i: vec) {
			cout << i << ",";
		}
		cout << "] ";
	}
}

struct Compare {
	bool operator() (Edge a, Edge b) {
		return get<2>(a) > get<2>(b);
	}
};

class PrimsMST {
private:
	AdjacencyList adj_list;
	Matrix weights;
	int num_nodes;
public:
	PrimsMST(int num_nodes, vector<Edge>& edges)
		: num_nodes{num_nodes}
		, adj_list{AdjacencyList(num_nodes)}
		, weights{Matrix(num_nodes, vector<int>(num_nodes, 0))} {
			for (auto [u,v,w]: edges) {
				adj_list[u].push_back(v);
				adj_list[v].push_back(u);
				weights[u][v] = w;
				weights[v][u] = w;
			}
	}
	int mstLength() {
		priority_queue<Edge, vector<Edge>, Compare> pq;
		int length = 0;
		vector<int> mst_nodes{0};
		for (int v: this->adj_list[0]) {
			pq.push(make_tuple(0,v,weights[0][v]));
		}
		for (int i = 1; i < num_nodes; ++i) {
			auto [x,y,z] = pq.top();
			pq.pop();
			while ((find(mst_nodes.begin(), mst_nodes.end(), y) != mst_nodes.end()) && (!pq.empty())) {
				tie(x,y,z) = pq.top();
				pq.pop();
			}
			mst_nodes.push_back(y);
			length += z;
			int u = y;
			for (int v: this->adj_list[u]) {
				pq.push(make_tuple(u,v,weights[u][v]));
			}
		}
		return length;
	}
	void printList() {
		printAdjList(this->weights);
	}
};


class PrimsMST2 {
private:
	AdjacencyList adj_list;
	Matrix weights;
	int num_nodes;
public:
	PrimsMST2(int num_nodes, vector<Edge>& edges)
		: num_nodes{num_nodes}
		, adj_list{AdjacencyList(num_nodes)}
		, weights{Matrix(num_nodes, vector<int>(num_nodes, 0))} {
			for (auto [u,v,w]: edges) {
				adj_list[u].push_back(v);
				adj_list[v].push_back(u);
				weights[u][v] = w;
				weights[v][u] = w;
			}
	}
	int mstLength() {
		int u = 0, connectedNodeCount = 0, length = 0;
		priority_queue<pair<int, int>> pq;
		unordered_set<int> added_nodes;
		while(++connectedNodeCount < num_nodes) {
			added_nodes.insert(u);
			for (int v: adj_list[u]) {
				pq.push({-weights[u][v], v});
			}
			while (added_nodes.count(pq.top().second)) {
				pq.pop();
			}
			length -= pq.top().first;
			u = pq.top().second;
			pq.pop();
		}
		return length;
	}
	void printList() {
		printAdjList(this->weights);
	}
};

class DisjointSetUnion {
private:
	vector<int> parent;
	vector<int> ranks;
public:
	DisjointSetUnion(int n)
		: parent{vector<int>(n)}
		, ranks{vector<int>(n)}
	{
		iota(parent.begin(), parent.end(), 0);
	}
	int findRepresentative(int u) {
		if (this->parent[u] == u) {
			return u;
		}
		parent[u] = findRepresentative(parent[u]);
		return parent[u];
	}
	void unite(int a, int b) {
		int parent_a = this->findRepresentative(a);
		int parent_b = this->findRepresentative(b);
		if (parent_a != parent_b) {
			if (this->ranks[parent_a] == this->ranks[parent_b]) {
				this->parent[b] = parent_a;
				this->ranks[parent_a]++;
			}
			else if (this->ranks[parent_a] > this->ranks[parent_b]) {
				this->parent[b] = parent_a;
			}
			else {
				this->parent[a] = parent_b;
			}
		}
	}
	bool inside_same_component(int a, int b) {
		return (findRepresentative(a) == findRepresentative(b));
	}
	void printParents() {
		for (int i = 0; i < this->parent.size(); ++i) {
			cout << i << ", parent: " << parent[i] << endl;
		}
	}
};

class KruskalMST {
private:
	vector<Edge> m_edges;
	int num_nodes;
public:
	KruskalMST(int n, vector<Edge>& edges)
		: num_nodes{n}
		, m_edges{edges}
	{
		auto comparator = [](Edge e1, Edge e2) {
			return get<2>(e1) < get<2>(e2);
		};
		sort(m_edges.begin(), m_edges.end(), comparator);
	}
	void printEdges() {
		for (auto [u,v,w]: this->m_edges) {
			cout << "Edge: <" << u << "," << v << "," << w << ">" << endl;
		}
	}
	int computeMST_length() {
		DisjointSetUnion dsu{this->num_nodes};
		int length = 0;
		for (auto [u,v,w]: this->m_edges) {
			if (!dsu.inside_same_component(u, v)) {
				cout << "Adding Edge: <" << u << "," << v << "," << w << ">" << endl;
				length += w;
				dsu.unite(u,v);
			}
		}
		return length;
	}
};


int main() {
	int n = 5;
	vector<Edge> edges{
		make_tuple(0, 4, 4),
		make_tuple(0, 2, 2),
		make_tuple(0, 1, 7),
		make_tuple(0, 3, 8),
		make_tuple(1, 3, 3),
		make_tuple(1, 2, 8),
		make_tuple(2, 4, 6),
	};
	PrimsMST2 p2(n, edges);
	cout << p2.mstLength() << endl;
}