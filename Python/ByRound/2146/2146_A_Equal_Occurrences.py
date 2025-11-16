# Problem: CF 2146 A - Equal Occurrences
# https://codeforces.com/contest/2146/problem/A

"""
Equal Occurrences

Algorithm/Techniques: Sorting, Frequency Counting, Greedy Approach

Time Complexity: O(n log n) due to sorting the frequency counts
Space Complexity: O(n) for storing frequency counts

This problem asks us to find the length of the longest balanced subsequence in a non-decreasing array.
A balanced subsequence has all elements appearing with the same frequency.

Approach:
1. Count frequencies of each element in the array.
2. Sort these frequencies in descending order.
3. For each possible frequency value i (from 1 to n), calculate the maximum number of elements
   that can be selected such that each appears exactly i times. This is computed as i * cnt[i-1]
   where cnt[i-1] is how many distinct elements have frequency >= i.
4. Return the maximum such value.

"""
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    cnt = [0 for i in range(n + 1)]  # Count frequencies of each number (1-indexed)
    for i in a:
        cnt[i] += 1
    cnt.sort(reverse=True)  # Sort frequencies in descending order
    ans = 0
    for i in range(1, n + 1):
        ans = max(ans, i * cnt[i - 1])  # Try selecting 'i' elements from each of cnt[i-1] distinct numbers
    print(int(ans))


# https://github.com/VaHiX/CodeForces/