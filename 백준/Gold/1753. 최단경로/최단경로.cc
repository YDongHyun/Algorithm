#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

struct Node {
	int to_node;
	int cost;

	bool operator<(Node a)const {
		return a.cost <  cost;
	}
};




int v, e;
int st_node;

vector<Node> graph[20001];
int dist[20001];

void dijk(int st_node) {
	priority_queue<Node> qu;
	qu.push({ st_node,0 });
	for (int i = 0; i <= v; i++) {
		dist[i] = 21e8;
	}
	dist[st_node] = 0;
	while (!qu.empty()) {
		Node now = qu.top();
		qu.pop();
		for (int i = 0; i < graph[now.to_node].size(); i++) {
			Node next = graph[now.to_node][i];
			int nextcost = dist[now.to_node] + next.cost;
			if (nextcost >= dist[next.to_node]) { continue; }
			qu.push({ next.to_node,nextcost });
			dist[next.to_node] = nextcost;
		}
	}
}

int main() {
	scanf("%d %d %d",&v,&e,&st_node);
	int st, tar, cost;
	for(int i = 0; i < e; i++) {
		scanf("%d %d %d",&st,&tar,&cost);
		graph[st].push_back({ tar,cost });
	}
	dijk(st_node);
	for (int i = 1; i <=v; i++) {
		if (dist[i] == 21e8) {
			printf("INF\n");
		}
		else {
			printf("%d\n", dist[i]);
		}
		
	}
	
}