#include <iostream>
#include <cmath>
using namespace std;

int n, r, c;

void func(int y, int x, int length,int cnt) {
	if (y == r && x == c) {
		cout << cnt << "\n";
		return;
	}

	length /= 2;
	if (r >= y + length) {
		if (c >= x + length) {
			func(y + length, x + length, length,cnt+(length*length)*3);
		}
		else {
			func(y + length, x,length, cnt + (length * length) * 2);
		}
	}
	else if (c >= x + length) {
		if (r<y+length) {
			func(y , x + length, length, cnt + (length * length) * 1);
		}
	}
	else {
		func(y, x, length,cnt);
	}
	length *= 2;

}


int main(){
	cin >> n >> r >> c;

	func(0, 0,pow(2,n), 0);
}