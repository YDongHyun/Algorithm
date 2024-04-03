#include <iostream>
#include <vector>
using namespace std;

int n;

int LIS[1000001];

int bs(int st, int en,int ipt) {
	int mid = 0;
	while (st <= en) {
		mid = (st + en)/2;
		if (LIS[mid] >= ipt) {
			//if (ipt == LIS[mid]) { break; }
			en = mid -1;
		}
		else {
			st = mid+1;
		}
	}
	return st;
}

int main() {
	cin >> n;
	int data;
	int cnt = 0;
	for(int i=0; i<n; i++){
		cin >> data;
		int idx=bs(0,cnt, data);

		if (idx != -1) {
			if (LIS[idx] == 0) {
				cnt++;
			}
			LIS[idx] = data;
		}
		if (data < LIS[0]) {
			LIS[0] = data;
		}
		
	}
	cout << cnt;
}