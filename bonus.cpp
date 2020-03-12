#include <bits/stdc++.h>
using namespace std;

#define N (1<<10) + 1

int grid[N][N];

struct P {
	int x = -1, y = -1;
	P(int _x = -1, int _y = -1) : x(_x), y(_y) {}
	bool operator <(const P& you) const {
		return tie(x, y) < tie(you.x, you.y);
	}
};

struct V {
	int x, y;
	V(int _x = -1, int _y = -1) : x(_x), y(_y) {}
	V(P a, P b) {
		x = b.x - a.x;
		y = b.y - a.y;
	}
};

vector<vector<int>> ans;
vector<P> points;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//$ mt19937 rng;

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int cross(V a, V b) {
	return a.x * b.y - a.y * b.x;
}

double angle(V a) {
	return atan2(a.y, a.x);
}

vector<P> get_points(int m) {
	
	set<int> seen;
	vector<P> arr;
	for(int rep = 0; rep < m; rep++) {
		int sz = points.size();
		int pos;
		do {
			pos = rand(0, sz-1);
		} while(seen.count(pos));
		P p = points[pos];
		bool ok = true;
		for(int i = 0; i < (int) arr.size(); i++) {
			for(int j = i+1; j < (int) arr.size(); j++) {
				// check collinear
				V a(p, arr[i]), b(p, arr[j]);
				if(cross(a, b) == 0) {
					ok = false;
				}
			}	
		}
			
		if(ok) {
			arr.push_back(p);
			swap(points[sz-1], points[pos]);
			points.pop_back();
		}		
	}
	
	return arr;
}

vector<P> get_hull(vector<P> arr) {
	set<P> s;
	int n = arr.size();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			V v(arr[i], arr[j]);
			bool pos = true, neg = true;
			
			for(int k = 0; k < n; k++) {
				if(k == i || k == j) continue;
				V u(arr[i], arr[k]);
				int c = cross(v, u);
				pos &= c > 0;
				neg &= c < 0;
			}
			
			if(pos || neg) {
				s.insert(arr[i]);
			}
		}
	}
	
	vector<P> res(s.begin(), s.end());
	
	// sort by angle => clockwise
	int sz = res.size();
	int x = 0, y = 0;
	for(P p : res) {
		x += p.x, y += p.y;
	}
	
	x /= sz, y /= sz;
	P center(x, y);
	
	sort(res.begin(), res.end(), [&](P a, P b) {
		return angle(V(center, a)) > angle(V(center, b));
	});
	
	int pos = -1, min_x = 1000*1000;
	for(int i = 0; i < sz; i++) {
		if(res[i].x < min_x) {
			pos = i;
			min_x = res[i].x;
		}
	}
	
	int k = (sz - pos) % sz;
	reverse(res.begin(), res.end());
	reverse(res.begin(), res.begin()+k);
	reverse(res.begin()+k, res.end());
	return res;
}

vector<P> move(vector<P> arr) {
	int n = arr.size();
	vector<P> made;
	
	for(int i = 0; i < n-1; i++) {
		P p = arr[i];
		P q = arr[i+1];
		
		int dx = q.x - p.x;
		int neg_x = dx < 0 ? -1 : 1;
		int dy = q.y - p.y;
		int neg_y = dy < 0 ? -1 : 1;
		dx *= neg_x, dy *= neg_y;
		int GCD = __gcd(dx, dy);
		dx /= GCD, dy /= GCD;
		dx *= neg_x, dy *= neg_y;
		
		int x = p.x + dx, y = p.y + dy;
		if(grid[x][y] == -1) {
			grid[x][y] = grid[p.x][p.y];
			made.push_back(P(x, y));
		}
		grid[p.x][p.y] = -1;
	}
	
	made.push_back(arr.back());
	return made;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);


	memset(grid, -1, sizeof grid);
	int n;
	cin >> n;
	points.resize(n);
	for(int i = 0; i < n; i++) {
		P& p = points[i];
		cin >> p.x >> p.y;
		grid[p.x][p.y] = i+1;
	}
	
	int moves = 0;
	
	while((int) points.size() > 1) {
		int sz = points.size();
		
		int m = min(3, sz);
		vector<P> arr = get_points(m);
		
		arr = get_hull(arr);
		
		vector<int> inst;
		for(P p : arr) {
			inst.push_back(grid[p.x][p.y]);
		}
		
		moves += inst.size();
		ans.push_back(inst);
		
		arr = move(arr);
		for(P p : arr) {
			points.push_back(p);
		}
		assert((int) points.size() - sz < (int) inst.size());
	}
	
	cerr << n << ' ' << moves << endl;
	cout << ans.size() << '\n';
	for(int i = 0; i < (int) ans.size(); i++) {
		cout << ans[i].size() << ' ';
		for(int j = 0; j < (int) ans[i].size(); j++) {
			cout << ans[i][j] << ' ';
		}
		cout << '\n';
	}

}
