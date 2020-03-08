#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int main(int argc, char *argv[]) {
	
	rng.seed(atoi(argv[1]));
	
	const int tc = 1, N = 10, Q = 5, MAX_VAL = 20;
	printf("%d\n", tc);
	for(int rep = 0; rep < tc; rep++) {
		int n = rand(2, N), q = rand(1, Q);
		printf("%d %d\n", n, q);
		for(int i = 0; i < n; i++) {
			printf("%d ", rand(1, MAX_VAL));
		}
		puts("");
		for(int i = 0; i < q; i++) {
			int x1 = rand(1, n-1);
			int x2 = rand(x1+1, n);
			int y = rand(1, MAX_VAL);
			printf("%d %d %d\n", x1, x2, y);
		}
	}
	
	return 0;
}
