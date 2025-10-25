# Problem: CF 1992 F - Valuable Cards
# https://codeforces.com/contest/1992/problem/F

"""
Task: Divide cards into minimum number of bad segments.
A segment is bad if no subset of cards in it can multiply to x.
Algorithm: Greedy approach with set manipulation.
Time Complexity: O(n * sqrt(x)) per test case, where n is the number of cards.
Space Complexity: O(sqrt(x)) for storing possible products in the set.
"""

def solve():
    n, x = map(int, input().split())
    a = list(map(int, input().split()))
    # Initialize set with x - this represents all possible products that could lead to x
    set_a = set([x])
    ans = 1  # Start with one segment
    for i in range(n):
        if a[i] not in set_a:
            # If a[i] is not in current set, we're still building a valid segment
            tmp_set = set_a.copy()
            for j in set_a:
                # If j is divisible by a[i], we can form a new product by dividing j by a[i]
                if j % a[i] == 0:
                    tmp_set.add(j // a[i])
            set_a = tmp_set
        else:
            # If a[i] is already in set, we must start a new segment
            set_a = set([x, x // a[i]])
            ans += 1
    print(ans)

t = int(input())
for _ in range(t):
    solve()


# https://github.com/VaHiX/CodeForces/