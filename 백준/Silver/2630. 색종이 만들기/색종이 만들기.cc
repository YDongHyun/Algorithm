#include <iostream>
using namespace std;

int n;
int map[129][129];
int blue;
int white;
void cutting(int y, int x, int num) {
	if (num == 1) {
		if (map[y][x] == 0) {
			white++;
		}
		else {
			blue++;
		}
		return;
	}
	int tmp = map[y][x];
	for (int i = y; i < y + num; i++) {
		for (int j = x; j < x + num; j++) {
			if (map[i][j] != tmp) {
				num /= 2;
				cutting(y, x, num);
				cutting(y, x+num, num);
				cutting(y+num, x, num);
				cutting(y+num, x+num, num);
				num *= 2;
				return;
			}
		}
	}
	if (tmp == 0) {
		white++;
	}
	else {
		blue++;
	}
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	cutting(0, 0, n);
	cout << white << "\n" << blue << "\n";
}