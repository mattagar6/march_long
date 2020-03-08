#include <bits/stdc++.h>
using namespace std;

#define MAXN 1005

vector<int> g[MAXN];
int match[MAXN], seen[MAXN];

bool aug(int i) {
	if(seen[i]) return false;
	seen[i] = 1;
	
	for(int v : g[i]) {
		if(match[v] == -1 || aug(match[v])) {
			match[v] = i;
			return true;
		}
	}
	
	return false;
}

void test_case() {
	
	memset(match, -1, sizeof match);
	for(int i = 0; i < MAXN; i++) g[i].clear();
	
	int n, k;
	cin >> n >> k;
	vector<vector<int>> perm(k, vector<int>(n)), pos(k, vector<int>(n));
	for(int i = 0; i < k; i++) {
		for(int j = 0; j < n; j++) {
			cin >> perm[i][j];
			perm[i][j]--;
			pos[i][perm[i][j]] = j;
		}
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			bool ok = true;
			for(int r = 0; r < k; r++) {
				if(pos[r][i] >= pos[r][j]) {
					ok = false;
				}
			}
			
			if(ok) {
				g[i].push_back(j+n); // out
				g[j+n].push_back(i); // in
			}
		}
	}
	
	for(int i = 0; i < n; i++) {
		memset(seen, 0, sizeof seen);
		aug(i);
	}
	
	vector<int> to(n);
	int ans = n;
	for(int i = n; i < 2*n; i++) {
		if(match[i] != -1) {
			to[match[i]] = i-n+1;
			ans--;
		}
	}
	cout << ans << '\n';
	for(int i = 0; i < n; i++) {
		cout << to[i] << " \n"[i==n-1];
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
