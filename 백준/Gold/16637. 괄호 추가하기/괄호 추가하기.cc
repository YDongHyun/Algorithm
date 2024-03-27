#include <iostream>
using namespace std;

int n;

char inp[25];


int visited[20];

int visited2[11];

int max_ = -21e8;

void dfs(int num, int sum, char cal) {
	if (n == 1) {
		if (inp[num]-'0' > max_) {
			max_ = inp[num]-'0';
		}
		return;
	}

	if (num >= n-1) {
		int sol=0;
		if (cal == '+') {
			sol = sum + (inp[num] - '0');
		}
		else if (cal == '-') {
			sol = sum - (inp[num] - '0');
		}
		else if (cal == '*') {
			sol = sum * (inp[num] - '0');
		}
		else if (cal == '/') {
			sol = sum / (inp[num] - '0');
		}
		else {
			sol = sum;
		}

		if (sol > max_) {
			max_ = sol;
		}
		
		
		return;
	}
	
	for (int i = 0; i <= 1; i++) {
		if (i == 0) {
			if (cal == '+') {
				dfs(num + 2, sum + (inp[num] - '0'), inp[num +  1]);
			}
			else if (cal == '-') {
				dfs(num + 2, sum - (inp[num] - '0'), inp[num + 1]);
			}
			else if (cal == '*') {
				dfs(num + 2, sum*(inp[num] - '0'), inp[num + 1]);
			}
			else if (cal == '/') {
				dfs(num + 2, sum/(inp[num] - '0'), inp[num + 1]);
			}
			else{
				dfs(num + 2, inp[num]-'0', inp[num + 1]);
			}
		}
		if (i == 1) {
			if (cal == '+') {
				if (inp[num + i] == '+') {
					dfs(num + 4, sum + ((inp[num] - '0') + (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '-') {
					dfs(num + 4, sum + ((inp[num] - '0') - (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '*') {
					dfs(num + 4, sum + ((inp[num] - '0') * (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '/') {
					dfs(num + 4, sum + ((inp[num] - '0') / (inp[num + 2] - '0')), inp[num + 3]);
				}
			}
			else if (cal == '-') {
				if (inp[num + i] == '+') {
					dfs(num + 4, sum - ((inp[num] - '0') + (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '-') {
					dfs(num + 4, sum - ((inp[num] - '0') - (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '*') {
					dfs(num + 4, sum - ((inp[num] - '0') * (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '/') {
					dfs(num + 4, sum - ((inp[num] - '0') / (inp[num + 2] - '0')), inp[num + 3]);
				}
			}
			else if (cal == '*') {
				if (inp[num + i] == '+') {
					dfs(num + 4, sum * ((inp[num ] - '0') + (inp[num+2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '-') {
					dfs(num + 4, sum * ((inp[num ] - '0') - (inp[num+2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '*') {
					dfs(num + 4, sum * ((inp[num] - '0') * (inp[num+2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '/') {
					dfs(num + 4, sum * ((inp[num] - '0') / (inp[num+2] - '0')), inp[num + 3]);
				}
			}
			else if (cal == '/') {
				if (inp[num + i] == '+') {
					dfs(num + 4, sum/((inp[num ] - '0') + (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '-') {
					dfs(num + 4, sum / ((inp[num] - '0') - (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '*') {
					dfs(num + 4, sum /((inp[num] - '0') * (inp[num + 2] - '0')), inp[num + 3]);
				}
				else if (inp[num + i] == '/') {
					dfs(num + 4, sum / ((inp[num] - '0') / (inp[num + 2] - '0')), inp[num + 3]);
				}
			}
			else {
				if (inp[num + i] == '+') {
					dfs(num + 4, (inp[num]-'0') + (inp[num + 2] - '0'), inp[num + 3]);
				}
				else if (inp[num + i] == '-') {
					dfs(num + 4, (inp[num] - '0') - (inp[num + 2] - '0'), inp[num + 3]);
				}
				else if (inp[num + i] == '*') {
					dfs(num + 4, (inp[num] - '0') * (inp[num + 2] - '0'), inp[num + 3]);
				}
				else if (inp[num + i] == '/') {
					dfs(num + 4, (inp[num] - '0') / (inp[num + 2] - '0'), inp[num + 3]);
				}
			}
		}
	}
}

int main() {
	cin >> n;
	cin >> inp;

	dfs(0,0,' ');

	cout << max_;
}