#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Player {
	int y, x;
	int dir;
	int ability;
	int gun;
	int score;
};

vector<Player> player;

struct Cmp {
	bool operator()(int a, int b) {
		return a < b;
	}
};

int n, m, k;
priority_queue<int,vector<int>,Cmp> map[23][23];
int	player_map[23][23];

int dy[4] = { -1,0,1,0 };
int dx[4] = { 0,1,0,-1 };

int move_player(int idx) { //player 이동
	int ny = player[idx].y + dy[player[idx].dir];
	int nx = player[idx].x + dx[player[idx].dir];
	if (ny<1 || nx<1 || ny>n || nx>n) {
		player[idx].dir = (player[idx].dir + 2) % 4;
		ny = player[idx].y + dy[player[idx].dir];
		nx = player[idx].x + dx[player[idx].dir];
	}

	player_map[player[idx].y][player[idx].x] = 0;
	player[idx].y = ny;
	player[idx].x = nx;
	if (player_map[ny][nx] != 0) {
		return player_map[ny][nx];
	}
	else{
		player_map[ny][nx] = idx;
		int max_gun = 0;
		if(!map[ny][nx].empty()){
			max_gun = map[ny][nx].top();
			if (max_gun > player[idx].gun) {
				map[ny][nx].pop();
				if (player[idx].gun != 0) {
					map[ny][nx].push(player[idx].gun);
				}
				player[idx].gun = max_gun;
			}
		}
		
		return 0;
	}
}

void player_win(int win, int lose) {
	int player1_pow = player[win].ability + player[win].gun;
	int player2_pow = player[lose].ability + player[lose].gun;

	player_map[player[win].y][player[win].x] = win;
	player[win].score += player1_pow - player2_pow;

	if (player[lose].gun != 0) {
		map[player[win].y][player[win].x].push(player[lose].gun);
		player[lose].gun = 0;
	}

	int max_gun = 0;
	if (!map[player[win].y][player[win].x].empty()) {
		max_gun = map[player[win].y][player[win].x].top();
		if (max_gun > player[win].gun) {
			map[player[win].y][player[win].x].pop();

			if (player[win].gun != 0) {
				map[player[win].y][player[win].x].push(player[win].gun);
			}
			player[win].gun = max_gun;
		}
	}
	
	int ny = -1;
	int nx = -1;
	for(int i =0; i<4; i++){
		ny = player[lose].y + dy[(player[lose].dir + i) % 4];
		nx = player[lose].x + dx[(player[lose].dir + i) % 4];
		if (ny > n || nx > n || ny < 1 || nx < 1) { continue; }
		if (player_map[ny][nx] == 0) {
			player[lose].dir = (player[lose].dir + i) % 4;
			break;
		}
	}
	player_map[ny][nx] = lose;
	player[lose].y = ny;
	player[lose].x = nx;


	max_gun = 0;
	if (!map[ny][nx].empty()) {
		max_gun = map[ny][nx].top();
		if (max_gun > player[lose].gun) {
			map[ny][nx].pop();

			if (player[lose].gun != 0) {
				map[ny][nx].push(player[lose].gun);
			}
			player[lose].gun = max_gun;
		}
	}
}

void fight(int player1, int player2) {
	int player1_pow = player[player1].ability + player[player1].gun;
	int player2_pow = player[player2].ability + player[player2].gun;

	if (player1_pow > player2_pow) {
		player_win(player1, player2);
	}
	else if (player1_pow < player2_pow) {
		player_win(player2, player1);
	}
	else {
		if (player[player1].ability > player[player2].ability) {
			player_win(player1, player2);
		}
		else {
			player_win(player2, player1);

		}
	}
}

int main() {
	cin >> n >> m >> k;

	player.push_back({ 0 });
	int gu;
	for (int i = 1; i <=n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> gu;
			map[i][j].push(gu);
		}
	}

	int h_y, h_x, h_d, h_a;
	for (int i = 1; i <=m; i++) {
		cin >> h_y >> h_x >> h_d >> h_a;
		player.push_back({ h_y,h_x,h_d,h_a,0,0 });
		player_map[h_y][h_x] = i;
	}

	for (int i = 0; i < k; i++) {
		for (int j = 1; j <= m; j++) {
			int is_fight=move_player(j);
			if (is_fight != 0) {
				fight(j, is_fight);
			}
		}
	}
	for (int i = 1; i <= m; i++) {
		cout << player[i].score << " ";
	}
}