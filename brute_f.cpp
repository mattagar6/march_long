#include <bits/stdc++.h>
using namespace std;

bool rec(vector<int> a, vector<int> b, map<int, int> table, bool attack, int beat) {
	if(a.empty() && b.empty()) {
		return true;
	}

	if(a.empty() && attack) {
		return false;
	}

	if(b.empty() && !attack) {
		return false;
	}

	int n = a.size(), m = b.size();
	if(attack) {
		if(table.empty()) {
			for(int i = 0; i < n; i++) {
				// try placing this card
				vector<int> next;
				for(int j = 0; j < n; j++) {
					if(i == j) continue;
					next.push_back(a[j]);
				}

				table[a[i]]++;
				if(rec(next, b, table, false, a[i])) {
					return true;
				}
				table[a[i]]--;
				if(table[a[i]] == 0) {
					table.erase(a[i]);
				}
			}

			return rec(b, a, map<int, int>(), true, -1);
		} else {
			for(int i = 0; i < n; i++) {
				if(table[count[a[i]]] == 0) continue;
				vector<int> next;
				for(int j = 0; j < n; j++) {
					if(i == j) continue;
					next.push_back(a[j]);
				}

				table[a[i]]++;
				if(rec(next, b, table, false, a[i])) {
					return true;
				}
				table[a[i]]--;
				if(table[a[i]] == 0) {
					table.erase(a[i]);
				}
			}

			return rec(b, a, map<int, int>(), true, -1);
		}
	} else {
		for(int j = 0; j < m; j++) {

		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	/*	make all swaps at the beginning,
	 *	then same as subtask 1
	 *
	 *	is order of moves relevant? kindof
	 */

}
