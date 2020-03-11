#include <bits/stdc++.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool sub_1(vector<int>& a, vector<int>& b) {
	int n = a.size();
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
	
	return ok;
}

bool sub_2(vector<int>& a, vector<int>& b) {
	int n = a.size();
	vector<int> arr;
	for(int x : a) arr.push_back(x);
	for(int x : b) arr.push_back(x);
	
	map<int, int> freq;
	for(int x : arr) freq[x]++;
	int mx = 0;
	for(auto p : freq) mx = max(mx, p.second);

	return mx <= n;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int tc, s;
	cin >> tc >> s;
	while(tc--) {
		int n;
		cin >> n;
		vector<int> a(n), b(n);
		for(int& x : a) cin >> x;
		for(int& x : b) cin >> x;
		bool ok = sub_1(a, b);
		if(s == 2 && sub_2(a, b)) {
			ok = true;
		}
		cout << (ok ? "YES" : "NO") << '\n';
	}
}
