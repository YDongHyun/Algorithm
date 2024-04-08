#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct YX {
	int y, x;
};

struct Tile {
	int num;
	int count;
};


vector<Tile> tile;

int n;
int map[30][30];
int tmp_map[30][30];

int visited[30][30];
int map_count[900][900];

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

Tile bfs(int y_, int x_,int idx) {
	queue<YX> q;
	q.push({ y_,x_ });
	visited[y_][x_] = idx;
	int val = map[y_][x_];
	int cnt = 1;
	while (!q.empty()) {
		YX now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= n) { continue; }
			if (visited[ny][nx]) { continue; }
			if (map[ny][nx] == val) {
				visited[ny][nx] = idx;
				cnt++;
				q.push({ ny,nx });
			}
		}
	}


	return { val, cnt };
}

void rotation_(int st, int en) {
	int div = n / 2;
	for (int i = 0; i < div; i++) {
		for (int j = 0; j < div; j++) {
			map[j+st][div-i-1+en] = tmp_map[i+st][j+en];
		}
	}
}

void rotation_r() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[n-j-1][i] = tmp_map[i][j];
		}
	}
}

void rotation_map() {
	int div = n / 2;
	memcpy(tmp_map, map, sizeof(map));
	rotation_r();
	rotation_(0, 0);
	rotation_(div+1,0);
	rotation_(0, div + 1);
	rotation_(div + 1, div + 1);	
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	int sum = 0;

	for(int rot=0; rot<4; rot++){
		memset(visited, 0, sizeof(visited));
		memset(map_count, 0, sizeof(map_count));
		tile.clear();
		tile.push_back({ 0 });
		
		if (rot > 0) {
			rotation_map();
		}

		int idx = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (visited[i][j]) { continue; }
				idx++;
				Tile now =bfs(i, j,idx);
				tile.push_back({now.num, now.count });
			}
		}

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < 4; k++) {
					int ny = i + dy[k];
					int nx = j + dx[k];
					if (ny >= n || nx >= n || ny < 0 || nx < 0) { continue; }
					if (visited[ny][nx] != visited[i][j]) {
						map_count[visited[i][j]][visited[ny][nx]]++;
					}

				}
			}
		}
		for (int i = 1; i <= idx; i++) {
			for (int j = i + 1; j <= idx; j++) {
				if (map_count[i][j] == 0) { continue; }
				sum += (tile[i].count + tile[j].count) * tile[i].num * tile[j].num * map_count[i][j];
			}
		}
	}
	cout << sum;

}