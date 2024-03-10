#include <iostream>
#include <set>
using namespace std;

int q, n, m,p;

struct Rabbit {
	int y, x;
	int id;
	long long d;
	int count;
	long long score;
};

struct YX {
	int y, x;
};

struct Cmp1 {
	bool operator()(Rabbit a, Rabbit b) const{
		if (a.count != b.count) {
			return a.count < b.count;
		}
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

struct Cmp2 {
	bool operator()(Rabbit a, Rabbit b) const{
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

set<Rabbit,Cmp1> rabbit1;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

void race(int k, int point) {
	long long cost[2001] = { 0 };
	int DAT[2001] = { 0 };
	set<Rabbit, Cmp2> rabbit2;
	set<Rabbit, Cmp1> tmp_rabbit;

	for (int i = 0; i < k; i++) {
		YX max_ = { 0,0 };
		int y = rabbit1.begin()->y;
		int x = rabbit1.begin()->x;
		int dist = rabbit1.begin()->d;
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i] * dist;
			int nx = x + dx[i] * dist;
			while(ny<1 || nx<1 || ny>n || nx>m){
				if ( ny > n) {
					ny = 2 * n - ny;
				}
				if (nx>m) {
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
					if (nx > max_.x){
						max_ = { ny,nx };
					}
				}
			}
		}

		for (auto tmp : rabbit1) {
			if (tmp.id != rabbit1.begin()->id) {
				cost[tmp.id] += max_.x + max_.y;
			}
		}
		if (DAT[rabbit1.begin()->id] = 1) {
			rabbit2.erase({ rabbit1.begin()->y,rabbit1.begin()->x
				,rabbit1.begin()->id ,rabbit1.begin()->d,rabbit1.begin()->count,
				rabbit1.begin()->score });
		}
		rabbit2.insert({ max_.y,max_.x
		,rabbit1.begin()->id ,rabbit1.begin()->d,rabbit1.begin()->count,
		rabbit1.begin()->score });
		int tmp_y = rabbit1.begin()->y;
		int tmp_x = rabbit1.begin()->x;
		rabbit1.insert({ max_.y,max_.x
				,rabbit1.begin()->id ,rabbit1.begin()->d,rabbit1.begin()->count+1,
				rabbit1.begin()->score });
		rabbit1.erase({ tmp_y, tmp_x
				,rabbit1.begin()->id ,rabbit1.begin()->d,rabbit1.begin()->count,
				rabbit1.begin()->score });

		DAT[rabbit1.begin()->id] = 1;
	}
	cost[rabbit2.begin()->id] += point;
	for (auto tmp : rabbit1) {
		tmp_rabbit.insert({ tmp.y,tmp.x,tmp.id ,tmp.d,tmp.count,tmp.score + cost[tmp.id] });

	}
	rabbit1.clear();
	for (auto tmp : tmp_rabbit) {
		rabbit1.insert({ tmp.y,tmp.x,tmp.id ,tmp.d,tmp.count,tmp.score });
	}
}

void change(int id, int l) {
	set<Rabbit, Cmp1> tmp_rabbit;
	for (set<Rabbit>::iterator i = rabbit1.begin(); i != rabbit1.end();i++) {
		if (i->id== id) {
			tmp_rabbit.insert({ i->y,i->x,i->id ,(i->d)*l,i->count,i->score});
			rabbit1.erase({ i->y,i->x,i->id ,i->d,i->count,i->score });
			break;
		}
	}
	rabbit1.insert({ tmp_rabbit.begin()->y,tmp_rabbit.begin()->x ,tmp_rabbit.begin()->id ,
		tmp_rabbit.begin()->d ,tmp_rabbit.begin()->count ,tmp_rabbit.begin()->score });
}

void find_king() {
	int max_num = 0;
	for (auto tmp : rabbit1) {
		if (tmp.score > max_num) {
			max_num = tmp.score;
		}
	}
	cout << max_num;
}

int main() {
	cin >> q;
	int query;
	int a, b;
	for (int i = 0; i < q; i++) {
		cin >> query;
		if(query==100){
			cin >> n >> m >> p;
			for (int j = 0; j < p; j++) {
				cin >> a >> b;
				rabbit1.insert({ 1,1,a,b,0,0 });
			}
			
		}
		else if (query == 200) {
			cin>> a>> b;


			race(a,b);
		}
		else if (query == 300) {
			cin >> a >> b;
			change(a, b);
		}

		else if (query == 400) {
			find_king();
		}
	}
	int de = -1;
}