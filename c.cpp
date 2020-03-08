#include <bits/stdc++.h>
using namespace std;

void test_case() {
	int r, c;
	cin >> r >> c;
	vector<pair<int, int>> path;
	int x = (r+c)/2;
	path.emplace_back(x, x);
	pair<int, int> cur = {1, 1};
	for(int rep = 0; rep < 8; rep++) {
		path.push_back(cur);
		pair<int, int> next;
		if(cur.first + cur.second > 8) {
			next = cur;
			while(next.second < 8) {
				next.second++;
				next.first--;
			}
		} else {
			next = {1, cur.first + cur.second - 1};
		}
		
		path.push_back(next);
		swap(next.first, next.second);
		path.push_back(next);
		path.push_back(cur);
		
		cur.first++, cur.second++;
	}
	
	
	path.resize(unique(path.begin(), path.end()) - path.begin());
	cout << path.size() << '\n';
	for(auto p : path) {
		cout << p.first << ' ' << p.second << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int tc;
	cin >> tc;
	while(tc--) {
		test_case();
	}
}
