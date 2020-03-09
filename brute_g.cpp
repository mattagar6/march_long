#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int mod = 998244353;

#define MAXN 1000+5

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

void test_case() {
	int n, q;
	cin >> n;
	vector<int> arr(n);
	for(int& x : arr) cin >> x;
	cin >> q;
	while(q--) {
		int L, R;
		cin >> L >> R;
		L--, R--;
		map<int, int> freq;
		for(int i = L; i <= R; i++) {
			freq[arr[i]]++;
		}
		int ans = 0;
		int sum = 0;
		for(auto p : freq) {
			sum ^= p.second;
		}
		
		for(auto p : freq) {
			int x = p.second;
			if((x ^ sum) < x) { 
				add_self(ans, binomial(x, x ^ sum));
			}
		}
		cout << ans << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
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
