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

int cross(V a, V b) {
	return a.x * b.y - a.y * b.x;
}

double angle(V a) {
	return atan2(a.y, a.x);
}

//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng;

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}


vector<P> points;

vector<P> get_hull() {
	vector<P> hull;
	
	int n = points.size();
	
	if(n < 3) {
		return points;
	}
	
	int pos = -1, min_y = 1000*1000, max_x = -1000*1000;
	for(int i = 0; i < n; i++) {
		if(points[i].y < min_y || (points[i].y == min_y && points[i].x > max_x)) {
			pos = i;
			min_y = points[i].y;
			max_x = points[i].x;
		}
	}
	
	P pivot = points[pos];
	swap(points[pos], points[0]);
	
	sort(points.begin()+1, points.end(), [&](P a, P b) {
		if(fabs(atan2(a.y - pivot.y, a.x - pivot.x) - atan2(b.y - pivot.y, b.x - pivot.x)) < eps) {
			return (a.y - pivot.y)*(a.y - pivot.y) + (a.x - pivot.x)*(a.x - pivot.x) <
					(b.y - pivot.y)*(b.y - pivot.y) + (b.x - pivot.x)*(b.x - pivot.x);
		} else {
			return atan2(a.y - pivot.y, a.x - pivot.x) < atan2(b.y - pivot.y, b.x - pivot.x);
		}
	});
	
	hull = {points[n-1], points[0], points[1]};
	int i = 2, j = -1;
	while(i < n) {
		j = (int) hull.size() - 1;
		int c = cross(V(hull[j], points[i]), V(hull[j], hull[j-1]));
		if(c < 0) {
			hull.push_back(points[i++]);
		} else if(c == 0) {
			i++;
		} else {
			hull.pop_back();
		}
	}
	
	reverse(hull.begin(), hull.end());
	return hull;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	memset(grid, 0, sizeof grid);
	
	int n;
	cin >> n;
	points.resize(n);
	for(int i = 0; i < n; i++) {
		P& p = points[i];
		cin >> p.x >> p.y;
		grid[p.x][p.y] = i+1;
	}
	
	cerr << points.size() << endl;
	
	vector<P> arr = get_hull();
	cerr << arr.size() << endl;
	cerr << points.size() << endl;
	for(P p : arr) {
		cerr << p << endl;
	}
}
