# Problem: CF 1748 B - Diverse Substrings
# https://codeforces.com/contest/1748/problem/B

"""
Algorithm: Diverse Substrings Counting
Techniques: Sliding window, brute-force with optimization

Time Complexity: O(n * min(n, 100)) = O(n^2) in worst case, but due to the constraint that 
max frequency of any digit in a substring must not exceed number of distinct digits, 
and since there are at most 10 distinct digits, we can optimize to O(n * 100) = O(n)
Space Complexity: O(1) - only using fixed size array of size 10 for counting digits

This solution iterates over all starting positions and for each starting position,
it builds substrings incrementally, keeping track of digit frequencies and distinct count.
It stops extending a substring when max frequency exceeds number of distinct digits.
"""

for _ in range(int(input())):
    n = int(input())
    arr, ans = input(), 0
    for i in range(n):
        # Array to count occurrences of each digit (0-9)
        ary, a = [0] * 10, 0
        # Optimization: only check up to 100 characters ahead due to constraint
        for k in range(i, min(i + 100, n)):
            # If this digit was seen for the first time, increment distinct count
            if ary[int(arr[k])] == 0:
                a += 1
            # Increment frequency of current digit
            ary[int(arr[k])] += 1
            # If max frequency is <= number of distinct digits, substring is diverse
            if max(ary) <= a:
                ans += 1
    print(ans)


# https://github.com/VaHiX/CodeForces/