# Problem: CF 1983 F - array-value
# https://codeforces.com/contest/1983/problem/F

from collections import defaultdict


def cf1983F():
    # Algorithm: Using binary lifting with trie-like approach to find k-th smallest XOR value
    # Time Complexity: O(n * log(max_value) * log(n)) where max_value <= 10^9
    # Space Complexity: O(n)
    n, k = map(int, input().split())
    a = list(map(int, input().split()))

    ans = 0
    f = [n] * n  # f[i] stores the rightmost index such that a[i] XOR a[j] can be minimized for some j > i
    for d in range(29, -1, -1):  # Iterate from most significant bit to least
        p = defaultdict()  # Map: (a[i] >> d) -> index i
        nf = f.copy()  # New array to store updated f values
        for i in range(n):
            cur = (a[i] ^ ans) >> d  # Current prefix after applying ans
            if cur in p.keys():
                j = p[cur]
                if nf[j] > i:
                    nf[j] = i
            p[a[i] >> d] = i  # Store index for current prefix

        # Update nf to contain minimum valid right boundary for subarrays ending at each index
        for i in range(n - 2, -1, -1):
            if nf[i] > nf[i + 1]:
                nf[i] = nf[i + 1]

        sm = 0  # Count total number of valid subarrays with XOR value <= ans
        for i in range(n):
            sm += n - nf[i]

        if sm < k:
            ans |= 1 << d  # Set current bit if there are not enough subarrays with smaller values
            for i, x in enumerate(nf):
                f[i] = x

    print(ans)
    return


t = int(input())
for i in range(t):
    cf1983F()


# https://github.com/VaHiX/CodeForces/