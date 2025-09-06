/*
 * Problem URL : https://codeforces.com/contest/657/problem/A
 * Submit Date : 2025-09-04
 */

#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
	int n, d, h;
	cin >> n >> d >> h;
	if (d - d/2 > h || d/2 > h || (n > 2 && d == 1)) return cout << -1, 0;
	for (int c = 1; c < n; printf("%d %d\n", ++c, (c-1==h&&d!=h?1:c>d?2-(h==1):c))) if (c > d && d >= n-1) break;
	return 0;
}
 
				  	  			  		  		  		 						