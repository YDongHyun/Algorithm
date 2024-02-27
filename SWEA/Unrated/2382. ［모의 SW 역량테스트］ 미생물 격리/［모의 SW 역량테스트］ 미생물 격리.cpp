#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cstring>
using namespace std;

int t;
int n, m, k;

struct V {
	int y, x;
	int nums;
	int dir;
	bool die;
};

struct YX {
	int y, x;
};

int map[102][102];

vector<V> cell;
unordered_map<string, vector<int>> um;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void move_cells() {
	for (int i = 0; i < cell.size(); i++) {
		cell[i].y += dy[cell[i].dir];
		cell[i].x += dx[cell[i].dir];
		if (map[cell[i].y][cell[i].x] == 1) {
			cell[i].nums /= 2;
			if (cell[i].nums == 0) { cell[i].die = 1; continue; }
			if (cell[i].dir == 0) {
				cell[i].dir = 1;
			}
			else if (cell[i].dir == 1) {
				cell[i].dir = 0;
			}
			else if (cell[i].dir == 2) {
				cell[i].dir = 3;
			}
			else {
				cell[i].dir = 2;

			}
		}
		string name =to_string(cell[i].y) + "," + to_string(cell[i].x);
		um[name].push_back(i);
	}
}

int main() {
	cin >> t;
	for(int tc=1;tc<=t; tc++){
		cin >> n >> m >> k;
		for (int i = 0; i < n; i++) {
			map[i][0] = 1;
			map[0][i] = 1;
			map[n - 1][i] = 1;
			map[i][n - 1] = 1;
		}

		int v1, v2, v3, v4;
		for (int i = 0; i < k; i++) {
			cin >> v1 >> v2 >> v3 >> v4;
			cell.push_back({ v1,v2,v3,v4 - 1,0 });
		}

		for (int i = 0; i < m; i++) {
			move_cells();

			for (auto Tmp : um) {
				auto now = Tmp.second;
				if (now.size() > 1) {
					int cnt = 0;
					int next_dir = -1;
					int max_num = -1;
					for (int j = 0; j < now.size(); j++) {
						cell[now[j]].die = 1;
						cnt += cell[now[j]].nums;
						if (max_num < cell[now[j]].nums) {
							max_num = cell[now[j]].nums;
							next_dir = cell[now[j]].dir;
						}
					}
					cell.push_back({ cell[now[0]].y, cell[now[0]].x,cnt,next_dir,0 });
				}
			}
			um.clear();
			
			for (int j = cell.size() - 1; j >= 0; j--) {
				if (cell[j].die) {
					cell.erase(cell.begin() + j);
				}
			}
			
		}
		int sum = 0;
		for (int i = 0; i < cell.size(); i++) {
			sum += cell[i].nums;
		}

		cout <<"#"<<tc<<" "<< sum << "\n";
		cell.clear();
		memset(map, 0, sizeof(map));
		um.clear();

	}
}