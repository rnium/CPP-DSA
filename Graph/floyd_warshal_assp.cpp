#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<int>> AdjacencyMatrix;
class PathDoesNotExists: public runtime_error {
    public:
        PathDoesNotExists(): runtime_error("Path does not exists between the nodes") {};
};


class FloydWarshal {
    private:
        AdjacencyMatrix distances;
        AdjacencyMatrix predecessor;
        static constexpr int UNKNOWN = -1;
        static constexpr int INF = 10'000;
        void initiate(AdjacencyMatrix& adj_matrix) {
            int n = adj_matrix.size();
            this->distances = AdjacencyMatrix(n, vector<int>(n, INF));
            this->predecessor = AdjacencyMatrix(n, vector<int>(n, UNKNOWN));
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (i == j) {
                        this->distances[i][i] = 0;
                        this->predecessor[i][i] = i;
                    }
                    else if (adj_matrix[i][j] > 0) {
                        this->distances[i][j] = adj_matrix[i][j];
                        this->predecessor[i][j] = i;
                    }
                }
            }
            
        }
        void compute(int n) {
            for (int k = 0; k < n; ++k) {
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if ((this->distances[i][k] + this->distances[k][j]) < this->distances[i][j]) {
                            this->distances[i][j] = this->distances[i][k] + this->distances[k][j];
                            this->predecessor[i][j] = this->predecessor[k][j];
                        }
                    }
                }
            }
            // for (auto vec: this->predecessor) {
            //     for (int i: vec) {
            //         cout << i << " ";
            //     }
            //     cout << endl;
            // }
        }

    public:
        FloydWarshal(AdjacencyMatrix& adj_matrix) {
            initiate(adj_matrix);
            compute(adj_matrix.size());
        }
        pair<int, vector<int>> getShortestPath(int start, int end) {
            int distance = this->distances[start][end];
            if (distance == INF) {
                throw PathDoesNotExists();
            }

            vector<int> path {end};
            int current = end;
            while (current != start) {
                current = this->predecessor[start][current];
                path.push_back(current);
            }
            std::reverse(path.begin(), path.end());
            return make_pair(distance, path);
        }
};


int main() {
    int n = 4;
    AdjacencyMatrix adjacencyMatrix(n, vector<int>(n, 0));
    vector<tuple<int, int, int>> edges {
        make_tuple(0, 1, 3), 
        make_tuple(1, 0, 2), 
        make_tuple(1, 2, 2), 
        make_tuple(2, 1, 5), 
        make_tuple(3, 2, 8), 
        make_tuple(3, 0, 20), 
        
    };
    for (auto [v, u, w] : edges) {
        adjacencyMatrix[v][u] = w;
    }

    FloydWarshal floydWarshall(adjacencyMatrix);
    auto [distance, path] = floydWarshall.getShortestPath(3, 1);
    cout << "Shortest path from 0 to 3:";
    for (int u : path) {
        cout << " " << u;
    }
    cout << endl << "Length of the path: " << distance << endl;
    
    try {
        floydWarshall.getShortestPath(1, 3);
    }
    catch (exception exe) {
        cout << "npt" << endl;
    } 
}