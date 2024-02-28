#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

struct Cell {
	int y, x;
	int sleep;
	int act;
	int sep;
};

bool cmp(Cell a, Cell b) {
	return a.act > b.act;
}

int t,n, m, k;
int visited[1001][1001];

vector<Cell> cell;
vector<Cell> tmp_cell;

int dy[4] = { -1,1,0,0 };
int dx[4] = { 0,0, - 1,1 };

int main() {
	cin >> t;
	for(int tc=1; tc<=t; tc++){
		cin >> n >> m >> k;
		int a;
		for (int i = 450; i <450+ n; i++) {
			for (int j =450; j <450+ m; j++) {
				cin >> a;
				if (a == 0) { continue; }
				cell.push_back({ i,j,a,a ,0});
				visited[i][j] = 1;
			}
		}

		for (int i = 1; i <=k; i++) {
			sort(cell.begin(), cell.end(), cmp);
			for (int j = 0; j < cell.size(); j++) {
				if (cell[j].act == 0) {continue;}
				if (cell[j].sleep != 0) { cell[j].sleep--; continue; }
				if (cell[j].sep == 0 && cell[j].act>0) {
					cell[j].sep = 1;
					for (int dir = 0; dir < 4; dir++) {
						int ny = cell[j].y + dy[dir];
						int nx = cell[j].x + dx[dir];
						if (visited[ny][nx] == 0) {
							visited[ny][nx] = 1;
							tmp_cell.push_back({ ny,nx,cell[j].act,cell[j].act,0});
						}
					}
				}
				cell[j].act--;
			}
			for (int j = cell.size() - 1; j >= 0; j--) {
				if (cell[j].act == 0) {
					cell.erase(cell.begin() + j);
				}
			}
			cell.insert(cell.end(), tmp_cell.begin(), tmp_cell.end());
			tmp_cell.clear();
		}
		cout <<"#"<<tc<<" "<<cell.size() << "\n";
		cell.clear();
		memset(visited, 0, sizeof(visited));
	}
}