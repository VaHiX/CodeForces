# Problem: CF 1904 B - Collecting Game
# https://codeforces.com/contest/1904/problem/B

"""
Collecting Game

Algorithm:
The problem requires us to determine, for each element in the array, how many additional elements can be removed 
after removing that element and setting the score to its value. This can be solved efficiently using a greedy approach 
with sorting and prefix sums.

Approach:
1. Sort the array in ascending order.
2. Compute prefix sums to quickly calculate the sum of elements up to a certain index.
3. Use dynamic programming from right to left to determine for each element how many elements can be removed 
   starting from that element.
4. Map the results back to the original array order.

Time Complexity: O(n log n) due to sorting.
Space Complexity: O(n) for storing prefix sums and mapping.

"""

def solve(n, arr):
    prefixs = [0] * n
    newarr = sorted(arr)  # Sort the array to process elements in increasing order
    ans = [0] * n
    ans[-1] = n - 1  # Last element can remove all elements to its left
    s = 0
    map = {newarr[-1]: n - 1}  # Map original values to computed answers
    
    # Compute prefix sums
    for i in range(len(newarr)):
        s += newarr[i]
        prefixs[i] = s
    
    # Fill the ans array from right to left using greedy logic
    for i in range(len(newarr) - 2, -1, -1):
        if prefixs[i] >= newarr[i + 1]:
            # If the sum of elements before i+1 is sufficient to include newarr[i+1], 
            # we can remove at least as many elements as from i+1
            ans[i] = ans[i + 1]
        else:
            # Otherwise, we can only remove elements up to index i
            ans[i] = i
        map[newarr[i]] = ans[i]  # Store the mapping for original array value
    
    # Map back the results to the original order of the array
    for i in range(len(arr)):
        ans[i] = map[arr[i]]
    return ans


t = int(input())
for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    ans = solve(n, arr)
    print(" ".join(map(str, ans)))


# https://github.com/VaHiX/CodeForces/