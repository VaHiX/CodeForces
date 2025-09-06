/*
 * Problem URL : https://codeforces.com/contest/929/problem/A
 * Submit Date : 2025-09-04
 */

#include<iostream>
#include<string>
using namespace std;

int main()
{
	int n, k;
	cin >> n >> k;
	int a;
	cin >> a;
	int pra = a;
	int kol = 1;
	for (int i = 1; i<n; i++)
	{
		int as;
		cin >> as;
		if (as - a>k) {
			cout << -1 << endl;
			return 0;
		}
		if (as - pra>k) {
			kol++;
			pra = a;
		}
		a = as;
	}
	cout << kol << endl;
	return 0;
}