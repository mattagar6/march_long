#include <bits/stdc++.h>
using namespace std;

void test_case() {
	int n, q;
	cin >> n >> q;
	int even = 0, odd = 0;
	for(int i = 0; i < n; i++) {
		int x;
		cin >> x;
		if(__builtin_popcount(x) % 2 == 0) {
			even++;
		} else {
			odd++;
		}
	}
	
	while(q--) {
		int p;
		cin >> p;
		if(__builtin_popcount(p) % 2 == 0) {
			cout << even << ' ' << odd << '\n';
		} else {
			cout << odd << ' ' << even << '\n';
		}
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
