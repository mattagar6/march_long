#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());


struct P {
	int x, y;
	P(int _x = -1, int _y = -1) : x(_x), y(_y) {}
	
	bool operator < (const P& rhs) const {
		return tie(x, y) < tie(rhs.x, rhs.y);
	}
};

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector<P> points(n);
	for(int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
	}
	
	vector<vector<int>> res;
	int moves = 0;
	while((int) points.size() > 1) {
		int m = points.size();
		int i = -1, j = -1;
		do {
			i = rand(0, m-1);
			j = rand(0, m-1);
		} while(i == j);
		
		P p = points[i], q = points[j];
		if(q < p) swap(p, q);
	}
	
	cout << moves << endl;
}
