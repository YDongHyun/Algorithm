#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct YX {
	int y, x;
};

struct Tower {
	int y, x;
	int power;
	int is_attack;
	int is_damaged;
	int is_die;
};

vector<Tower> tower;

int n, m,k;
int map[11][11];
int visited[11][11];

int dy[8] = { 0,1,0,-1 ,1,1,-1,-1};
int dx[8] = { 1,0,-1,0 ,1,-1,1,-1};

int find_attacker() {
	int min_power = 21e8;
	int min_idx = 0;
	for (int i = 1; i < tower.size(); i++) {
		if (tower[i].is_die) { continue; }
		if (min_power == tower[i].power) {
			if (tower[min_idx].is_attack == tower[i].is_attack) {
				if (tower[min_idx].y + tower[min_idx].x == tower[i].y + tower[i].x) {
					if (tower[min_idx].y < tower[i].y) {
						min_idx = i;
					}
				}
				else if (tower[min_idx].y + tower[min_idx].x < tower[i].y + tower[i].x) {
					min_idx = i;
				}
			}
			else if(tower[min_idx].is_attack < tower[i].is_attack){
				min_idx = i;
			}
		}
		else if (min_power > tower[i].power) {
			min_idx = i;
			min_power = tower[i].power;
		}
	}
	return min_idx;
}

int find_defender() {
	int max_power = 0;
	int max_idx = 0;
	for (int i = 1; i < tower.size(); i++) {
		if (tower[i].is_die) { continue; }
		if (max_power == tower[i].power) {
			if (tower[max_idx].is_attack == tower[i].is_attack) {
				if (tower[max_idx].y + tower[max_idx].x == tower[i].y + tower[i].x) {
					if (tower[max_idx].y > tower[i].y) {
						max_idx = i;
					}
				}
				else if (tower[max_idx].y + tower[max_idx].x > tower[i].y + tower[i].x) {
					max_idx = i;
				}
			}
			else if (tower[max_idx].is_attack > tower[i].is_attack) {
				max_idx = i;
			}
		}
		else if (max_power < tower[i].power) {
			max_idx = i;
			max_power = tower[i].power;
		}
	}
	return max_idx;
}

bool laser_bfs(int y_, int x_,int att_idx) {
	queue<YX> q;
	q.push({ y_,x_ });
	visited[y_][x_] = 1;
	while (!q.empty()) {
		YX now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny < 1) { ny += n; }
			else if (nx < 1) { nx += m; }
			else if (ny > n) { ny -= n; }
			else if (nx > n) { nx -= m; }
			if (map[ny][nx] == 0) { continue; }
			if (visited[ny][nx]) { continue; }
			visited[ny][nx] = visited[now.y][now.x] + 1;
			q.push({ ny,nx });

		}
	}

	if (visited[tower[att_idx].y][tower[att_idx].x] != 0) {
		return 1;
	}
	return 0;
}

void laser_attack(int att, int def) {
	YX att_yx = { tower[att].y,tower[att].x };
	YX def_yx = { tower[def].y,tower[def].x };
	tower[att].power += (n + m);
	tower[att].is_damaged =1;

	int route = visited[att_yx.y][att_yx.x];

	while(1){
		for (int j = 0; j < 4; j++) {
			int ny = att_yx.y + dy[j];
			int nx = att_yx.x + dx[j];
			if (ny < 1) { ny += n; }
			else if (nx < 1) { nx += m; }
			else if (ny > n) { ny -= n; }
			else if (nx > n) { nx -= m; }
			if (map[ny][nx] == 0) { continue; }
			if (visited[ny][nx] == route - 1) {
				tower[map[ny][nx]].is_damaged = 1;

				if (visited[ny][nx] == 1) {
					tower[map[ny][nx]].power -= tower[att].power;
					return;
				}
				route -= 1;
				tower[map[ny][nx]].power -= (tower[att].power / 2);
				att_yx = { ny,nx };
				break;
			}
		}
	}
}

void boom_attack(int att, int def) {
	YX att_yx = { tower[att].y,tower[att].x };
	YX def_yx = { tower[def].y,tower[def].x };
	tower[att].power += (n + m);
	tower[att].is_damaged = 1;
	tower[def].power -= tower[att].power;
	tower[def].is_damaged = 1;


	for (int i = 0; i < 8; i++) {
		int ny = def_yx.y + dy[i];
		int nx = def_yx.x + dx[i];
		if (ny < 1) { ny += n; }
		if (nx < 1) { nx += m; }
		if (ny > n) { ny -= n; }
		if (nx > n) { nx -= m; }
		if (map[ny][nx] == 0) { continue; }
		if (map[ny][nx] != att) {
			tower[map[ny][nx]].power-= (tower[att].power / 2);
			tower[map[ny][nx]].is_damaged = 1;
		}
	}

}

int main() {
	cin >> n >> m >> k;
	tower.push_back({ 0 });
	int tower_idx = 1;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			cin >> map[i][j];
			if (map[i][j] > 0) {
				tower.push_back({ i,j,map[i][j],0,0,0});
				map[i][j] = tower_idx;
				tower_idx++;
			}
		}
	}

	for (int iter = 1; iter <=k; iter++) {
		int att_idx=find_attacker();
		tower[att_idx].is_attack = iter;
		int def_idx = find_defender();
		memset(visited, 0, sizeof(visited));
		if (laser_bfs(tower[def_idx].y, tower[def_idx].x, att_idx)) {
			laser_attack(att_idx, def_idx);
		}
		else {
			
			boom_attack(att_idx, def_idx);
		}

		for (int i = 1; i < tower.size(); i++) {
			if (tower[i].is_damaged) {
				if (tower[i].power <= 0) {
					map[tower[i].y][tower[i].x] = 0;
					tower[i].is_die = 1;
				}
				else {
					tower[i].is_damaged = 0;
				}
			}
			else {
				tower[i].power += 1;
			}

		}
	}

	int max_power = 0;
	for (int i = 1; i < tower.size(); i++) {
		if (max_power < tower[i].power) {
			max_power = tower[i].power;
		}
	}

	cout << max_power;
}