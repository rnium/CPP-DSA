#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <numeric>
#include <algorithm>

using namespace std;


template<typename T>
void printVec(vector<T>& vec) {
    for (T i: vec) {
        cout << i << " ";
    }
    cout << endl;
}

typedef vector<vector<pair<int, int>>> AdjacencyList;
typedef tuple<int, int, int> Edge;


class DisjointSetUnion {
private:
    vector<int> parents;
    vector<int> ranks;
public:
    DisjointSetUnion(int num_nodes)
        : ranks{vector<int>(num_nodes, 0)}
        , parents{vector<int>(num_nodes)} {
        iota(parents.begin(), parents.end(), 0);
    }
    int find(int u) {
        if (parents[u] == u) {
            return u;
        }
        parents[u] = find(parents[u]);
        return parents[u];
    }
    void unite(int a, int b) {
        int u = find(a);
        int v = find(b);
        if (u != v) {
            if (ranks[u] == ranks[v]) {
                parents[u] = v;
                ranks[v]++;
            }
            else if (ranks[u] > ranks[v]) {
                parents[v] = u;
            }
            else if (ranks[u] < ranks[v]) {
                parents[u] = v;
            }
        }
    }
};

pair<int, AdjacencyList> computeMST(AdjacencyList& adj_list) {
    vector<Edge> edges;
    int num_nodes = adj_list.size();
    AdjacencyList mst_adj_list(num_nodes);
    for (int u = 0; u < num_nodes; ++u) {
        for (auto [v,w]: adj_list[u]) {
            edges.push_back(make_tuple(u,v,w));
        }
    }
    sort(edges.begin(), edges.end(), [](Edge a, Edge b){return get<2>(a) < get<2>(b);});
    DisjointSetUnion dsu(num_nodes);
    int weightofmst = 0;
    for (auto [u,v,w]: edges) {
        if (dsu.find(u) != dsu.find(v)) {
            dsu.unite(u,v);
            weightofmst += w;
            mst_adj_list[u].push_back(make_pair(v,w));
            mst_adj_list[v].push_back(make_pair(u,w));
        }
    }
    return make_pair(weightofmst, mst_adj_list);
}

int main() {
    int n = 5;
    vector<Edge> edges{
        make_tuple(0,1,7),
        make_tuple(0,3,8),
        make_tuple(0,2,2),
        make_tuple(0,4,4),
        make_tuple(1,3,3),
        make_tuple(1,2,8),
        make_tuple(2,4,6),
    };
    AdjacencyList adj_list(n);
    for (auto [u,v,w]: edges) {
        adj_list[u].push_back(make_pair(v,w));
        adj_list[v].push_back(make_pair(u,w));
    }
    auto [weight, mstAdj] = computeMST(adj_list);
    cout << weight << endl;
}
