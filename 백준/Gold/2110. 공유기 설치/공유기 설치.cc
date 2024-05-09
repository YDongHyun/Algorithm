#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <algorithm>

int map[200010];
int n, c;

bool is_val(int mid) {
	int cnt = 1;
	int now = 1;
	for (int i = 1; i <= n; i++) {
		if (map[i] - map[now] >= mid) {
			cnt++;
			now = i;
	
		}
	}

	if (cnt >= c) {
		return 1;
	}
	else {
		return 0;
	}

}

int bs(int st, int en) {
	int mid = 0;
	int upper = 0;
	while (st <= en) {
		mid = (st + en) / 2;
		if (is_val(mid)) {
			upper = mid;
			st = mid+1;
		}
		else {
			en = mid-1;
		}
	}
	return upper;
}

int main() {
	scanf("%d %d", &n, &c);

	for (int i = 1; i <= n; i++) {
		scanf("%d", &map[i]);
	}
	std::sort(map,map+n+1);

	printf("%d\n",bs(0, 1000000000));

}