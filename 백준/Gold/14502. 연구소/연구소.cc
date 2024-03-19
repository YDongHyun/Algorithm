#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int n, m;

struct YX {
	int y, x;
};

int map[9][9];
int visited[9][9];

queue<YX> q;
queue<YX> tmp_q;
vector<YX> v;
YX tmp[4];


int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };
int max_ = 0;

int bfs() {
	int cnt = 0;
	while (!tmp_q.empty()) {
		YX now = tmp_q.front();
		tmp_q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= m) { continue; }
			if (visited[ny][nx] !=0) { continue; }
			visited[ny][nx] = 2;
			tmp_q.push({ ny,nx });
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j] == 0) {
				cnt++;
			}
		}
	}
	return cnt;
}


void dfs(int num, int bef) {
	if (num == 3) {
		for (int i = 0; i < 3; i++) {
			map[tmp[i].y][tmp[i].x] = 1;
		}
		tmp_q = q;
		memcpy(visited, map, sizeof(map));
		int na = bfs();
		memset(visited, 0, sizeof(visited));
		if (na > max_) {
			max_ = na;
		}
		for (int i = 0; i < 3; i++) {
			map[tmp[i].y][tmp[i].x] = 0;
		}
		return;
	}

	for (int i = bef+1; i < v.size(); i++) {
		tmp[num] = v[i];
		dfs(num + 1, i);
	}
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
			if(map[i][j]==2){
				q.push({ i,j });
			}
			else if (map[i][j] == 0) {
				v.push_back({ i,j });
			}
		}
	}
	
	dfs(0, -1);
	cout << max_;

}