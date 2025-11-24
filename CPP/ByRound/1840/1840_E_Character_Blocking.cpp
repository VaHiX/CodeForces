// Problem: CF 1840 E - Character Blocking
// https://codeforces.com/contest/1840/problem/E

#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 5;
char a[2][MAX];
char yes[] = "YES";
char no[] = "NO";

void testcase() {
    // Read two strings
    for (int i = 0; i < 2; i++) {
        scanf("%s", a[i]);
    }
    
    int n = strlen(a[0]);
    int cnt = 0;
    
    // Helper functions to update count of differing positions
    auto remove = [&](int i) { cnt -= (a[0][i] != a[1][i]); };
    auto take = [&](int i) { cnt += (a[0][i] != a[1][i]); };
    
    // Initialize count of differing positions
    for (int i = 0; i < n; i++)
        take(i);
    
    int x, q;
    scanf("%d%d", &x, &q);
    
    // Array to keep track of positions that are removed
    vector<int> at(q + x + 1, -1);
    
    for (int i = 0; i < q; i++) {
        if (at[i] != -1)
            take(at[i]);
            
        int typ;
        scanf("%d", &typ);
        
        if (typ == 1) {
            // Mark character for removal from comparison
            int y;
            scanf("%d", &y);
            y--;
            remove(y);
            at[i + x] = y;
        } else if (typ == 2) {
            // Swap characters between strings
            int t1, t2, i1, i2;
            scanf("%d%d%d%d", &t1, &i1, &t2, &i2);
            t1--;
            t2--;
            i1--;
            i2--;
            
            // Remove old differing positions
            remove(i1);
            remove(i2);
            
            // Perform swap
            swap(a[t1][i1], a[t2][i2]);
            
            // Add new differing positions
            take(i1);
            take(i2);
        } else {
            // Print result based on count of differing positions
            printf("%s\n", (cnt == 0 ? yes : no));
        }
    }
}

int main() {
    int tt = 1;
    scanf("%d", &tt);
    while (tt--) {
        testcase();
    }
    return 0;
}


// https://github.com/VaHiX/CodeForces/