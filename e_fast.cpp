#include <bits/stdc++.h>
using namespace std;

bool cmp_less(const pair<int, int>& a, const pair<int, int>& b) {
	return max(a.first, a.second) < max(b.first, b.second);
}

bool cmp_great(const pair<int, int>& a, const pair<int, int>& b) {
	return min(a.first, a.second) > min(b.first, b.second);
}

struct Node {
	vector<pair<int, int>> less,great;
	void merge(const Node& a, const Node& b) {
		int sz = a.less.size() + b.less.size();
		less.resize(sz);
		great.resize(sz);
		std::merge(a.less.begin(), a.less.end(), b.less.begin(), b.less.end(), less.begin(), cmp_less);
		std::merge(a.great.begin(), a.great.end(), b.great.begin(), b.great.end(), great.begin(), cmp_great);
	}
};

void test_case() {
	int n, q;
	scanf("%d%d", &n, &q);
	vector<int> arr(n);
	for(int& x : arr) {
		scanf("%d", &x);
	}
	
	vector<pair<int, int>> seg(n-1);
	for(int i = 1; i < n; i++) {
		seg[i-1] = make_pair(arr[i-1], arr[i]);
	}
	int B = 1;
	while(B < n-1) {
		B *= 2;
	}
	
	vector<Node> tree(2*B);
	for(int i = B; i < B+n-1; i++) {
		tree[i].less = {seg[i-B]};
		tree[i].great = {seg[i-B]};
	}

	for(int i = B-1; i > 0; i--) {
		tree[i].merge(tree[2*i], tree[2*i+1]);
	}

#define debug(x) cerr << #x << " : " << x << endl
	while(q--) {
		int L, R, y;
		scanf("%d%d%d", &L, &R, &y);
		L += B - 1, R += B - 2;
		pair<int, int> p(y, y);
		int ans = R - L + 1;
		while(L <= R) {
			//debug(L); debug(R); debug(ans);
			if(L % 2 == 1) {
				auto& less = tree[L].less;
				auto& great = tree[L].great;
				ans -= lower_bound(less.begin(), less.end(), p, cmp_less) - less.begin();
				ans -= lower_bound(great.begin(), great.end(), p, cmp_great) - great.begin();
				L++;
			}

			if(R % 2 == 0) {
				auto& less = tree[R].less;
				auto& great = tree[R].great;
				ans -= lower_bound(less.begin(), less.end(), p, cmp_less) - less.begin();
				ans -= lower_bound(great.begin(), great.end(), p, cmp_great) - great.begin();
				R--;
			}
			L /= 2, R /= 2;
		}

		printf("%d\n", ans);
	}
}

int main() {

	int tc;
	scanf("%d", &tc);	
	while(tc--) {
		test_case();
	}
}
