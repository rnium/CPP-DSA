#include <cassert>
#include <iostream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> AdjList;

enum class NodeState{undiscovered, in_progress, finished};

class CycleExistsError: public runtime_error {
public:
    CycleExistsError()
        : runtime_error("Cycle Exists in the graph")
    {}
};


class TopologySort {
private:
    int m_num_nodes;
    AdjList m_adj_list;
    vector<NodeState> m_states;
    vector<int> m_finishing;
public:
    TopologySort(int n, AdjList a_list)
        : m_num_nodes{n}
        , m_adj_list{a_list}
        , m_states{vector<NodeState>(n, NodeState::undiscovered)}
    {}
    void dfs(int u) {
        switch(this->m_states[u]) {
            case (NodeState::undiscovered): {
                m_states[u] = NodeState::in_progress;
                for (int v: m_adj_list[u]) {
                    dfs(v);
                }
                m_states[u] = NodeState::finished;
                m_finishing.push_back(u);
                break;
            }
            case (NodeState::in_progress): {
                throw CycleExistsError();
                break;
            }
            case NodeState::finished: {
                break;
            }
        }
    }
    vector<int> topology_order() {
        for (int i = 0; i < m_num_nodes; ++i) {
            dfs(i);
        }
        reverse(m_finishing.begin(), m_finishing.end());
        return m_finishing;
    }
};


int main() {
    int n = 5;
    AdjList adjacencyList(n);
    vector<pair<int, int>> edges {{0, 1}, {0, 4}, {2, 4}, {2, 1}, {3, 0}, {4, 1}};
    for (auto [u, v] : edges) {
        adjacencyList[u].push_back(v);
    }
    TopologySort t1(n, adjacencyList);
    vector<int> res = t1.topology_order();
    for (int i: res) {
        cout << i << " ";
    }
    cout << endl;
}