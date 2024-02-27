#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

struct BC {
	int y, x;
	int distance;
	int power;
};

struct Human {
	int y, x;
	int charge;
};

struct Power {
	int cost;
	int idx;
};

int dy[5] = { 0,-1,0,1,0 };
int dx[5] = { 0,0,1,0,-1 };

vector<BC> bc;
Human h1;
Human h2;

bool cmp(BC a, BC b) {
	return a.power > b.power;
}

bool cmp2(Power a, Power b) {
	return a.cost > b.cost;
}

queue<int> h1_move;
queue<int> h2_move;

Power DAT_h1[9];
Power DAT_h2[9];
int tmp_cost[9];

int t, m, a;

void bc_find(Human a,int mode) {
	int dist = 0;
	for (int i = 0; i < bc.size(); i++) {
		dist = abs(a.y - bc[i].y) + abs(a.x - bc[i].x);
		if (dist <= bc[i].distance) {
			if (mode == 1) {
				DAT_h1[i] = { bc[i].power,i };
			}
			else {
				DAT_h2[i] = {bc[i].power, i};
			}
		}
	}
}

void move_func(Human *a, int dir) {
	a->y += dy[dir];
	a->x += dx[dir];
}

int main() {
	cin >> t;
	for(int tc=1; tc<=t; tc++){
	cin >> m >> a;
	int move_tmp;

	h1 = { 1,1,0 };
	h2 = { 10,10,0 };
	h1_move.push(0);
	h2_move.push(0);
	for (int i = 0; i < m; i++) {
		cin >> move_tmp;
		h1_move.push(move_tmp);
	}
	for (int i = 0; i < m; i++) {
		cin >> move_tmp;
		h2_move.push(move_tmp);
	}
	
	int bc1, bc2, bc3, bc4;
	for (int i = 0; i < a; i++) {
		cin >> bc2 >> bc1 >> bc3 >> bc4;
		bc.push_back({ bc1,bc2,bc3,bc4 });
	}
	int cnt = 0;
	while (!h1_move.empty()) {
		
		int h1_mo = h1_move.front();
		int h2_mo = h2_move.front();
		h1_move.pop();
		h2_move.pop();
		move_func(&h1, h1_mo);
		move_func(&h2, h2_mo);
		bc_find(h1, 1);
		bc_find(h2, 2);
	
		sort(DAT_h1, DAT_h1 + a, cmp2);
		sort(DAT_h2, DAT_h2 + a, cmp2);
		if (DAT_h1[0].idx == DAT_h2[0].idx) {
			if (DAT_h1[0].cost + DAT_h2[1].cost < DAT_h1[1].cost + DAT_h2[0].cost) {
				h1.charge += DAT_h1[1].cost;
				h2.charge += DAT_h2[0].cost;
			}
			else {
				h1.charge += DAT_h1[0].cost;
				h2.charge += DAT_h2[1].cost;
			}
		}
		else{
			h1.charge += DAT_h1[0].cost;
			h2.charge += DAT_h2[0].cost;
		}
		memset(DAT_h1, 0, sizeof(DAT_h1));
		memset(DAT_h2, 0, sizeof(DAT_h2));

		cnt++;
	}

	cout <<"#"<<tc<<" "<< h1.charge + h2.charge << "\n";
	bc.clear();
	}
}
