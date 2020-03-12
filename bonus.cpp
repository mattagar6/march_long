#include <bits/stdc++.h>
using namespace std;

#define N (1<<10) + 1
#define eps (1e-9)

int grid[N][N];

struct P {
	int x = -1, y = -1;
	P(int _x = -1, int _y = -1) : x(_x), y(_y) {}
	
	bool operator ==(const P& you) const {
		return tie(x, y) == tie(you.x, you.y);
	}
	bool operator <(const P& you) const {
		return tie(x, y) < tie(you.x, you.y);
	}
};

ostream& operator <<(ostream& out, const P& p) {
	return out << "(" << p.x << ", " << p.y << ")";
}

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

//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng;

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int cross(V a, V b) {
	return a.x * b.y - a.y * b.x;
}

double angle(V a) {
	return atan2(a.y, a.x);
}

void shrink(int& dx, int& dy) {
	int neg_x = dx < 0 ? -1 : 1;
	int neg_y = dy < 0 ? -1 : 1;
	dx *= neg_x, dy *= neg_y;
	int GCD = __gcd(dx, dy);
	if(dx == 0) dy = 1;
	else if(dy == 0) dx = 1;
	else dx /= GCD, dy /= GCD;
	dx *= neg_x, dy *= neg_y;
}

P go(P p, int dx, int dy) {
	shrink(dx, dy);
	int x = p.x + dx, y = p.y + dy;
	while(grid[x][y] == -1) {
		x += dx, y += dy;
	}
	return P(x, y);
}



vector<P> get_points(int m, int thres = 0) {
	vector<P> arr;
	
	for(int rep = 0; rep < m; rep++) {
		int sz = points.size();
		int pos;
		pos = rand(0, sz-1);
		P p = points[pos];
		
		swap(points[pos], points[sz-1]);
		points.pop_back();
		arr.push_back(p);
	}
	
	return arr;
}

vector<P> get_hull(vector<P> arr) {
	vector<P> hull;
	
	int n = arr.size();
	
	if(n < 3) {
		return arr;
	}
	
	int pos = -1, min_y = 1000*1000, max_x = -1000*1000;
	for(int i = 0; i < n; i++) {
		if(arr[i].y < min_y || (arr[i].y == min_y && arr[i].x > max_x)) {
			pos = i;
			min_y = arr[i].y;
			max_x = arr[i].x;
		}
	}
	
	P pivot = arr[pos];
	swap(arr[pos], arr[0]);
	
	sort(arr.begin()+1, arr.end(), [&](P a, P b) {
		if(fabs(atan2(a.y - pivot.y, a.x - pivot.x) - atan2(b.y - pivot.y, b.x - pivot.x)) < eps) {
			return (a.y - pivot.y)*(a.y - pivot.y) + (a.x - pivot.x)*(a.x - pivot.x) <
					(b.y - pivot.y)*(b.y - pivot.y) + (b.x - pivot.x)*(b.x - pivot.x);
		} else {
			return atan2(a.y - pivot.y, a.x - pivot.x) < atan2(b.y - pivot.y, b.x - pivot.x);
		}
	});
	
	hull = {arr[n-1], arr[0], arr[1]};
	int i = 2, j = -1;
	while(i < n-1) {
		j = (int) hull.size() - 1;
		int c = cross(V(hull[j], arr[i]), V(hull[j], hull[j-1]));
		if(c > 0) {
			hull.push_back(arr[i++]);
		} else if(c == 0) {
			i++;
		} else {
			hull.pop_back();
		}
	}
	
	int m = hull.size();
	bool ok = true;
	for(i = 0; i < m; i++) {
		P a = hull[(m + i - 1) % m], b = hull[i], c = hull[(i+1)%m];
		int dx = c.x - b.x, dy = c.y - b.y;
		ok &= go(b, dx, dy) == c;
		
		if(!(go(b, dx, dy) == c)) {
			cerr << "in the way\n";
		}
		
		int cr = cross(V(b, a), V(b, c));
		if(cr == 0) {
			cerr << "collinear\n";
			ok = false;
		}
	}
	
	if(!ok) {
		return vector<P>();
	}
	
	reverse(hull.begin(), hull.end());
	return hull;
}

vector<P> move(vector<P> arr) {
	int n = arr.size();
	vector<P> made;
	
	for(int i = 0; i < n-1; i++) {
		P p = arr[i];
		P q = arr[i+1];
		
		int dx = q.x - p.x;
		int dy = q.y - p.y;
		shrink(dx, dy);
		assert(dx != 0 || dy != 0);
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
		int m = min(5, sz);
		vector<P> arr = get_points(m);
		vector<P> hull = get_hull(arr);
		if(hull.empty()) {
			for(P p : arr) {
				points.push_back(p);
			}
			continue;
		}
		vector<int> inst;
		for(P p : hull) {
			inst.push_back(grid[p.x][p.y]);
			assert(grid[p.x][p.y] != -1);
		}
		
		moves += inst.size();
		ans.push_back(inst);
		
		arr = move(hull);
		for(P p : arr) {
			points.push_back(p);
			assert(grid[p.x][p.y] != -1);
		}
	}
	assert(moves <= 500*1000);
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
