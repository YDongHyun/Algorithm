#include <iostream>
#include <queue>
using namespace std;

struct YX {
	int y, x;
	int dir;
};

int map[51][51];
int visited[51][51];
int n, m;
int init_y, init_x, init_dir;

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int cnt;

void bfs(int y, int x,int dir) {
	queue<YX> q;
	q.push({ y,x,dir });
	while (!q.empty()) {
		YX now = q.front();
		q.pop();
		int cc = 0;
		if (map[now.y][now.x] == 0) {
			map[now.y][now.x] = 2;
			cnt++;
		}

		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 0 || nx < 0 || ny >= n || nx >= m) { continue; }
			if (map[ny][nx] == 0) { cc++; }
		}
		if (cc == 0) {
			int ny = now.y - dy[now.dir];
			int nx = now.x - dx[now.dir];
			if (ny < 0 || nx < 0 || ny >= n || nx >= m) { continue; }
			if (map[ny][nx] == 1) {
				return;
			}
			q.push({ ny,nx,now.dir });
		}
		else {
			while(1){
				now.dir = (now.dir +3) % 4;
				int ny = now.y + dy[now.dir];
				int nx = now.x + dx[now.dir];
				if (ny < 0 || nx < 0 || ny >= n || nx >= m) { continue; }
				if (map[ny][nx] == 0) {
					q.push({ ny,nx,now.dir });
					break;
				}
			}
		}
	}
}

int main() {
	cin >> n >> m;

	cin >> init_y >> init_x >> init_dir;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	bfs(init_y, init_x, init_dir);
	cout << cnt;
}