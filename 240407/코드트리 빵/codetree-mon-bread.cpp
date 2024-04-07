#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Human {
	int y, x;
	bool is_escape;
};

struct YX {
	int y, x;
};

int n, m;
int map[20][20];

vector<YX> base;
vector<YX> store;
vector<Human> human;
queue<YX> escape;

int dy[4] = { -1,0,0,1 };
int dx[4] = { 0,-1,1,0 };

int find_base(int num) {
	int min_dist = 21e8;
	int dist = 21e8;
	int base_idx=0;
	for (int i = 0; i < base.size(); i++) {
		dist = abs(store[num].y - base[i].y) + abs(store[num].x - base[i].x);
		if (dist <= min_dist) {
			if (dist == min_dist) {
				if (base[base_idx].y > base[i].y) {
					base_idx = i;
				}
				if (base[base_idx].y == base[i].y && base[base_idx].x > base[i].x) {
					base_idx = i;
				}
			}
			else {
				min_dist = dist;
				base_idx = i;
			}
		}
	}
	map[base[base_idx].y][base[base_idx].x] =2;
	return base_idx;
}


int main() {
	cin >> n >> m;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				base.push_back({ i,j });
			}
		}
	}
	store.push_back({ -1,-1 });
	human.push_back({ -1,-1,0 });

	int st_y, st_x;
	for (int i = 0; i < m; i++) {
		cin >> st_y >> st_x;
		store.push_back({ st_y,st_x });
	}
	int time = 1;
	int count = 1;
	bool flag = 0;

	while (1) {
		int cnt = 0;
		for(int i=1; i<=count; i++){
			if (human.size()==m+1) {
				if (human[i].is_escape){continue; }
			}
			int bs_idx = find_base(i);
			if (human.size() < i+1) {
				human.push_back({ base[bs_idx].y,base[bs_idx].x ,0});
				base.erase(base.begin() + bs_idx);
				continue;
			}
			else {
				int st_dist = abs(store[i].y - human[i].y) + abs(store[i].x - human[i].x);
				for (int j = 0; j < 4; j++) {
					int ny = human[i].y + dy[j];
					int nx = human[i].x + dx[j];
					if (ny > n || nx > n || ny < 1 || nx < 1) { continue; }
					if (map[ny][nx] == 2) { continue; }
					int dist = abs(store[i].y - ny) + abs(store[i].x - nx);
					if (st_dist > dist) {
						human[i].y = ny;
						human[i].x = nx;
						break;
					}
				}
			}

			if (human[i].y == store[i].y && human[i].x == store[i].x) {
				human[i].is_escape = 1;
				escape.push({ human[i].y,human[i].x });
			}
		}
		for (int i = 1; i <= count; i++) {
			if (human[i].is_escape == 0) { break; }
			if (i == count) {
				flag = 1;
			}
		}
		if (flag) {
			break;
		}

		while (!escape.empty()) {
			YX now = escape.front();
			escape.pop();
			map[now.y][now.x] = 2;
		}
		if(count<m){
			count++;
		}
		time++;
	}
	cout << time;


}