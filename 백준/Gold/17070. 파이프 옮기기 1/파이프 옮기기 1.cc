#include <iostream>
using namespace std;


int pipe[3][2][1] = { {{0},{1}},{{1},{0}},{{1},{1}} };

int n;
int map[17][17];
int cnt;

void dfs(int y, int x, int bef_pipe) {
	if (y == n && x == n) {
		cnt++;
		return;
	}

	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			if (bef_pipe != 1) {
				if (y + pipe[i][0][0] > n || x + pipe[i][1][0] > n) { continue; }
				if(map[y + pipe[i][0][0]][x + pipe[i][1][0]]){continue;}
				dfs(y + pipe[i][0][0], x + pipe[i][1][0],i);
			}
		}
		else if (i == 1) {
			if (bef_pipe != 0) {
				if (y + pipe[i][0][0] > n || x + pipe[i][1][0] > n) { continue; }
				if (map[y + pipe[i][0][0]][x + pipe[i][1][0]]) { continue; }
				dfs(y + pipe[i][0][0], x + pipe[i][1][0], i);
			}
		}
		else {
			if (y + pipe[i][0][0] > n || x + pipe[i][1][0] > n) { continue; }
			if (map[y + pipe[0][0][0]][x + pipe[0][1][0]] ||
				map[y + pipe[1][0][0]][x + pipe[1][1][0]] ||
				map[y + pipe[2][0][0]][x + pipe[2][1][0]]) { continue; }
			dfs(y + pipe[i][0][0], x + pipe[i][1][0], i);
		}
	}

}

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
	dfs(1, 2, 0);
	cout << cnt;
}

