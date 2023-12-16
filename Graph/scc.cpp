#include <stack>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef vector<vector<int>> AdjacencyList;

enum class NodeState{undiscovered, in_progress, finished};

class SCC {
private:
    int m_num_nodes;
    AdjacencyList m_adj_list;
    vector<NodeState> m_node_states;
    stack<int> m_finishing;
public:
    SCC(int n, AdjacencyList adj_list)
        : m_num_nodes{n}
        , m_adj_list{adj_list}
        , m_node_states{vector<NodeState>(n, NodeState::undiscovered)}
    {}
    void dfs1(int u) {
        if (m_node_states[u] == NodeState::undiscovered) {
            m_node_states[u] = NodeState::in_progress;
            for (int v: m_adj_list[u]) {
                dfs1(v);
            }
            m_node_states[u] = NodeState::finished;
            m_finishing.push(u);
        }
    }
    void reverseAdjList() {
        AdjacencyList new_list(m_num_nodes);
        for (int u=0; u < m_num_nodes; ++u) {
            for (int v: m_adj_list[u]) {
                new_list[v].push_back(u);
            }
        }
        m_adj_list = new_list;
    }

    void reverseDFS(int u, vector<int>& component) {
        if (m_node_states[u] == NodeState::undiscovered) {
            component.push_back(u);
            m_node_states[u] = NodeState::in_progress;
            for (int v: m_adj_list[u]) {
                reverseDFS(v, component);
            }
            m_node_states[u] = NodeState::finished;
        }
    }

    vector<vector<int>> get_scc() {
        for (int i=0; i < m_num_nodes; ++i) {
            dfs1(i);
        }
        reverseAdjList();
        fill(m_node_states.begin(), m_node_states.end(), NodeState::undiscovered);
        vector<vector<int>> res;
        while (!this->m_finishing.empty()) {
            int u = m_finishing.top();
            switch (m_node_states[u]) {
                case NodeState::undiscovered: {
                    vector<int> component;
                    reverseDFS(u, component);
                    res.push_back(component);
                }
                case NodeState::finished: {
                    m_finishing.pop();
                    break;
                }
            }
        }
        return res;
    }

    void print() {
        cout << "[";
        for (auto vec: this->m_adj_list) {
            cout << "[";
            for (int i: vec) {
                cout << i << ",";
            }
            cout << "]";
        }
        cout << "]" << endl;
    }
};

void printADJlist(AdjacencyList adj_lst) {
    cout << "[";
    for (auto vec: adj_lst) {
        cout << "[";
        for (int i: vec) {
            cout << i << ",";
        }
        cout << "]";
    }
    cout << "]" << endl;
}




int main() {

}