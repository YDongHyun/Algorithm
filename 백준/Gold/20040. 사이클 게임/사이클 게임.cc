#include <iostream>
using namespace std;

int n, m;
int arr[500001];

void init(int n) {
	for (int i = 0; i <=n; i++) {
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
	init(n);
	int a, b;
	int end = 0;
	int flag = 0;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		if (find(a) == find(b)) {
			if (flag) { continue; }
			end = i + 1;
			flag = 1;
		}
		union_(a, b);
	}
	cout << end;
}
