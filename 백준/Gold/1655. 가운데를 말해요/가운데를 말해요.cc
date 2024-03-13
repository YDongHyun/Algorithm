#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int n;
int min_heap[100101];
int max_heap[100101];
int minhn;
int maxhn;

int maxpop(int* heap, int& hn) {
	int ret, tmp;
	ret = heap[1];
	heap[1] = heap[hn];
	heap[hn--] = -21e8;
	for (int i = 1; i * 2 <= hn;) {
		if (heap[i] > heap[i * 2] && heap[i] > heap[i * 2 + 1]) {
			break;
		}
		else if (heap[i * 2] > heap[i * 2 + 1]) {
			tmp = heap[i * 2];
			heap[i * 2] = heap[i];
			heap[i] = tmp;
			i = i * 2;
		}
		else {
			tmp = heap[i * 2 + 1];
			heap[i * 2 + 1] = heap[i];
			heap[i] = tmp;
			i = i * 2 + 1;
		}

	}
	return ret;
}

void maxpush(int* heap, int& hn, int x) {
	heap[++hn] = x;
	int tmp;
	for (int i = hn; i > 1; i /= 2) {
		if (heap[i / 2] > heap[i]) break;
		tmp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = tmp;
	}
}



int minpop(int* heap, int& hn) {
	int ret, tmp;
	ret = heap[1];
	heap[1] = heap[hn];
	heap[hn--] = 21e8;
	for (int i = 1; i * 2 <= hn;) {
		if (heap[i] < heap[i * 2] && heap[i] < heap[i * 2 + 1]) {
			break;
		}
		else if (heap[i * 2] < heap[i * 2 + 1]) {
			tmp = heap[i * 2];
			heap[i * 2] = heap[i];
			heap[i] = tmp;
			i =i* 2;
		}
		else {
			tmp = heap[i * 2+1];
			heap[i * 2+1] = heap[i];
			heap[i] = tmp;
			i =i*2+1;
		}

	}
	return ret;
}

void minpush(int * heap, int& hn, int x) {
	heap[++hn] = x;
	int tmp;
	for (int i = hn; i >1; i /= 2) {
		if (heap[i / 2] < heap[i]) break;
		tmp = heap[i / 2];
		heap[i / 2] = heap[i];
		heap[i] = tmp;
	}
}



int main() {
	scanf("%d", &n);
	int a;
	scanf("%d", &a);
	minpush(min_heap, minhn, a);
	printf("%d\n", a);

	for (int i =1; i < n; i++){
		scanf("%d", &a);
		if (minhn == maxhn) {
			if (a < max_heap[1]) {
				minpush(min_heap, minhn, maxpop(max_heap, maxhn));
				maxpush(max_heap,maxhn,a);
				printf("%d\n", min_heap[1]);
			}
			else {
				minpush(min_heap,minhn,a);
				printf("%d\n", min_heap[1]);
			}
		}
		else {
			if (a > min_heap[1]) {
				maxpush(max_heap, maxhn, minpop(min_heap, minhn));
				minpush(min_heap, minhn, a);
				printf("%d\n", max_heap[1]);
			}
			else {
				maxpush(max_heap, maxhn, a);
				printf("%d\n", max_heap[1]);
			}
		}

	}

}