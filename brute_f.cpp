#include <bits/stdc++.h>
using namespace std;

void sub_1() {
	int n;
	cin >> n;
	vector<int> a(n), b(n);
	for(int& x : a) cin >> x;
	for(int& x : b) cin >> x;
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	set<int> seen;
	bool ok = true;
	for(int i = 0; i < n; i++) {
		if(b[i] > a[i]) {
			if(i > 0 && seen.count(a[i]) == 0) {
				ok = false;
			}
		} else {
			ok = false;
		}
		seen.insert(a[i]);
		seen.insert(b[i]);
	}
	
	cout << (ok ? "YES" : "NO") << '\n';
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tc, s;
	cin >> tc >> s;
	while(tc--) {
		if(s == 1) {
			sub_1();
		} else {
			
		}
	}
}
