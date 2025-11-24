# Problem: CF 1858 B - The Walkway
# https://codeforces.com/contest/1858/problem/B

"""
Problem: Minimize the number of cookies Petya eats by removing one cookie seller.
Algorithm: 
- Use a greedy approach with sliding window technique to calculate cookie consumption.
- For each possible seller removal, compute the effect on cookie consumption.
- Maintain prefix and suffix calculations to efficiently determine impact.

Time Complexity: O(m) where m is the number of cookie sellers
Space Complexity: O(m) for storing the bench positions

The key idea is to model the cookie eating process as a sequence of intervals where 
Petya eats cookies at certain points. When a seller is removed, the impact on cookie eating 
can be calculated based on how the intervals around that seller are affected.

This uses a greedy algorithm:
1. Calculate the base number of cookies eaten without removing any seller
2. For each seller, compute how removing it changes the cookie count
3. Find the minimum possible count and how many sellers can achieve it
"""

def solve(d, x):
    # Calculate the number of cookies eaten based on current seller positions
    ans = 0
    for i in range(1, len(x)):
        # Count cookies in gaps between consecutive sellers
        ans += (x[i] - x[i - 1] - 1) // d
    # Add the count of sellers (as Petya eats one cookie at each seller's bench)
    ans += len(x) - 2
    return ans


def main():
    t = int(input())
    for _ in range(t):
        n, m, d = map(int, input().split())
        r = list(map(int, input().split()))
        # Add sentinel values to simplify calculations
        r.insert(0, 1 - d)
        r.append(n + 1)
        ans = 2e9  # Initialize with large value
        res = []   # Stores indices of sellers whose removal leads to minimum cookies
        for i in range(1, m + 1):
            # Calculate the gaps before and after removing the i-th seller
            A = r[i] - r[i - 1] - 1  # gap before this seller
            B = r[i + 1] - r[i] - 1  # gap after this seller
            C = r[i + 1] - r[i - 1] - 1  # combined gap (without this seller)
            # Calculate the impact of removing this seller
            D = C // d - (A // d + B // d)
            if D < ans:
                # Found a better (smaller) impact - reset the result list
                ans = D
                res = []
            if D == ans:
                # Same impact - add to result list
                res.append(r[i])
        # Final result is total cookies minus the minimum impact plus one (for initial cookie)
        print(ans + solve(d, r) - 1, len(res))


if __name__ == "__main__":
    main()


# https://github.com/VaHiX/CodeForces/