#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int main(int argc, char *argv[]) {
	
	rng.seed(atoi(argv[1]));
	const int tc = 5, N = 100*1000, Q = 100*1000, MAXVAL = 1000*1000*1000;
	printf("%d\n", tc);
	for(int rep = 0; rep < tc; rep++) {
		int n = N;
		printf("%d\n", n);
		for(int i = 0; i < n; i++) {
			printf("%d ", 1);
		}
		puts("");
		int q = Q;
		printf("%d\n", q);
		for(int i = 0; i < q; i++) {
			int L = rand(1, rand(1, n));
			int R = rand(rand(L, n), n);
			printf("%d %d\n", L, R);
		}
	}
}
