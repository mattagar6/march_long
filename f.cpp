#include <bits/stdc++.h>
using namespace std;

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

bool remove(map<int, int>& a, int x) {
	a[x]--;
	if(a[x] == 0) {
		a.erase(x);
		return false;
	}
	
	return true;
}

bool add(map<int, int>& a, int x) {
	a[x]++;
	return true;
}


bool rec(map<int, int>& a, map<int, int>& b) {
	if(a.empty() && b.empty()) {
		return true;
	}
	
	if(a.empty() || b.empty()) {
		return false;
	}
	
	set<int> seen;
	for(auto it = a.begin(); it != a.end() && a.size() && b.size(); it = a.begin()) {
		int x = it->first;
		if(seen.empty() || seen.count(x) == 1) {
			do {
				auto p = b.upper_bound(x);
				
				if(p == b.end()) {
					auto q = a.upper_bound(x);
					if(q == a.end()) {
						return false;
					} else {
						int y = q->first;
						remove(a, y);
						remove(a, x);
						int z = b.begin()->first;
						remove(b, z);
						add(a, z);
						continue;
					}
				} else {
					//$ cerr << p->first << endl;
					seen.insert(p->first);
					remove(b, p->first);
				}
				
				seen.insert(x);
				remove(a, x);
			} while(a.count(x));
		} else {
			return rec(b, a);
		}
	}
	
	return a.empty() && b.empty();
}

bool sub_2(vector<int>& a, vector<int>& b) {
	
	map<int, int> A, B;
	for(int x : a) A[x]++;
	for(int x : b) B[x]++;
	
	return rec(A, B);
	
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
		bool ok = false;
		if(s == 1) {
			ok = sub_1(a, b);
		} else {
			ok = sub_2(a, b);
		}
		
		cout << (ok ? "YES" : "NO") << '\n';
	}
}
