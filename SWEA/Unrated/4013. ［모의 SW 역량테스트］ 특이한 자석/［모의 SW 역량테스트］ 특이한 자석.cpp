#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

queue<pair<int, int>> q;

int t, k;
int map[5][9];
int visited[4];

void rotate(int idx, int dir) {
	if (idx != 0) {
		if (map[idx - 1][2] != map[idx][6]) {
			if(visited[idx-1]==0){
				visited[idx - 1] = 1;
				if(dir ==1){
					rotate(idx - 1, -1);
				}
				else {
					rotate(idx - 1, 1);
				}
			}
		}

	}
	if (idx != 3) {
		if (map[idx + 1][6] != map[idx][2]) {
			if(visited[idx+ 1] == 0) {
				visited[idx + 1] = 1;
				if (dir == 1) {
					rotate(idx + 1, -1);
				}
				else {
					rotate(idx + 1, 1);
				}
			}
		}
	}
	if(dir ==1){
		int tmp = map[idx][7];

		for (int i = 6; i >=0; i--) {
			map[idx][i+1] = map[idx][i];
		}
		map[idx][0] = tmp;
	}
	else {
		int tmp = map[idx][0];

		for (int i = 1; i <=7; i++) {
			map[idx][i-1] = map[idx][i];
		}
		map[idx][7] = tmp;
	}
}

int main() {
	cin >> t;
	for(int tc= 1; tc<=t; tc++){
		cin >> k;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 8; j++) {
				cin >> map[i][j];
			}
		}
		int a, b;
		for (int i = 0; i < k; i++) {
			cin >> a >> b;
			q.push({ a - 1,b });
		}

		while (!q.empty()) {
			pair<int, int> now = q.front();
			q.pop();
			visited[now.first] = 1;
			rotate(now.first, now.second);
			memset(visited, 0, sizeof(visited));
		}
		int sum = 0;
		for (int i = 0; i < 4; i++) {
			sum += map[i][0] * pow(2, i);
		}

		cout <<"#"<<tc<<" "<< sum << "\n";
		memset(map, 0, sizeof(map));

	}
}