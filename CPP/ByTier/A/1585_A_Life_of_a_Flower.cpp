/*
 * Problem URL : https://codeforces.com/contest/1585/problem/A
 * Submit Date : 2025-08-31
 */

#include<bits/extc++.h>
using namespace std;
int t, n, k, a, b;
int main() {
    for (scanf("%d", &t); t--; printf("%d\n", k < 0 ? -1 : k))
        for (scanf("%d%d", &n, &b), k = 1 + b; --n; scanf("%d", &a),
            a ? (b ? k += 5 : ++k) : (b ? 0 : k = -999), b = a);
    exit(0);
}