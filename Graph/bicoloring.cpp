#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> AdjacencyList;

enum class Colors {WHITE, RED, BLUE};

class Bicolor {
    private:
        AdjacencyList adj_list;
        vector<Colors> colors;
        vector<int> explored_nodes;
        static constexpr int UNEXPLORED = 0;
        static constexpr int EXPLORED = 1;
    public:
        Bicolor(AdjacencyList& _adj_list)
            : adj_list{_adj_list}
            , colors{vector<Colors>(_adj_list.size(), Colors::WHITE)}
            , explored_nodes{vector<int>(_adj_list.size(), UNEXPLORED)}
        {}
        bool is_bicolorable(int start) {
            queue<int> q;
            colors[start] = Colors::RED;
            q.push(start);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                explored_nodes[u] = EXPLORED;
                for (int v: adj_list[u]) {
                    if (explored_nodes[v] == UNEXPLORED) {
                        q.push(v);
                    }
                    if (colors[v] == Colors::WHITE) {
                        if (colors[u] == Colors::RED) {
                            colors[v] = Colors::BLUE;
                        }
                        else {
                            colors[v] = Colors::RED;
                        }
                    }
                    if (colors[u] == colors[v]) {
                        return false;
                    }
                }
            }
            return true;
        }
};

int main() {
    AdjacencyList a_list(4);
    vector<pair<int, int>> edges{{0,2}, {2,3}, {3,1}, {1,0}};
    for (auto [u,v]: edges) {
        a_list[u].push_back(v);
    }
    Bicolor b(a_list);
    cout << boolalpha << b.is_bicolorable(0) << endl;
}