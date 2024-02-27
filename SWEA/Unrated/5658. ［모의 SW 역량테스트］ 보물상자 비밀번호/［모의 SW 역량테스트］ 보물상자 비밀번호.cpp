#include <iostream>
#include <set>
#include <string>
#include <cmath>
using namespace std;

int t, n, k;
string a;


int main() {

	cin >> t;
	for(int tc=1;tc<=t; tc++){
	cin >> n >> k;
	cin >> a;
	set<string> se;
	int length_ = n / 4;
	string tmp;
	string tmp_2;


	for (int j = 0; j < length_+1; j++) {
		tmp_2 = a[n-1];
		if(j!=0){
			a.insert(0, tmp_2);
			a.erase(n, 1);
		}
		//a.replace(n-1, n-1, 1, tmp_2);
		for (int i = 0; i <n-length_+1; i++) {
			tmp=a.substr(i, length_);
			se.insert(tmp);
		}
	}
	int cnt = 0;
	string sol16;
	for (auto Idx : se) {
		if (cnt == se.size() - k) {
			sol16= Idx;
			break;
		}
		cnt++;
	}
	int sum=0;
	int idx = 0;
	for(int i =n/4-1; i>=0; i--){
		if(sol16[idx]>=48 && sol16[idx]<=57){
			sum+=(sol16[idx]-'0')*pow(16, i);
		}
		else {
			sum +=(sol16[idx] - 'A'+10) * pow(16, i);
		}
		idx++;
	}
	cout <<"#"<<tc<<" "<< sum<<"\n";
	}
}