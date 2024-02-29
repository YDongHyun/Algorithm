#include <iostream>
#include <queue>
#include <cstring>
using namespace std;


struct YX {
	int y, x;
};

int t, n, k;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1};
int map[20][20];
int visited[20][20];
int max_top;
int max_dist;
vector<YX> top;

void func(int y, int x, int cnt, int flag) {
	if (max_dist < cnt) {
		max_dist = cnt;
	}
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || nx < 0 || ny >= n || nx >= n) { continue; }
		if (visited[ny][nx]) { continue; }
		for (int j = 0; j <=k; j++) {
			if (j == 0) {
				if (map[ny][nx] < map[y][x]) {
					cnt += 1;
					visited[ny][nx] = 1;
					func(ny, nx, cnt,flag);
					visited[ny][nx] = 0;
					cnt -= 1;
				}
			}
			else {
				if(flag==0){
					map[ny][nx] -= j;
					if (map[ny][nx] < map[y][x]) {
						cnt += 1;
						visited[ny][nx] = 1;
						func(ny, nx, cnt, 1);
						visited[ny][nx] = 0;

						cnt -= 1;
					}
					map[ny][nx] += j;
				}
			}
		}
	}
}

int main() {
	cin >> t;
	for (int tc = 1; tc <= t; tc++) {
		cin >> n >> k;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> map[i][j];
				if (map[i][j] > max_top) {
					max_top = map[i][j];
				}
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (map[i][j] == max_top) {
					top.push_back({ i,j });
				}
			}
		}

		for(int i=0; i<top.size(); i++){
			visited[top[i].y][top[i].x] = 1;
			func(top[i].y,top[i].x,1,0);
			visited[top[i].y][top[i].x] = 0;
		}
		cout << "#" << tc << " " << max_dist << "\n";
		max_top=0;
		max_dist=0;
		top.clear();
	}

}