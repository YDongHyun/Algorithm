#include <iostream>
#include <queue>
using namespace std;

struct Man {
	int y, x, cost, escape;
};

struct Sq {
	int y, x, len;
};

int n, m, k;
int map[12][12];
int tmp_map[12][12];
int dy[5] = { 0,0,0,-1,1 };
int dx[5] = { 0,-1,1,0,0 };
Man man[12];
Man exit_;
Sq sq;

void find_dir(int num) {
	Man now = man[num];
	int dir = 0;
	int init_dist = abs(now.y - exit_.y) + abs(now.x - exit_.x);
	for (int i = 0; i < 5; i++) {
		int ny = now.y + dy[i];
		int nx = now.x + dx[i];
		if (ny< 1 || nx<1 || ny>n || nx>n) { continue; }
		if (map[ny][nx] > 0) { continue; }
		int dist = abs(ny - exit_.y) + abs(nx - exit_.x);
		if (init_dist >= dist) {
			init_dist = dist;
			dir = i;
		}
	}
	if (dir != 0) { man[num].cost++; }
	man[num].y += dy[dir];
	man[num].x += dx[dir];
	if (man[num].y == exit_.y && man[num].x == exit_.x) {
		man[num].escape = 1;
	}
}

void find_sq() {
	for (int len = 1; len <= n; len++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				if ((i + len) > n || (j + len) > n) { continue; }
				if (exit_.y >= i && exit_.y <= i + len &&
					exit_.x >= j && exit_.x <= j + len) {
					for (int p = 1; p <= m; p++) {
						if (man[p].escape) { continue; }
						if (man[p].y >= i && man[p].y <= i + len &&
							man[p].x >= j && man[p].x <= j + len) {
							sq = { i,j,len };
							return;
						}
					}
				}
			}
		}
	}
}

void rotation() {
	int visited[13] = { 0 };
	for (int i = sq.y; i <= sq.y + sq.len; i++) {
		for (int j = sq.x; j <= sq.x + sq.len; j++) {
			tmp_map[i][j] = map[i][j];
		}
	}
	for (int i = sq.y; i <= sq.y + sq.len; i++) {
		for (int j = sq.x; j <= sq.x + sq.len; j++) {
			int ny = j - sq.x +sq.y;
			int nx = sq.len - (i - sq.y)+sq.x;
			if (tmp_map[i][j] > 0) {
				map[ny][nx] = tmp_map[i][j] - 1;
			}
			else {
				map[ny][nx] = tmp_map[i][j];
			}
			if (i == exit_.y && j == exit_.x) {
				if (visited[12]==0) {
				visited[12] = 1;
				exit_.y = ny;
				exit_.x = nx;
				}
			}
			for (int p = 1; p <= m; p++) {
				if (man[p].escape) { continue; }
				if (man[p].y == i && man[p].x == j) {
					if (visited[p]) { continue; }
					visited[p] = 1;
					man[p].y = ny;
					man[p].x = nx;
				}
			}
		}
	}
}


int main() {
	cin >> n >> m >> k;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
	int a, b;
	for (int i = 1; i <= m; i++) {
		cin >> a >> b;
		man[i] = { a,b,0,0 };
	}
	cin >> a >> b;
	exit_ = { a,b,0,0 };

	for (int i = 0; i < k; i++) {
		for (int j = 1; j <= m; j++) {
			if (man[j].escape) { continue; }
			find_dir(j);
		}
		int flag = 0;
		for (int j = 1; j <= m; j++) {
			if (man[j].escape) { continue; }
			flag = 1;
		}
		if (flag == 0) {
			break;
		}

		find_sq();
		rotation();
	}

	int sum = 0;
	for (int i = 1; i <= m; i++) {
		sum += man[i].cost;
	}
	cout << sum << "\n";
	cout << exit_.y << " " << exit_.x;
}