#include <iostream>
#include <stdio.h>
#include <algorithm>
using namespace std;

int n;

int dp[1500001];

int main() {
	cin >> n;

	int t, p;
	int max_=0;

	for (int i = 0; i <n; i++) {
		dp[i] = max(max_, dp[i]);
		scanf("%d %d",&t,&p);
		if(i+t<=n){
			dp[i + t] = max(dp[i + t], dp[i]+p);
		}
		max_ = max(max_, dp[i]);
	}
	cout << max(dp[n],dp[n-1]);
}