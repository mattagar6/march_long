#include <bits/stdc++.h>
using namespace std;

#define inf 2*1000*1000*1000

int test;

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

//$ mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937 rng;

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

bool good = true;

bool go(vector<vector<int>> player) {
	
	int turn = 0;
	map<int, int> table;
	int it = 0;
	//$ cerr << test << endl;
	while(!player[0].empty() && !player[1].empty() && it++ < 500*1000) {
		int x = player[turn][0];
		//$ printf("elem: %d, attack: %d\n", x, turn);
		if(!table.empty() && table.count(x) == 0) {
			table.clear();
			turn ^= 1;
		} else if(rand(0, 2)) {
			
			table[x]++; // attacker plays x
			swap(player[turn][0], player[turn].back());
			player[turn].pop_back();
			
			int y = -1, pos = -1;
			int m = player[turn^1].size();
			for(int rep = 0; rep < 5 && y == -1; rep++) {
				int i = rand(0, m-1);
				if(player[turn^1][i] > x) {
					y = player[turn^1][i];
					pos = i;
				}
			}
			
			
			
			if(y == -1) {
				// defender gives up
				
				for(auto p : table) {
					int a = p.first, f = p.second;
					while(f--) {
						player[turn^1].push_back(a);
					}
				}
				
				table.clear();
			} else {
				table[y]++;
				swap(player[turn^1][pos], player[turn^1].back());
				player[turn^1].pop_back();
			}
		} else {
			table.clear();
			turn ^= 1;
		}
	}
	
	good = it < 500*1000;
	return player[0].empty() && player[1].empty();
}

bool sub_2(vector<vector<int>> player) {
	
	int n = player[0].size();
	
	for(test = 1; test < 1000; test++) {
		for(int i = 0; i < 2; i++) {
			shuffle(player[i].begin(), player[i].end(), rng);
		}
		
		if(go(player)) {
			return true;
		} else if(!good) {
			good = true;
			return false;
		}
		
	}
	
	return false;
}


int main() {
	//$ ios_base::sync_with_stdio(false);
	//$ cin.tie(0);

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
	 *		-> we win when we run out of cards first
	 * 		-> in our best interest to play biggest card
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
