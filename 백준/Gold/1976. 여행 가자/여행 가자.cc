#include <iostream>
using namespace std;

int n, m;
int arr[201];
int tmp[1001];
int map[201][201];

void init() {
	for (int i = 0; i <201; i++) {
		arr[i] = i;
	}
}

int find(int tar) {
	if (tar == arr[tar]) { return tar; }
	int ret = find(arr[tar]);
	arr[tar] = ret;
	return ret;
}

void union_(int a, int b) {
	int t1 = find(a);
	int t2 = find(b);
	if (t1 == t2) { return; }
	arr[t2] = t1;
}

int main() {
	cin >> n >> m;
	init();
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cin >> map[i][j];
		}
	}
	
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			if (map[i][j] == 0) { continue; }
			union_(i, j);
		}
	}
	int a;
	for (int i = 0; i < m; i++) {
		cin >> tmp[i];
	}
	for (int i = 1; i < m; i++) {
		if (find(tmp[0]) != find(tmp[i])) { cout << "NO"; return 0; }
	}
	
	cout << "YES";

}
