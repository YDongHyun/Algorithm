#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct YX {
	int y, x;
};

struct Train {
	YX head;
	int dir;
	int length;
	YX tail;
};

int score;

int n, m, k;

int map[22][22];
YX train_map[22][22];
int visited[22][22];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,-1,0,1 };

vector<Train> team;
vector<YX> head_tmp;


void find_train(YX yx) {
	memset(visited, 0, sizeof(visited));
	int train_length = 1;
	int init_dir = 0;
	YX tmp_tail = { 0 };
	queue<YX> q;
	q.push(yx);
	visited[yx.y][yx.x] = 1;
	while (!q.empty()) {
		YX now = q.front();
		q.pop();
		int flag = 0;
		for(int i=0; i<4; i++){
			int ny = now.y + dy[i];
			int nx = now.x + dx[i];
			if (ny > n || nx > n || ny < 1 || nx < 1) { continue; }
			if (visited[ny][nx]) { continue; }
			visited[ny][nx] = 1;
			if (map[ny][nx] == 2) {
				if (map[now.y][now.x] == 1) {
					init_dir = i;
					flag = 1;
				}

				train_length++;
				q.push({ ny,nx });
			}
			if (map[ny][nx] == 3) {
				if (map[now.y][now.x] == 1 && !flag) {
					init_dir = i;
				}

				tmp_tail = { ny,nx };
				train_length++;
			}
		}
		
	}
	team.push_back({ yx,init_dir,train_length,tmp_tail });

}


void map_init() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <=n; j++) {
			if (map[i][j] == 2 || map[i][j] == 3 || map[i][j]==1) {
				map[i][j] = 4;
			}
		}
	}
}


void draw_train_map(int idx) {
	memset(visited, 0, sizeof(visited));
	Train now = team[idx];
	//visited[now.head.y][now.head.x] = 1;
	for (int i = 1; i <= now.length; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == 1 &&  j == now.dir) { continue; }
			if (i==2) {
				if (now.length == 2) {
					team[idx].tail = { now.head.y,now.head.x };
				}
				visited[now.head.y][now.head.x] = 1; 
				train_map[now.head.y][now.head.x] = { idx,i };
				break;
			}
			int ny = now.head.y + dy[j];
			int nx = now.head.x + dx[j];
			if (ny<1 || nx <1 || ny>n || nx>n) { continue; }
			if (visited[ny][nx]) { continue; }
			if (map[ny][nx] == 4) {
				visited[ny][nx] = 1;
				if (i == 1) {
					team[idx].dir = (j + 2) % 4;
					train_map[ny][nx] = { idx,i };
					team[idx].head = { ny,nx };
					break;
				}

				if (i == now.length) {
					team[idx].tail = { ny,nx };
				}
				//now.dir = (i + 2) % 4;
				train_map[ny][nx] = { idx,i };
				now.head = { ny,nx };
				break;

			}
		}
	}
}

YX throw_ball(int round) {
	int mode = (round / n)%n;
	int number = round % n;
	if (mode == 0) {
		for (int i = 1; i <= n; i++) {
			if (train_map[number][i].y != 0 || train_map[number][i].x != 0) {
				return train_map[number][i];
			}
		}
	}
	
	else if (mode == 1) {
		for (int i = n; i >=1; i--) {
			if (train_map[i][number].y != 0 || train_map[i][number].x != 0) {
				return train_map[i][number];
			}
		}
	}

	else if (mode == 2) {
		for (int i = n; i >= 1; i--) {
			if (train_map[number][i].y != 0 || train_map[number][i].x != 0) {
				return train_map[number][i];
			}
		}

	}

	else if (mode == 3) {
		for (int i = 1; i <= n; i++) {
			if (train_map[i][number].y != 0 || train_map[i][number].x != 0) {
				return train_map[i][number];
			}
		}
	}
	return { 0,0 };
}

void find_dir(int idx) {
	Train now = team[idx];
	for (int i = 0; i < 4; i++) {
		int ny = now.head.y + dy[i];
		int nx = now.head.x + dx[i];
		if (ny<1 || nx <1 || ny>n || nx>n) { continue; }
		if (train_map[ny][nx].x == now.length - 1) {
			team[idx].dir = i;
			return;
		}
	}
}

int main() {
	cin >> n >> m >> k;
	
	for (int i = 1; i <=n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
			if (map[i][j] == 1) {
				head_tmp.push_back({ i,j });
			}
		}
	}

	for (int i = 0; i < m; i++) {
		find_train(head_tmp[i]);
	}
	map_init();

	for (int round = 1; round <=k; round++) {
		memset(train_map, 0, sizeof(train_map));
		for (int i = 0; i < m; i++) {;
			draw_train_map(i);
		}

	

		YX team_idx = throw_ball(round);
		if (team_idx.y == 0 && team_idx.x == 0) {
			continue;
		}

		YX tmp = team[team_idx.y].head;
		team[team_idx.y].head = team[team_idx.y].tail;
		team[team_idx.y].tail = tmp;
		find_dir(team_idx.y);

		score += team_idx.x * team_idx.x;

	}
	cout << score;
	int de = -1;
}