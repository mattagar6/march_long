#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 998244353;

#define MAXN 100*1000+5
#define BITS 31

int fact[MAXN];

void add_self(int& a, int b) {
	a += b;
	if(a >= mod) { a -= mod; }
}

int mul(int a, int b) {
	return ll(a) * ll(b) % mod;
}

int mpow(int a, int n) {
	if(n == 0) return 1;
	int x = mpow(a, n/2);
	x = mul(x, x);
	if(n % 2 == 1) x = mul(x, a);
	return x;
}

int binomial(int n, int k) {
	return mul(fact[n], mul(mpow(fact[k], mod-2), mpow(fact[n-k], mod-2)));
}

const int block = 1000;

struct Query {
	int L, R;
	bool operator < (const Query& rhs) const {
		if(L/block == rhs.L/block) {
			return R < rhs.R;
		} else {
			return L/block < rhs.L/block;
		}
	};
};

void test_case() {
	int n, m;
	cin >> n;
	vector<int> arr(n);
	for(int& x : arr) cin >> x;
	cin >> m;
	vector<pair<Query, int>> queries(m);
	for(int i = 0; i < m; i++) {
		Query& q = queries[i].first;
		queries[i].second = i;
		cin >> q.L >> q.R;
		q.L--, q.R--;
		
	}
	
	vector<int> ans(m);
	sort(queries.begin(), queries.end());
	
	int cur_L = 0, cur_R = 0;
	int sum = 0;
	
	for(int i = 0; i < m; i++) {
		int L = queries[i].first.L, R = queries[i].first.R;
		
	}
	
	for(int i = 0; i < m; i++) {
		cout << ans[i] << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	// use Mo's algorithm to answer queries
	// (x ^ sum) < x => x has leftmost bit of sum set,
	// buckets? 
	
	fact[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fact[i] = mul(i, fact[i-1]);
	}
	
	int tc;
	cin >> tc;
	while(tc--) {
		test_case();
	}
}
