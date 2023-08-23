#include<bits/stdc++.h>
using namespace std;


typedef vector<vector<int>> AdjacencyList;

class PathDoesNotExists: public runtime_error {
    public: 
        PathDoesNotExists(): runtime_error("Path does not exists beetween the nodes") {}
};

class ShortestPath {
    private:
        AdjacencyList adj_list;
        vector<int> distances;
        vector<int> parents;
        static constexpr int UNKNOWN = -1;
    public:
        ShortestPath(const AdjacencyList& _adj_list)
            : adj_list {_adj_list}
            , distances {vector<int>(_adj_list.size(), UNKNOWN)}
        {}
        void bfs(int start) {
            this->distances.assign(adj_list.size(), UNKNOWN);
            this->parents.assign(adj_list.size(), UNKNOWN);
            queue<int> discovered;
            discovered.push(start);
            while (!discovered.empty()) {
                int u = discovered.front();
                discovered.pop();
                for (int v: adj_list[u]) {
                    if (parents[v] == UNKNOWN) {
                        this->parents[v] = u;
                        this->distances[v] = distances[u] + 1;
                        discovered.push(v);
                    }
                }
            }
        }
        vector<int> find_shortest_path(int start, int end) {
            bfs(start);
            if (parents[end] == UNKNOWN) {
                throw PathDoesNotExists();
            }
            vector<int> path;
            path.push_back(end);
            int current = end;
            while (current != start) {
                current = parents[current];
                path.push_back(current);
            }
            std::reverse(path.begin(), path.end());
            return path;
        }
};


int main() {
    int n = 7;
	AdjacencyList a_list(n);
	vector<pair<int, int>> edges {{0, 1}, {0, 2}, {1, 3}, {2,4}, {3,4}, {3,0}, {4,3}, {4,5}, {6,5}};
	for (auto [u, v]: edges) {
		a_list[u].push_back(v);
	}
    ShortestPath s_path(a_list);
    for (int i: s_path.find_shortest_path(0, 6)) {
        cout << i << " ";
    }
}