#include <iostream>
using namespace std;

int map[501][501];
int visited[501][501];

int n, m;

int dy[4] = { -1,1,0,0 };
int dx[4] = {0,0, -1,1 };

int max_ = 0;

void func(int num, int y, int x, int sum,int turn) {
	if (num == 3) {
		if (sum > max_) {
			max_=sum;
		}
		return;
	}

	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= n || nx >= m) { continue; }
		if (visited[ny][nx] == 1 && num == 2&&turn==0) {
			func(num, ny, nx, sum,1);
		}
		if (visited[ny][nx]==1) { continue; }

		visited[ny][nx]++;
		sum += map[ny][nx];
		func(num + 1, ny, nx, sum,turn);
		sum -= map[ny][nx];
		visited[ny][nx]--;
	}

}

int main() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			visited[i][j]++;
			func(0, i, j, map[i][j],0);
			visited[i][j]--;
		}
	}
	cout << max_;
}