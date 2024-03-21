#include <iostream>
using namespace std;

int n, l;
int map[101][101];

bool check_row(int num) {
	int ca = l - 1;
	int flag = 0;
	for (int i = 0; i < n - 1; i++) {
		if (map[num][i + 1] != map[num][i]) {
			if (abs(map[num][i + 1] - map[num][i]) > 1) {
				return 0;
			}
			if (map[num][i + 1] > map[num][i]) {
				if (flag == 1 || flag == 0) {
					if (ca > 0) {
						return 0;
					}

				}
				else if (flag == 2) {
					if (ca > -l) {
						return 0;
					}
				}
				flag = 1;
				ca = l;
			}
			else if (map[num][i + 1] < map[num][i]) {
				if (flag == 2) {
					if (ca > 0) {
						return 0;
					}
				}
				flag = 2;
				ca = l;
			}
		}
		ca--;
	}

	if (flag == 2 && ca > 0) {
		return 0;
	}
	

	return 1;
}

bool check_col(int num) {
	int ca = l-1;
	int flag = 0;
	for (int i = 0; i < n - 1; i++) {
		if (map[i + 1][num] != map[i][num]) {
			if (abs(map[i + 1][num] - map[i][num]) > 1) {
				return 0;
			}
			if (map[i + 1][num] > map[i][num]) {
				if (flag == 1 || flag == 0) {
					if (ca > 0) {
						return 0;
					}
				}
				else if (flag == 2) {
					if (ca > -l) {
						return 0;
					}
				}
		
				flag = 1;
				ca = l;
			}

			if (map[i + 1][num] < map[i][num]) {
				if (flag == 2 ) {
					if (ca > 0) {
						return 0;
					}
				}
	
				flag = 2;
				ca = l;
			}
		}
		ca--;
	}

	if (flag == 2 && ca > 0) {
		return 0;
	}
	return 1;
}


int main() {
	cin >> n >> l;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
	int cnt = 0;
	int cnt2 = 0;
	for (int i = 0; i < n; i++) {
		if (check_row(i)) {  cnt++; }

		if (check_col(i)) {  cnt++; }
	}

	cout << cnt;

}
