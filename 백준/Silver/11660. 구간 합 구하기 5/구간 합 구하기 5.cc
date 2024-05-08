#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int map[1025][1025];
int n, m;



int main() {
	scanf("%d %d",&n,&m);
	int tmp = 0;
	for (int i = 1; i <=n; i++) {
		for (int j = 1; j <=n; j++) {
			scanf("%d", &tmp);
			map[i][j] = map[i][j - 1] + tmp;
		}
	}
	int x1, x2, y1, y2;
	for (int i = 0; i < m; i++) {
		int sol = 0;
		scanf("%d %d %d %d", &y1, &x1, &y2, &x2);

		for (int k = y1; k <= y2; k++) {
			sol += map[k][x2] - map[k][x1 - 1];
		}
		printf("%d\n", sol);
		
	}

	
}