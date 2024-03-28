#include <iostream>
#include<stdio.h>
#include <queue>
using namespace std;

struct YX {
	int st, en;
	bool operator<(YX a)const {
		return st > a.st;
	}

};

int n;
priority_queue <YX> pq;

int main() {
	cin >> n;
	int a, b;
	for (int i = 0; i < n; i ++ ) {
		scanf("%d %d", &a, &b);
		pq.push({ a, b });
	}

	int sum = 0;
	int r = -21e8;
	int l = -21e8;
	while (!pq.empty()) {
		YX now = pq.top();
		pq.pop();
		if (r < now.st) {
			sum += r - l;
			l = now.st;
			r = now.en;
		}
		else {
			if (r < now.en) {
				r = now.en;
			}
		}
	}
	sum += r - l;
	cout << sum;
}

