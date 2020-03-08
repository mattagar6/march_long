#include <bits/stdc++.h>
#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

// query less than self in a range => merge sort tree 

#define MAXN 100*1000 + 5

pair<int, int> seg[MAXN];

bool cmp_less(const pair<int, int>& x, const pair<int, int>& y) {
	return max(x.first, x.second) < max(y.first, y.second);
}

bool cmp_great(const pair<int, int>& x, const pair<int, int>& y) {
	return min(x.first, x.second) > min(y.first, y.second);
}

class SegTree {
public:
	struct Node {
		vector<pair<int, int>> less, great;
		inline void merge(const Node& a,const Node& b) {
			int sz = a.less.size() + b.less.size();
			less.resize(sz);
			great.resize(sz);
			std::merge(a.less.begin(), a.less.end(), b.less.begin(), b.less.end(), less.begin(), cmp_less);
			std::merge(a.great.begin(), a.great.end(), b.great.begin(), b.great.end(), great.begin(), cmp_great);
		};
	};
	
	SegTree(int n_) {
		n = n_;
		tree.resize(4*n);
	}
	
	void build(int i, int L, int R) {
		if(L == R) {
			tree[i].less = {seg[L-1]};
			tree[i].great = {seg[L-1]};
		} else {
			int mid = L + (R - L)/2;
			build(2*i, L, mid);
			build(2*i+1, mid+1, R);
			tree[i].merge(tree[2*i], tree[2*i+1]);
		}
		
	}
	
	void push(int i) {
		
	}
	
	int get(int i, int L, int R, int tl, int tr, int v) {
		if(tl > tr) return 0;
		if(L == tl && tr == R) {
			int ans = 0;
			pair<int, int> p(v, v);
			ans += lower_bound(tree[i].less.begin(), tree[i].less.end(), p, cmp_less) 
						- tree[i].less.begin();
			ans += lower_bound(tree[i].great.begin(), tree[i].great.end(), p, cmp_great) 
						- tree[i].great.begin();
			return ans;
		} else {
			int mid = L + (R-L)/2;
			return get(2*i, L, mid, tl, min(tr, mid), v) + get(2*i+1, mid+1, R, max(tl, mid+1), tr, v);
		}
	}
	
	int get(int tl, int tr, int v) {
		return get(1, 1, n, tl, tr, v); 		
	}
	
private:
	int n;
	vector<Node> tree;
};



inline void test_case() {
	int n, q;
	cin >> n >> q;
	vector<int> arr(n);
	for(int& x : arr) scanf("%d", &x);
	for(int i = 0; i < n-1; i++) {
		seg[i] = make_pair(arr[i], arr[i+1]);
	}
	
	SegTree st(n-1);
	st.build(1, 1, n-1);
	
	while(q--) {
		int x1, x2, y;
		scanf("%d%d%d", &x1, &x2, &y);
		//$ x1--, x2--;
		printf("%d\n", x2 - x1 - st.get(x1, x2-1, y));
	}
}

int main() {
	
	int tc;
	scanf("%d", &tc);
	while(tc--) {
		test_case();
	}
}
