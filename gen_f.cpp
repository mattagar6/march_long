#include <bits/stdc++.h>
using namespace std;

//$ mt19937 rng;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand(int a, int b) {
	return a + rng() % (b - a + 1);
}

int main(int argc, char *argv[]) {
	
	//$ rng.seed(atoi(argv[1]));
	#define POINTS (1<<17)
	#define N 10
	#define VAL 5*1000
	
	
	
	int tc = 10000;
	printf("%d 2\n", tc);
	while(tc--) {
		int n = N;
		printf("%d\n", n);
		vector<int> arr(n);
		for(int i = 0; i < n; i++) {
			arr[i] = rand(1, VAL);
		}
		sort(arr.begin(), arr.end());
		for(int i = 0; i < n; i++) {
			printf("%d ", arr[i]);
		}
		puts("");
		for(int i = 0; i < n; i++) {
			arr[i] = rand(1, VAL);
		}
		sort(arr.begin(), arr.end());
		for(int i = 0; i < n; i++) {
			printf("%d ", arr[i]);
		}
		puts("");
	}
}
