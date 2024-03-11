#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <map>
#include <queue>
#include <stdio.h>
using namespace std;

int q, n, m, p;

struct Rabbit {
	int y, x;
	int id;
	int count;
};

struct Info {
	int d;
	long long score;
};

struct YX {
	int y, x;
};

struct Cmp1 {
	bool operator()(Rabbit a, Rabbit b) const {
		if (a.count != b.count) {
			return a.count > b.count;
		}
		if (a.x + a.y != b.x + b.y) {
			return a.x + a.y > b.x + b.y;
		}
		if (a.y != b.y) {
			return a.y > b.y;
		}
		if (a.x != b.x) {
			return a.x > b.x;
		}
		return a.id > b.id;
	}
};

struct Cmp2 {
	bool operator()(Rabbit a, Rabbit b) const {
		if (a.x + a.y != b.x + b.y) {
			return a.x + a.y < b.x + b.y;
		}
		if (a.y != b.y) {
			return a.y < b.y;
		}
		if (a.x != b.x) {
			return a.x < b.x;
		}
		return a.id < b.id;
	}
};

priority_queue<Rabbit,vector<Rabbit>,Cmp1> rabbit1;
map<int, Info> info;
int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void race(int k, int point) {
	priority_queue<Rabbit, vector<Rabbit>, Cmp2> rabbit2;
	for (int i = 0; i < k; i++) {
		Rabbit now = rabbit1.top();
		rabbit1.pop();
		int dist = info[now.id].d;
		YX max_ = { 0,0 };
		for (int j = 0; j < 4; j++) {
			int ny = now.y + dy[j] * info[now.id].d;
			int nx = now.x + dx[j] * info[now.id].d;
			while (ny<1 || nx<1 || ny>n || nx>m) {
				if (ny > n) {
					ny = 2 * n - ny;
				}
				if (nx > m) {
					nx = 2 * m - nx;
				}
				if (ny < 1) {
					ny = 2 - ny;
				}
				if (nx < 1) {
					nx = 2 - nx;
				}
			}
			if (ny + nx > max_.x + max_.y) {
				max_ = { ny,nx };
			}
			if (ny + nx == max_.x + max_.y) {
				if (ny > max_.y) {
					max_ = { ny,nx };
				}
				else if (ny == max_.y) {
					if (nx > max_.x) {
						max_ = { ny,nx };
					}
				}
			}
		}
		for (map<int, Info>::iterator i = info.begin(); i!= info.end(); i++){
			if(i->first!=now.id){
				i->second.score += max_.y + max_.x;
			}
		}
		rabbit1.push({ max_.y, max_.x, now.id ,now.count + 1 });
		rabbit2.push({ max_.y, max_.x, now.id ,now.count + 1 });
	}
	info[rabbit2.top().id].score += point;
}

void change(int id, int l) {
	info[id].d *= l;
}

void find_king() {
	int max_ = 0;
	for (auto tmp : info) {
		if (tmp.second.score > max_) {
			max_ = tmp.second.score;
		}
	}
	cout << max_;
}

int main() {

	//freopen("input.txt", "r", stdin);
	cin >> q;
	int query;
	int a, b;
	for (int i = 0; i < q; i++) {
		scanf("%d",&query);
		if (query == 100) {
			scanf("%d %d %d",&n,&m,&p);
			for (int j = 0; j < p; j++) {
				scanf("%d %d", &a, &b);
				rabbit1.push({ 1,1,a,0 });
				info[a] = { b,0 };
			}
			int de = -1;
		}
		else if (query == 200) {
			scanf("%d %d", &a, &b);
			race(a, b);
		}
		else if (query == 300) {
			scanf("%d %d", &a, &b);
			change(a, b);
		}

		else if (query == 400) {
			find_king();
		}
	}
	int de = -1;
}