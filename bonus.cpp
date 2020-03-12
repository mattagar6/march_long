#include <bits/stdc++.h>
using namespace std;

//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//$ int rand(int a, int b) {
	//$ return a + rng() % (b - a + 1);
//$ }

struct P {
	int x, y;
	P(int _x = -1, int _y = -1) : x(_x), y(_y) {}
	
	bool operator !=(const P& rhs) const {
		return x != rhs.x || y != rhs.y;
	}
	
	bool operator < (const P& rhs) const {
		return tie(x, y) < tie(rhs.x, rhs.y);
	}
};



int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	set<pair<P, int>> points;
	for(int i = 0; i < n; i++) {
		P p;
		cin >> p.x >> p.y;
		points.emplace(p, i+1);
	}
	
	int moves = 0;
	vector<vector<int>> ans;
	while((int) points.size() > 1) {
		vector<int> arr;
		P p, q;
		int i, j;
		p = points.begin()->first;
		i = points.begin()->second;
		points.erase(points.begin());
		
		
		q = points.begin()->first;
		j = points.begin()->second;
		
		int dx = q.x - p.x;
		int dy = q.y - p.y;
		int neg = dy < 0 ? -1 : 1;
		dy *= neg;
		int GCD = __gcd(dx, dy);
		dx /= GCD, dy /= GCD;
		dy *= neg;
		p.x += dx, p.y += dy;
		if(p != q) {
			points.emplace(p, i);
		}
		
		arr = {i, j};
		ans.push_back(arr);
		moves += 2;
	}
	
	//$ assert(moves <= 500*1000);
	cout << moves << endl;
	//$ cout << ans.size() << '\n';
	//$ for(int i = 0; i < (int) ans.size(); i++) {
		//$ cout << ans[i].size() << ' ';
		//$ for(int j = 0; j < (int) ans[i].size(); j++) {
			//$ cout << ans[i][j] << ' ';
		//$ }
		//$ cout << '\n';
	//$ }
}
