# Problem: CF 1500 A - Going Home
# https://codeforces.com/contest/1500/problem/A

"""
Algorithm: Hash Map + Two Sum-like Approach
Purpose: To find four distinct indices x, y, z, w such that a[x] + a[y] = a[z] + a[w]

Approach:
- Iterate through all pairs (i, j) where i > j
- For each pair, compute the sum a[i] + a[j]
- Store the first occurrence of each sum in a hash map with indices (i, j)
- If the same sum is encountered again and the new indices are different from previous ones, 
  we have found the required four indices

Time Complexity: O(n^2) - We iterate through all pairs (i, j) where i > j, which is roughly n^2/2.
Space Complexity: O(n^2) - In the worst case, we store up to n^2/2 different sums in the hash map.

"""

def main():
    n = int(input())
    a = list(map(int, input().split()))
    counters = dict()
    for i in range(1, n):  # i starts from 1 to n-1 (0-indexed)
        for j in range(i):  # j ranges from 0 to i-1
            s = a[i] + a[j]  # compute sum of a[i] and a[j]
            if s not in counters:  # if this sum is seen for the first time
                counters[s] = (i, j)  # store indices (i, j)
                continue
            prev = counters[s]  # get previous indices for this sum
            if i not in prev and j not in prev:  # check if current indices are not used before
                print("YES")
                print(i + 1, j + 1, prev[0] + 1, prev[1] + 1)  # print 1-indexed indices
                return
    print("NO")  # if no valid quadruple found


main()


# https://github.com/VaHiX/CodeForces/