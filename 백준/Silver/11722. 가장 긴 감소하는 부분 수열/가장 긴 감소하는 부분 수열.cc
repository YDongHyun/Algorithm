#include <iostream>
#include <algorithm>
using namespace std;

int n;

int dp[1001];
int in[1001];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> in[i];
	}
	for(int j=0; j<n; j++){
		dp[j] = max(dp[j],1);
		for (int i =j; i < n; i++) {
			if (in[j] > in[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}
	
	int max_=0;
	for (int i = 0; i <= n; i++) {
		max_ = max(max_, dp[i]);
	}

	cout << max_;
}