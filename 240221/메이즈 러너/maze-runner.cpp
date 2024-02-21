#include <iostream>
#include <queue>
using namespace std;

struct Man {
	int y, x, cost, escape;
};

int n, m, k;
int map[12][12];
int dy[5] = { 0,0,0,-1,1 };
int dx[5] = { 0,-1,1,0,0 };
Man man[12];
Man exit_;
int global_dist = 21e8;

int find_dir(int num) {
	Man now = man[num];
	int min_dist = 21e8;
	int dir = 0;
	int init_dist = abs(now.y - exit_.y) + abs(now.x - exit_.x);
	for (int i = 0; i < 5; i++) {
		int ny = now.y + dy[i];
		int nx = now.x + dx[i];
		if (ny< 1 || nx<1 || ny>n || nx>n) { continue; }
		if (map[ny][nx] > 0) { continue; }
		int dist = abs(ny - exit_.y) + abs(nx - exit_.x);
		if (min_dist >= dist) {
			min_dist = dist;
			dir = i;
		}
	}
	return dir;
}

void find_man(int num) {
	Man now = man[num];
	int dist = abs(now.y - exit_.y) + abs(now.x - exit_.x);
	if (dist < global_dist) {
		global_dist = dist;
	}
}

void rotation_box(int length) {
	for (int i = 1; i <= m; i++) {
		if (man[i].escape) { continue; }
		map[man[i].y][man[i].x] = -i;
	}
	map[exit_.y][exit_.x] = -11;
	int flag1 = 0;
	int flag2 = 0;
	int flag3 = 0;

	pair<int, int> square_;
	queue<int> tmp;

	for (int i = 1; i <= n; i++) {
		if (flag3) { break; }
		for (int j = 1; j <= n; j++) {
			if (flag3) { break; }
			if (i + length<1 || j + length<1 || i + length>n || j + length>n) { continue; }
			for (int k = i; k <= i + length; k++) {
				if (flag3) { break; }
				for (int l = j; l <= j + length; l++) {
					if (flag3) { break; }
					if (map[k][l] == -11) { flag1 = 1; }
					else if (map[k][l] < 0) { flag2 = 1; }
					if (flag1 && flag2) {
						square_ = { i,j };
						flag3 = 1;
						break;
					}
				}
			}
		}
	}
	for (int i = square_.first; i <= square_.first + length; i++) {
		for (int j = square_.second; j <= square_.second + length; j++) {
			tmp.push(map[i][j]);
		}
	}

	for (int i = square_.second + length; i >= square_.second; i--) {
		for (int j = square_.first; j <= square_.first + length; j++) {
			int re = tmp.front();
			tmp.pop();
			if (re > 0) {
				map[j][i] = re - 1;
			}
			else if (re == -11) {
				map[j][i] = 0;
				exit_.y = j;
				exit_.x = i;
			}
			else if (re < 0) {
				map[j][i] = 0;
				man[-re].y = j;
				man[-re].x = i;
			}
			else {
				map[j][i] = 0;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] < 0) {
				map[i][j] = 0;
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

	for (int i = 1; i <= k; i++) {
		for (int j = 1; j <= m; j++) {
			if (man[j].escape) { continue; }
			int dir = find_dir(j);

			man[j].y += dy[dir];
			man[j].x += dx[dir];
			if (dir != 0) {
				man[j].cost++;
			}
			if (man[j].y == exit_.y && man[j].x == exit_.x) {
				man[j].escape = 1;
			}
		}

		for (int j = 1; j <= m; j++) {
			if (man[j].escape) { continue; }

			find_man(j);
		}

		rotation_box(global_dist);

		global_dist = 21e8;
	}
	int cnt = 0;
	for (int i = 1; i <= m; i++) {
		cnt += man[i].cost;
	}
	cout << cnt << "\n";
	cout << exit_.y << " " << exit_.x;

}