# Problem: CF 2101 C - 23 Kingdom
# https://codeforces.com/contest/2101/problem/C

"""
C. 23 Kingdom

Purpose:
This code computes the maximum possible beauty of any "nice" array b derived from a given array a.
A nice array b satisfies: 1 <= b[i] <= a[i] for all i, and the beauty is defined as the sum of 
distances d_x(c) over all distinct values x in c, where d_x(c) is the largest gap between two occurrences of x in c.

Approach:
Uses a greedy algorithm with Union-Find (Disjoint Set Union) data structure to efficiently manage
and merge intervals of elements. The idea is to process elements from both ends of the array,
assigning values greedily and computing maximal distances.

Time Complexity: O(n * α(n)) where α is the inverse Ackermann function (nearly constant).
Space Complexity: O(n)

Algorithms/Techniques:
- Union-Find (Disjoint Set Union) for efficient merging and querying
- Two-pointer technique to traverse array from both ends
"""

def find(x, book):
    if x == book[x]:
        return x
    book[x] = find(book[x], book)
    return book[x]


for _ in range(int(input())):
    n, a = int(input()), list(map(int, input().split()))
    a = [0] + a  # Make indexing 1-based
    bookl, bookr = list(range(n + 1)), list(range(n + 1))  # Union-Find structures for left and right
    ans, l, r = 0, 1, n
    while l < r:
        # Move l pointer to next element that hasn't been processed yet (find(a[l], bookl) == 0)
        while l < r and find(a[l], bookl) == 0:
            l += 1
        # Move r pointer to previous element that hasn't been processed yet (find(a[r], bookr) == 0)
        while l < r and find(a[r], bookr) == 0:
            r -= 1
        if l < r:
            # Add the contribution of current pair: number of positions between l and r
            ans += r - l
            # Union-Find update: mark a[l] and a[r] as processed by decrementing their root values
            bookl[find(a[l], bookl)] = find(a[l], bookl) - 1
            bookr[find(a[r], bookr)] = find(a[r], bookr) - 1
            l += 1
            r -= 1
    print(ans)


# https://github.com/VaHiX/codeForces/