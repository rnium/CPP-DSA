#include <bits/stdc++.h>
using namespace std;

typedef vector<int> intVec;
typedef vector<vector<int>> AdjacencyList;

// DFS implemetation
enum class NodeState {UNVISITED, IN_PROGRESS, FINISHED};

class CycleDetector {
	private:
		AdjacencyList adj_list;
		vector<NodeState> node_states;
		bool cycle_found;
	public:
		CycleDetector(const AdjacencyList& _adj_list)
			: adj_list{_adj_list}
			, node_states {vector<NodeState>(_adj_list.size(), NodeState::UNVISITED)}
			, cycle_found{false}
		{}
		void dfs(int u) {
			this->node_states[u] = NodeState::IN_PROGRESS;
			for (int v: this->adj_list[u]) {
				switch(this->node_states[v]) {
					case NodeState::UNVISITED: dfs(v);break;
					case NodeState::IN_PROGRESS: this->cycle_found = true; break;
					case NodeState::FINISHED: break;
				}
			}
			node_states[u] = NodeState::FINISHED;
		}
		bool has_cycle() {
			int num_nodes = static_cast<int>(adj_list.size());
			for (int u = 0; u < num_nodes; u++) {
				dfs(u);
			}
			return this->cycle_found;
		}
};

class CycleFoundError: public runtime_error {
	public:
		CycleFoundError(): runtime_error("cyclic graphs cannot perform topylogy sort!") {}
};

class TopologySort {
	private:
		AdjacencyList adj_list;
		vector<NodeState> node_states;
		vector<int> finishing_order;
	public:
		TopologySort(AdjacencyList& _adj_list)
			: adj_list{_adj_list}
			, node_states{vector<NodeState>(_adj_list.size(), NodeState::UNVISITED)}
			, finishing_order(0)
		{}
		void dfs(int u) {
			node_states[u] = NodeState::IN_PROGRESS;
			for (int v: adj_list[u]) {
				switch(node_states[v]) {
					case NodeState::UNVISITED: dfs(v); break;
					case NodeState::IN_PROGRESS: throw CycleFoundError(); break;
					case NodeState::FINISHED: break;
				}
			}
			node_states[u] = NodeState::FINISHED;
			// clog << "finished: " << u << endl;
			finishing_order.push_back(u);
		}
		vector<int> topology_sort() {
			int num_nodes = static_cast<int>(adj_list.size());
			for (int u = 0; u < num_nodes; u++) {
				if (node_states[u] == NodeState::FINISHED) continue;
				dfs(u);
			}
			reverse(finishing_order.begin(), finishing_order.end());
			return finishing_order;
		}
};

int main() {
	int n = 4;
	AdjacencyList a_list(n);
	vector<pair<int, int>> edges {{0, 1}, {1,2}, {3,2}};
	for (auto [u, v]: edges) {
		a_list[u].push_back(v);
	}
	TopologySort t_sort(a_list);
	// t_sort.topology_sort();
	for (int i: t_sort.topology_sort()) {
		cout << i << " ";
	}
}