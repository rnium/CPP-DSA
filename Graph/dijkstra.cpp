#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> NodeAndDistance;
typedef vector<vector<int>> AdjacencyList;
typedef vector<vector<int>> AdjacencyMatrix;
class DijkstraAlgo {
	private:
		AdjacencyList a_list;
		AdjacencyMatrix cost;
		vector<int> parents;
		vector<int> distances;
		static constexpr int UNKNOWN = INT32_MAX;
	public:
		DijkstraAlgo(AdjacencyList& _a_list, AdjacencyMatrix _cost)
			: a_list{_a_list}
			, cost{_cost}
			, parents{vector<int>(_a_list.size(), UNKNOWN)}
			, distances{vector<int>(_a_list.size(), UNKNOWN)}
		{}
		vector<int> sssp(int source) {
			auto comparator = [](NodeAndDistance& p1, NodeAndDistance& p2) {
				return p2.second < p1.second || (p2.second==p1.second && p2.first < p1.first);
			};
			priority_queue<NodeAndDistance, vector<NodeAndDistance>, decltype(comparator)> pq(comparator);
			pq.push(make_pair(source, 0));
			this->parents[source] = source;
			this->distances[source] = 0;
			while (! pq.empty()) {
				int u = pq.top().first;
				pq.pop();
				for (int v: a_list[u]) {
					if (distances[u] + cost[u][v] < distances[v]) {
						distances[v] = distances[u] + cost[u][v];
						// cout << "found shortest path for: " << v << " , newdist: " << distances[v] << endl;
						parents[v] = u;
						pq.push(make_pair(v, distances[v]));
					}					
				}
			}
			return this->distances;
			
		}
};

int main() {
	constexpr int inf = INT32_MAX;
	AdjacencyList a_list{{}, {2,3}, {3}, {4}, {}};
	AdjacencyMatrix cost{{0, inf, inf, inf, inf}, {inf, 0, 2, 5, inf}, {inf, inf, 0, 1, inf}, {inf, inf, inf, 0, 3}, {inf, inf, inf, inf, 0}};
	DijkstraAlgo da(a_list, cost);
	for (int i: da.sssp(1)) {
		cout << i << endl;
	}
}
