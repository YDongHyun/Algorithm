#include <iostream>
#include <algorithm>
using namespace std;

int n;
int dp[16];
int t[16];
int p[16];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> t[i] >> p[i];
	}
	int max_ = 0;
	for (int i = 0; i <= n; i++) {
		dp[i] = max(max_, dp[i]);
		if (i + t[i] <= n){
			dp[i + t[i]] = max(dp[i] + p[i], dp[i+t[i]]);
		}
		max_ = max(max_, dp[i]);
	}
	cout << dp[n];

}