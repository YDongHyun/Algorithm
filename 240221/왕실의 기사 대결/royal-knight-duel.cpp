#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Knight {
	int y;
	int x;
	int h;
	int w;
	int k;
	int die;
};

struct Move {
	int knight_idx;
	int dir;
};

queue<Move> move_knight;
Knight knights[32];

int l, n, q;
int map[42][42];
int knight_map[42][42];
int tmp_map[42][42];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };
int init_hp[32];

void copy_map(int a[42][42], int b[42][42]) {
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++) {
			a[i][j] = b[i][j];
		}
	}
}

void bfs(int idx, int dir) {
	if (knights[idx].die) { return; }
	copy_map(tmp_map, knight_map);
	int visited[32] = { 0 };
	int DAT[32] = { 0 };
	int damage[32] = { 0 };
	DAT[idx] = 1;
	queue<Knight> q;
	q.push({ knights[idx] });
	while (!q.empty()) {

		Knight now = q.front();
		int idx_ = knight_map[now.y][now.x];
		visited[idx_] = 1;
		q.pop();
		for (int i = now.y; i < now.y + now.h; i++) {
			for (int j = now.x; j < now.x + now.w; j++) {
				int ny = i + dy[dir];
				int nx = j + dx[dir];
				if (ny<1 || nx<1 || ny>l || nx>l) { return; }
				if (map[ny][nx] == 2) { return; }
				if (map[ny][nx] == 1 && idx_!=idx) {
					damage[idx_]++;
				}
				tmp_map[i][j] = 0;
				if (knight_map[ny][nx] != idx && knight_map[ny][nx] > 0) {
					DAT[knight_map[ny][nx]]++;
				}
			}
		}
		for (int i = 1; i <= n; i++) {
			if (DAT[i] != 0 && !visited[i]) {
				q.push(knights[i]);
				visited[i] = 1;
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		if (DAT[i] != 0 ) {
			knights[i].k -= damage[i];
			if (knights[i].k <= 0) { knights[i].die = 1; continue;}
			knights[i].y += dy[dir];
			knights[i].x += dx[dir];
			Knight next = knights[i];
			for (int k = next.y; k < next.y + next.h; k++) {
				for (int j = next.x; j < next.x + next.w; j++) {
					tmp_map[k][j] = i;
				}
			}
		}
	}
	copy_map(knight_map, tmp_map);
}

int main() {
	cin >> l >> n >> q;
	for (int i = 1; i <= l; i++) {
		for (int j = 1; j <= l; j++) {
			cin >> map[i][j];
		}
	}
	int r, c, h, w, k;
	for (int i = 1; i <= n; i++) {
		cin >> r >> c >> h >> w >> k;
		init_hp[i] = k;
		knights[i] = { r,c,h ,w,k,0 };
		for (int k = r; k < r+h; k++) {
			for (int j = c; j <c+ w; j++) {
				knight_map[k][j] = i;
			}
		}
	}
	int a, b;
	for (int i = 0; i < q; i++) {
		cin >> a >> b;
		move_knight.push({ a,b });
	}
	
	while (!move_knight.empty()) {
		Move now = move_knight.front();
		move_knight.pop();
		bfs(now.knight_idx,now.dir);
	}
	int cnt=0;
	for (int i = 1; i <= n; i++) {
		if (knights[i].k > 0) {
			cnt += (init_hp[i] - knights[i].k);
		}
	}
	cout << cnt;
}