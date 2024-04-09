#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct Human {
	int y, x;
	int dir;
	int catched;
};

struct YX {
	int y, x;
};

int score;

Human catcher;

vector<Human> runner;

int n, m, h, k;

int map[101][101];
vector<int> runner_map[101][101];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int rot;
bool mode_flag;

int margin;

queue<YX> c_move;

void move_runner() {
	for (int i = 0; i <=n; i++) {
		for (int j = 0; j <=n; j++) {
			runner_map[i][j].clear();
		}
	}
	for (int i = 0; i < runner.size(); i++) {
		if (runner[i].catched) { continue; }
		if (3 <abs(runner[i].y - catcher.y) + abs(runner[i].x - catcher.x)) { 
			runner_map[runner[i].y][runner[i].x].push_back (i + 1);
			continue; 
		}

		int ny = runner[i].y + dy[runner[i].dir];
		int nx = runner[i].x + dx[runner[i].dir];
		if (ny<1 || nx<1 || ny>n || nx>n) {
			runner[i].dir = (runner[i].dir +2) % 4;
			ny = runner[i].y + dy[runner[i].dir];
			nx = runner[i].x + dx[runner[i].dir];
			if (ny == catcher.y && nx == catcher.x) {
				runner_map[runner[i].y][runner[i].x].push_back(i + 1);
				continue;
			}
			else {
				runner[i].y = ny;
				runner[i].x = nx;
			}

		}
		else{
			if (ny == catcher.y && nx == catcher.x) {
				runner_map[runner[i].y][runner[i].x].push_back(i + 1);
				continue;
			}
			else {
				runner[i].y = ny;
				runner[i].x = nx;
			}
		}
		runner_map[runner[i].y][runner[i].x].push_back(i+1);
	}
}

void move_catcher(int mode) {
	if (mode == 1) {
		if (rot == 4) {
			rot = 0;
			margin++;
		}
		int ny = catcher.y + dy[catcher.dir];
		int nx = catcher.x + dx[catcher.dir];
		if (ny == n/2+1 && nx == n/2+1) {
			catcher.dir = 0;
			catcher.y = n/2+1;
			catcher.x = n/2+1;
			rot = 0;
			mode_flag = 0;
			margin = n / 2;
			return;
		}
		if (catcher.dir == 0) {
			if (ny == margin) {
				catcher.dir = (catcher.dir + 3) % 4;
				rot++;
			}
		}
		else if (catcher.dir == 2) {
			if (ny == n - margin + 1) {
				catcher.dir = (catcher.dir + 3) % 4;
				rot++;
			}
		}
		else if (catcher.dir == 1) {
			if (nx == n - margin + 1) {
				catcher.dir = (catcher.dir + 3) % 4;
				rot++;
			}
		}
		else if (catcher.dir == 3) {
			if (nx == margin) {
				catcher.dir = (catcher.dir + 3) % 4;
				rot++;
			}
		}
		catcher.y = ny;
		catcher.x = nx;
	}

	if(mode==0){
		if (rot == 4) {
			rot = 0;
			if (margin > 0) {
				margin--;
			}
		}
		int ny = catcher.y + dy[catcher.dir];
		int nx = catcher.x + dx[catcher.dir];
		if (ny == 1 && nx==1) {
			catcher.dir = (catcher.dir + 2) % 4;
			catcher.y = 1;
			catcher.x = 1;
			mode_flag = 1;
			margin++;
			rot = 1;
			return;
		}
		if (catcher.dir == 0 ) {
			if (ny == margin) {
				catcher.dir = (catcher.dir + 1) % 4;
				rot++;
			}
		}
		else if (catcher.dir == 2) {
			if  (ny == n - margin + 1) {
				catcher.dir = (catcher.dir + 1) % 4;
				rot++;
			}
		}
		else if (catcher.dir == 1) {
			if (nx  == n - margin + 1) {
				catcher.dir = (catcher.dir + 1) % 4;
				rot++;
			}
		}
		else if (catcher.dir == 3) {
			if (nx == margin ) {
				catcher.dir = (catcher.dir + 1) % 4;
				rot++;
			}
		}
		catcher.y = ny;
		catcher.x = nx;
	}
}

int find_runner() {
	int cnt = 0;
	for (int i = 0; i <=2;i++) {
		int ny = catcher.y + dy[catcher.dir] * i;
		int nx = catcher.x + dx[catcher.dir] * i;
		if (ny<1 || nx<1 || ny>n || nx>n) { continue; }
		if (map[ny][nx] == 1) { continue; }
		for (int j = 0; j < runner_map[ny][nx].size(); j++) {
			if (runner[runner_map[ny][nx][j] - 1].catched) { continue; }
			runner[runner_map[ny][nx][j] - 1].catched = 1;
			cnt++;
		}
		
	}
	return cnt;
}

int main() {
	cin >> n >> m >> h >> k;
	int input_y = 0;
	int input_x = 0;
	int input_dir = 0;
	margin = n / 2;
	catcher={ n / 2+1,n / 2+1,0,0 };
	for (int i = 0; i < m; i++) {
		cin >> input_y >> input_x >> input_dir;
		runner.push_back({ input_y,input_x,input_dir });
	}
	for (int i = 0; i < h; i++) {
		cin >> input_y >> input_x;
		map[input_y][input_x] = 1;
	}

	for (int iter = 1; iter <= k;iter++) {
		move_runner();
		move_catcher(mode_flag);
		int catch_cnt=find_runner();
		score += iter * catch_cnt;

	}
	cout << score;
}