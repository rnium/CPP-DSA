#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> AdjacencyList;

enum class Colors {WHITE, RED, BLUE};

class Bicolor {
    private:
        AdjacencyList adj_list;
        vector<Colors> colors;
        vector<int> levels;
        static constexpr int UNKNOWN = -1;
    public:
        Bicolor(AdjacencyList& _adj_list)
            : adj_list{_adj_list}
            , colors{vector<Colors>(_adj_list.size(), Colors::WHITE)}
            , levels{vector<int>(_adj_list.size(), UNKNOWN)}
        {}
        bool is_bicolorable(int start) {
            queue<int> q;
            colors[start] = Colors::RED;
            levels[start] = 0;
            q.push(start);
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v: adj_list[u]) {
                    if (levels[v] == UNKNOWN) {
                        levels[v] = levels[u] + 1;
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
    AdjacencyList a_list(3);
    vector<pair<int, int>> edges{{0,2}, {2,1}, {1,0}};
    for (auto [u,v]: edges) {
        a_list[u].push_back(v);
    }
    Bicolor b(a_list);
    cout << boolalpha << b.is_bicolorable(0) << endl;
}