#include <bits/stdc++.h>
using namespace std;

#define inf 2*1000*1000*1000

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

bool sub_2(vector<vector<int>> player) {
	
	for(int i = 0; i < 2; i++) {
		sort(player[i].begin(), player[i].end());
	}

	int n = player[0].size();
	int turn = 0;
	set<int> table;
	for(int i = 0; i < n; ) {
		int x = player[turn][i];
	//	cerr << x << ' ' << turn << '\n';
		if(!table.empty() && table.count(x) == 0) {
			table.clear();
			turn ^= 1;
		} else {
			auto op = upper_bound(player[turn^1].begin(), player[turn^1].end(), x);
			if(op == player[turn^1].end()) {
				auto me = upper_bound(player[turn].begin(), player[turn].end(), x);
				if(me == player[turn].end()) {
					if(table.empty()) {
						return false;
					} else {
						table.clear();
						turn ^= 1;
						continue;
					}
				}

				table.clear();
				*me = x;
				player[turn][i+1] = player[turn^1][i];
				i++;
				turn ^= 1;
			} else {
				table.insert(x);
				table.insert(*op);
				*op = player[turn^1][i];
				i++;
			}
		}
	}	
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	/*
	 * 	if I can do it in k turns, can I do it in k + 1?
	 * 	probably not the right way to go
	 *
	 *
	 * 	on my turn, 2 operations:
	 * 		1. play a card already on the table (must play on first turn)
	 * 		2. give up => cards on table are discarded
	 *	
	 *	on opponent's turn, 2 operations:
	 *		1. play a card > than the card I just played
	 *		2. give up => opponent gets all cards on the table
	 *	
	 *	-> attackers played cards on a turn must be non-decreasing
	 *	-> same with defender, with constraint that a[i] < b[i] for all i
	 *	-> length of defender's sequence can be 1 shorter than attacker
	 *
	 *	opponent giving up is bad:
	 *		they gain > 1 cards that are on the table
	 *		attacker - k, oppenent + k
	 *	attacker giving up is good..
	 *
	 *	if one person gives up as the defender, the other player must also
	 *
	 *	I can defeat my own card... call it x
	 *		I use a card > x and give it to the opponent
	 *		opponent uses that card to beat x,
	 *		I give up, opponent gives me some card y,
	 *		its now opponents turn
	 *
	 *	maybe if we both try to win, we will tie?
	 *		-> we win when the opponent runs out of cards first
	 *		-> no, defender has the advantage, 
	 *		   can give up everytime => oponent giving up is bad?
	 *
	 *	consider a card x that gets beat by y, it is optimal for y to be 
	 *	as small as possible
	 *		-> 1, 2
	 *		-> 2, 3
	 *
	 *		proof: consider 2 possible ys, y1 and y2, y1 < y2
	 *			
	 *			
	 *
	 *
	 *	attacker plays 1, gets beat by 2, A plays 2, D plays 3
	 */

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
			ok = sub_2({a, b});
		}
		
		cout << (ok ? "YES" : "NO") << '\n';
	}
}
