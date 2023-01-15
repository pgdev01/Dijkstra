#include <iostream>
#include <vector>
#include <stack>
#include <limits>
using namespace std;

struct node {
    int nr, D=numeric_limits<int>::max(), Q=1, P=-1;
};

void path(vector<node>* nodes, int start, int end) {
    stack<int> stack;
    stack.push(end);
    for (int i = end; i != start; i= nodes->at(i).P)
        stack.push(nodes->at(i).P);
    while (!stack.empty()) {
        cout << stack.top();
        if (stack.size() > 1)
            cout << " -> ";
        stack.pop();
    }
    cout << endl;
    cout << "Koszt: " << nodes->at(end).D;
}

node min_node(vector<node> * queue) {
    node min = queue->at(0);
    for (auto it = queue->begin(); it != queue->end(); it++)
        if (it->D < min.D)
            min = *it;
    return min;
}

vector<node> mkqueue(vector<node>* nodes) {
    vector<node> queue;
    for (auto it = nodes->begin(); it != nodes->end(); it++)
        if (it->Q == 1)
            queue.push_back(*it);
    return queue;
}

void Dijkstra(vector<vector<int>>* graph, vector<node>* nodes, int start) {
    for (int i = 0; i < graph->size(); i++) {
        if (i != start)
            nodes->push_back({ i });
        else
            nodes->push_back({ i,0 });
    }
    vector<node> queue = mkqueue(nodes);
    while (!empty(queue)) {
        node min = min_node(&queue);
        nodes->at(min.nr).Q = 0;
        for (int i = 0; i < graph->size(); i++) {
            int graph_xy = graph->at(min.nr).at(i);
            if (graph_xy != 0) {
                int Dy = nodes->at(i).D;
                if ((min.D + graph_xy) < Dy) {
                    nodes->at(i).D = min.D + graph_xy;
                    nodes->at(i).P = min.nr;
                }
            }
        }
        queue = mkqueue(nodes);
    }
}

int main() {
	int start = 8, end = 0;
    vector<node> nodes;
	vector<vector<int>> graph = { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
                                { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
                                { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
                                { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
                                { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
                                { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
                                { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
                                { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
                                { 0, 0, 2, 0, 0, 0, 6, 7, 0 } };
    Dijkstra(&graph, &nodes, start);
    path(&nodes, start, end);
    return 0;
}