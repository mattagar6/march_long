#include <bits/stdc++.h>
using namespace std;

void test_case() {
	int n, m, k, q;
	cin >> n >> m >> k >> q;
	vector<pair<int, int>> arr(q);
	for(int i = 0; i < q; i++) {
		cin >> arr[i].first >> arr[i].second;
	}

	if(k == 3) {
		cout << 2 << ' ';
		for(int i = 0; i < q; i++) {
			cout << m-1 << ' ';
		}
		cout << endl;
		int ans;
		cin >> ans;
		if(ans == -1) {
			exit(0);
		}

	} else {
		vector<int> ans(q);

		for(int i = 0; i < q; i++) {
			int L = arr[i].first, R = arr[i].second;
			cout << 1 << ' ' << L << ' ' << R << ' ' << m/2 << endl;
			cin >> ans[i];
		}

		cout << 2 << ' ';
		for(int i = 0; i < q; i++) {
			cout << ans[i] << ' ';
		}
		cout << endl;
		int res;
		cin >> res;
		if(res == -1) {
			exit(0);
		}
	}
}

int main() {

	int tc;
	cin >> tc;
	while(tc--) {
		test_case();
	}

}
