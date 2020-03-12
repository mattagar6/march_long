#include <bits/stdc++.h>
using namespace std;

mt19937 rng;
//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int main(int argc, char *argv[]) {
	
	rng.seed(atoi(argv[1]));
	#define POINTS (1<<2)
	#define N (1<<3)
	
	int test = 4;
	
	if(test == 1) {
		vector<pair<int, int>> points;
		for(int x = 0; x <= 500; x++) {
			for(int y = 0; y <= 500; y++) {
				if((x+y) % 2 == 0) {
					points.emplace_back(x, y);
				}
			}
		}
		
		printf("%d\n", (int) points.size());
		for(int i = 0; i < (int) points.size(); i++) {
			printf("%d %d\n", points[i].first, points[i].second);
		}
	} else if(test == 2) {
		
	} else if(test == 3) {
		
	} else {
		set<pair<int, int>> seen;
		int n = POINTS;
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
}
