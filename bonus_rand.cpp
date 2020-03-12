#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//$ mt19937 rng;

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

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

#define N (1<<10) + 1

int used[N][N], start[N][N];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	memset(used, -1, sizeof used);
	memset(start, -1, sizeof start);
	int n;
	cin >> n;
	vector<P> arr(n);
	
	for(int i = 0; i < n; i++) {
		P& p = arr[i];
		cin >> p.x >> p.y;
		used[p.x][p.y] = start[p.x][p.y] = i+1;
	}
	
	int moves = 1000*1000;
	vector<vector<int>> best;
	for(int rep = 0; rep < 50; rep++) {
		vector<vector<int>> ans;
		vector<P> points = arr;
		int cur_moves = 0;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++) {
				used[i][j] = start[i][j];
			}
		while((int) points.size() > 1) {
			vector<int> cur;
			int m = points.size();
			P p, q;
			int i;
			do {
				i = rand(0, m-2);
				p = points[i];
				q = points[m-1];
				if(q < p) {
					swap(points[i], points[m-1]);
				}
			} while(q < p);
			
			
			swap(points[i], points[m-1]);
			points.pop_back();
			
			int dx = q.x - p.x;
			int dy = q.y - p.y;
			int neg = dy < 0 ? -1 : 1;
			
			dy *= neg;
			int GCD = __gcd(dx, dy);
			dy *= neg;
			dx /= GCD, dy /= GCD;
			
			int j = used[p.x][p.y];
			used[p.x][p.y] = -1;
			p.x += dx, p.y += dy;
			if(used[p.x][p.y] == -1) {
				
				points.push_back(p);
				int r = p.x, c = p.y;
				while(used[r][c] == -1) {
					r += dx, c += dy;
				}
				used[p.x][p.y] = j;
				cur = {j, used[r][c]};
			} else {
				cur = {j, used[p.x][p.y]};
			}
			
			ans.push_back(cur);
			cur_moves += 2;
		}
		
		if(cur_moves < moves) {
			moves = cur_moves;
			best = ans;
		}
	}
	
	assert(moves <= 500*1000);
	cerr << moves << endl;
	cout << best.size() << '\n';
	for(int i = 0; i < (int) best.size(); i++) {
		cout << best[i].size() << ' ';
		for(int j = 0; j < (int) best[i].size(); j++) {
			cout << best[i][j] << ' ';
		}
		cout << '\n';
	}
}
