#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int main(int argc, char *argv[]) {
	
	rng.seed(atoi(argv[1]));
	#define POINTS (1<<17)
	#define N (1<<10)
	set<pair<int, int>> seen;
	int n = N;
	printf("%d\n", n);
	for(int i = 0; i < n; i++) {
		pair<int, int> p;
		do {
			p.first = rand(0, N);
			p.second = rand(0, N);
		} while(seen.count(p));
		seen.insert(p);
		printf("%d %d\n", p.first, p.second);
	}
}
