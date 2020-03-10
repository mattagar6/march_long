#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;

using ll = long long;
const int mod = 998244353;

#define MAXN 100*1000+5

int fact[MAXN], fact_inv[MAXN];

inline void add_self(int& a, int b) {
	a += b;
	if(a >= mod) { a -= mod; }
}

inline int mul(int a, int b) {
	return ll(a) * ll(b) % mod;
}

int mpow(int a, int n) {
	if(n == 0) return 1;
	int x = mpow(a, n/2);
	x = mul(x, x);
	if(n % 2 == 1) x = mul(x, a);
	return x;
}

inline int binomial(int n, int k) {
	return mul(fact[n], mul(fact_inv[k], fact_inv[n-k]));
}

const int block = 400;

struct Query {
	int L, R;

	inline pair<int, int> to_pair() const {
		return make_pair(L/block, ((L/block) & 1) ? -R : R);
	}

	bool operator < (const Query& rhs) const {
		return to_pair() < rhs.to_pair();
	};
};

inline void compress(vector<int>& arr) {
	vector<int> ans = arr;
	sort(ans.begin(), ans.end());
	ans.resize(unique(ans.begin(), ans.end()) - ans.begin());
	for(int& x : arr) {
		int i = lower_bound(ans.begin(), ans.end(), x) - ans.begin();
		x = i;
	}
}

inline void test_case() {
	int n, m;
	cin >> n;
	vector<int> arr(n);
	for(int& x : arr) cin >> x;
	compress(arr);
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
	//$ unordered_map<int, int> freq_freq; // change to an array
	//$ freq_freq.reserve(2*m);
	gp_hash_table<int, int> freq_freq;
	vector<int> freq(n);
	//$ freq[arr[0]] = 1;
	//$ freq_freq[1] = 1;
	for(int i = 0; i < m; i++) {
		int L = queries[i].first.L, R = queries[i].first.R;
		while(cur_R <= R) {
			int f = freq[arr[cur_R]];
			freq[arr[cur_R]]++;
			freq_freq[f]--;
			freq_freq[f+1]++;
			sum ^= f ^ (f+1);
			cur_R++;
		}
		
		while(cur_L > L) { 
			int f = freq[arr[cur_L-1]];
			freq[arr[cur_L-1]]++;
			freq_freq[f]--;
			freq_freq[f+1]++;
			sum ^= f ^ (f+1);
			cur_L--;
		}
		
		while(cur_L < L) {
			int f = freq[arr[cur_L]];
			freq[arr[cur_L]]--;
			freq_freq[f]--;
			freq_freq[f-1]++;
			sum ^= f ^ (f-1);
			cur_L++;
		}

		while(cur_R > R + 1) {
			int f = freq[arr[cur_R-1]];
			freq[arr[cur_R-1]]--;
			freq_freq[f]--;
			freq_freq[f-1]++;
			sum ^= f ^ (f-1);
			cur_R--;
		}
		int& res = ans[queries[i].second];
		if(sum == 0) {
			res = 0;
			continue;
		}
		for(auto p : freq_freq) {
			int x = p.first, occur = p.second;
			assert(x >= 0);
			if((x ^ sum) < x) {
				add_self(res, mul(occur, binomial(x, x ^ sum)));
			} 
		}
		if(i % 1000 == 0) {
			cerr << i << " done" << endl;
		}
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
	
	fact[0] = fact_inv[0] = 1;
	for(int i = 1; i < MAXN; i++) {
		fact[i] = mul(i, fact[i-1]);
		fact_inv[i] = mpow(fact[i], mod-2);
	}
	
	int tc;
	cin >> tc;
	while(tc--) {
		test_case();
	}
}
