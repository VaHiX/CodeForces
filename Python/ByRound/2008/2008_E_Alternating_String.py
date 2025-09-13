# Contest 2008, Problem E: Alternating String
# URL: https://codeforces.com/contest/2008/problem/E

import sys
ci = sys.stdin.readline

def get_ind(c):
    return ord(c)-97

for _ in range(int(ci())):
    n = int(ci())
    s = ci().strip()
    odd, even = [0]*26, [0]*26
    if n & 1:
        for i in range(1, n, 2):
            odd[get_ind(s[i])] += 1
            even[get_ind(s[i+1])] += 1
        res = n - max(odd) - max(even)
        for i in range(0, n-1):
            arr = even if i & 1 else odd
            arr[get_ind(s[i])] += 1
            arr[get_ind(s[i+1])] -= 1
            res = min(res, n - max(odd) - max(even))
        print(res)
    else:
        for i in range(0, n, 2):
            odd[get_ind(s[i])] += 1
            even[get_ind(s[i+1])] += 1
        print(n - max(odd) - max(even))
