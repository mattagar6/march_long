#include <bits/stdc++.h>
using namespace std;

int sng(int x) {
	return (x > 0) - (x < 0);
}

void test_case() {
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for(int& x : arr) cin >> x;
	
	while(q--) {
		int x1, x2, y;
		cin >> x1 >> x2 >> y;
		x1--, x2--;
		int ans = 0;
		for(int l = x1; l < x2; l++) {
			if(sng(arr[l] - y) != sng(arr[l+1] - y) || arr[l] == y || arr[l+1] == y) {
				ans++;
			}
		}
		
		cout << ans << '\n';
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
