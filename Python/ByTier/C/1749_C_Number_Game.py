# Problem: CF 1749 C - Number Game
# https://codeforces.com/contest/1749/problem/C

"""
Algorithm: Greedy + Binary Search on Answer
Time Complexity: O(n^2) per test case
Space Complexity: O(n) per test case

The problem is about determining the maximum number of stages k Alice can win
in a game where both players play optimally. In each stage i, Alice must remove 
an element <= (k - i + 1), and Bob adds (k - i + 1) to any element if array isn't empty.

We use binary search on k (from n down to 0) to find the maximum k such that 
Alice wins. For a fixed k, we check if Alice can win by simulating the game:
- Sort the array.
- Try to greedily assign elements to stages.
- If we can assign each stage's requirement, Alice wins.

Key idea: For k stages, if the sorted array allows us to pick elements for each 
stage (each element is <= stage number), then Alice can win.
"""

for _ in range(int(input())):
    n = int(input())
    a = sorted(list(map(int, input().split())))
    # Try decreasing values of k from n to 0
    for k in range(n, -1, -1):
        # Check if Alice can win with k stages
        # For each stage i (0-indexed), we need a[i] <= i+1 (since k-i+1 = k-i+1)
        # But a is sorted, and we're checking if we can pick k elements properly
        # So: a[k-1+i] <= i+1 for all i in [0, k-1] 
        # This is checking a[k-1+i] <= i+1 for i = 0..k-1
        if all(k - 1 + i < n and a[k - 1 + i] <= i + 1 for i in range(k)):
            print(k)
            break


# https://github.com/VaHiX/CodeForces/