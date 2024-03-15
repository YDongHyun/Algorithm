#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n, m, k;
typedef long long int ll; 

ll tree[4000000];

void update(int left, int right, int node, int idx, ll value) {
	if (left > idx || right < idx) { return; }
	if (left == right) { tree[node] = value; return; }
	int mid = (left + right) / 2;

	update(left, mid, node * 2, idx, value);
	update(mid+1, right, node * 2+1,idx, value);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll getsum(int left, int right,int a, int b, int node) {
	if (left > b || right < a) { return 0; }
	if (left >= a && right <= b) { return tree[node]; }
	int mid = (left + right) / 2;
	return getsum(left, mid, a, b, node * 2)+getsum(mid+1,right,a,b,node*2+1);
}


int main() {
	scanf("%d %d %d", &n, &m, &k);
	int num1,num2;
	ll num3;
	for (int i = 1; i <=n; i++) {
		scanf("%lld", &num3);
		update(1, n,1, i, num3);
	}

	int query;
	for(int i= 0; i<m+k; i++){
		scanf("%d", &query);
		if (query == 1) {
			scanf("%d %lld", &num1, &num3);
			update(1, n, 1, num1, num3);
		}
		else {
			scanf("%d %d", &num1, &num2);
			printf("%lld \n", getsum(1, n, num1, num2, 1));
		}
	}
}