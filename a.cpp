#include <bits/stdc++.h>
using namespace std;

void test_case() {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> fruit(n);
        for(int i = 0; i < n; i++) {
                cin >> fruit[i].first;
        }
        for(int i = 0; i < n; i++) {
                cin >> fruit[i].second;
        }
        map<int, int> cost;
        for(int i = 0; i < n; i++) {
                cost[fruit[i].first] += fruit[i].second;
        }
        int ans = cost.begin()->second;
        for(auto& p : cost) {
                ans = min(ans, p.second);
        }
        cout << ans << '\n';
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