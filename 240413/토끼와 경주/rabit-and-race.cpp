#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

struct Rabbit {
	int y, x;
	int dist;
	int count;
	int now_count;
	int score;
};

int query;
int q;
int n, m, p;
int id, ipt_dist;
int k, s;

int last_sum_score;

unordered_map<int,Rabbit> rabbit;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0,-1,1 };

int find_first() {
	int max_id = rabbit.begin()->first;
	for (unordered_map<int, Rabbit>::iterator i = rabbit.begin(); i != rabbit.end(); i++) {
		if (i->second.count == rabbit[max_id].count) {
			if (i->second.y + i->second.x == rabbit[max_id].y + rabbit[max_id].x) {
				if (i->second.y == rabbit[max_id].y) {
					if (i->second.x == rabbit[max_id].x) {
						if (i->first < max_id) {
							max_id = i->first;
						}
					}
					else if (i->second.x < rabbit[max_id].x) {
						max_id = i->first;
					}
				}
				else if (i->second.y < rabbit[max_id].y) {
					max_id = i->first;
				}
			}
			else if (i->second.y + i->second.x < rabbit[max_id].y + rabbit[max_id].x) {
				max_id = i->first;
			}
		}
		else if (i->second.count < rabbit[max_id].count) {
				max_id = i->first;
		}
	}
	return max_id;
}

void move_first(int id) {
	Rabbit now = rabbit[id];
	rabbit[id].count++;
	rabbit[id].now_count++;
	pair<int, int> YX = { -1,-1 };
	for (int i = 0; i < 4; i++) {
		int ny = now.y + dy[i] * (now.dist%(2*(n-1)));
		int nx = now.x + dx[i] * (now.dist % (2 * (m - 1)));
		if(ny<1 || nx<1 || ny>n || nx>m){
			if (i == 0 || i == 1) {
				if (ny <= 0) {
					ny = ny+abs(ny) + 1;
				}
				int mu = ny / n;
				int ma = ny % n;
				if (mu == 1) {
					ny = n - (mu + ma) + 1;
				}
				else {
					ny = mu + ma;
				}
			}
			else{
				if (nx <= 0) {
					nx = nx+abs(nx) + 1;
				}
				int mu = nx / m;
				int ma = nx % m;
				if (mu == 1) {
					nx = m - (mu + ma) + 1;
				}
				else {
					nx = mu + ma;
				}
			}
		}
		if (ny + nx == YX.first + YX.second) {
			if (ny == YX.first) {
				if (nx > YX.first) {
					YX = { ny,nx };
				}
			}
			else if (ny > YX.first) {
				YX = { ny,nx };
			}
		}
		else if (ny + nx > YX.first + YX.second){
			YX = { ny,nx };
		}
	}
	//cout << id << " " << YX.first << " " << YX.second << "\n";
	last_sum_score += YX.first + YX.second;
	rabbit[id].score -= YX.first + YX.second;
	rabbit[id].y = YX.first;
	rabbit[id].x = YX.second;
}

int find_last() {
	int max_id = -1;

	for (unordered_map<int, Rabbit>::iterator i = rabbit.begin(); i != rabbit.end(); i++) {
		if (max_id == -1 && i->second.now_count > 0) {
			max_id = i->first;
			i->second.now_count = 0;
		}
		if (max_id != -1 && i->second.now_count > 0) {
			i->second.now_count = 0;
			if (rabbit[max_id].y + rabbit[max_id].x == i->second.y + i->second.x) {
				if (rabbit[max_id].y == i->second.y) {
					if (rabbit[max_id].x == i->second.x) {
						if (max_id < i->first) {
							max_id = i->first;
						}
					}
					else if (rabbit[max_id].x < i->second.x) {
						max_id = i->first;
					}
				}
				else if (rabbit[max_id].y < i->second.y) {
					max_id = i->first;
				}
			}
			else if (rabbit[max_id].y + rabbit[max_id].x < i->second.y + i->second.x) {
				max_id = i->first;
			}
		}
	}
	return max_id;
}

void find_winner() {
	int max_score = -21e8;
	for (unordered_map<int, Rabbit>::iterator i = rabbit.begin(); i != rabbit.end(); i++) {
		if (i->second.score > max_score) {
			max_score = i->second.score;
		}
	}
	cout << max_score + last_sum_score;
}
int main() {
	cin >> q;
	for(int qu=0; qu<q; qu++){
		cin >> query;

		if (query == 100) {
			cin >> n >> m >> p;
			for (int i = 0; i < p; i++) {
				cin >> id >> ipt_dist;
				rabbit[id] = { 1,1,ipt_dist,0,0,0 };
			}
		}
		else if (query == 200) {
			cin >> k >> s;
			for(int i=0; i<k; i++){
				int first_id = find_first();
				//cout << "f_id : " << first_id << "\n";

				move_first(first_id);
			}
			int last_id = find_last();
			rabbit[last_id].score += s;
		}
		else if (query == 300) {
			cin >> id >> ipt_dist;
			rabbit[id].dist *= ipt_dist;
			//cout <<"dist:"<< rabbit[id].dist << "\n";
		}
		else {
			find_winner();
		}
	}
}