#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, m;
int start, end_;

struct Graph {
	int node;
	int cost;
};

vector<Graph> v[10001];
int visited[100001];
bool flag;

void dfs(int st, int en, int mid) {
	if (st == en) {
		flag= 1;
		return;
	}

	for (int i = 0; i < v[st].size(); i++) {
		if (visited[v[st][i].node] == 1) { continue; }
		if (v[st][i].cost < mid) {
			continue;
		}
		visited[v[st][i].node] = 1;
		dfs(v[st][i].node, en, mid);
	}
}


int bst(int st, int en) {
	int mid;
	int max_ = 0;
	while (st <= en) {
		mid = (st + en) / 2;
		memset(visited, 0, sizeof(visited));
		dfs(start, end_, mid);
		if (flag) {
			flag = 0;
			if (max_ < mid) {
				max_ = mid;
			}
			st = mid + 1;
		}
		else {
			en = mid - 1;
		}
	}
	return max_;
}

int max_cost;

int main() {
	cin >> n >> m;
	int from, to, cost;
	for (int i = 0; i < m; i++) {
		cin >> from >> to >> cost;
		if (cost > max_cost) {
			max_cost = cost;
		}
		v[from].push_back({to,cost});
		v[to].push_back({ from,cost });
		
	}
	cin >> start >> end_;
	visited[start] = 1;
	cout<<bst(1, max_cost);

}