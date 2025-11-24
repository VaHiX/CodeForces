# Problem: CF 1928 E - Modular Sequence
# https://codeforces.com/contest/1928/problem/E

"""
Modular Sequence Problem

Algorithm:
The problem involves constructing a sequence of length n where:
- First element is x
- Each subsequent element is either (previous + y) or (previous % y)
- Total sum must be S

Approach:
1. Check if S is within reasonable bounds (minimum and maximum possible sums)
2. Use dynamic programming to determine how to distribute increments of y
3. Construct the sequence by building it step by step, using DP to decide where to apply increments

Time Complexity: O(n * sqrt(S)) where S is the sum of sequence elements
Space Complexity: O(sqrt(S)) for the DP array
"""

def II():
    return int(input())


def LMI():
    return list(map(int, input().split()))


def I():
    return input()


def MII():
    return map(int, input().split())


import math


def t():
    n, x, y, s = MII()
    alp = x % y  # remainder when x is divided by y
    
    # Check minimum possible sum
    if s < x + (n - 1) * alp:
        print("NO")
        return
        
    # Check if sum is valid based on modular arithmetic
    if (s - n * alp) % y:
        print("NO")
        return
        
    # Check maximum possible sum
    if s > n * x + y * (((n - 1) * n) // 2):
        print("NO")
        return
        
    # Calculate adjusted sum
    alp = s - n * alp
    bet = (x - x % y) // y  # whole multiples of y in x
    gam = alp // y  # number of y increments needed
    
    # DP array to store minimum operations needed
    dp = [math.inf] * (gam + 1)
    dp2 = [0] * (gam + 1)  # parent tracking for reconstruction
    dp[0] = 0
    
    # Build DP table - this represents different ways to distribute increments
    for i in range(1, gam + 1):
        xx = 1
        temp = 2
        while xx <= i:
            # Update DP with minimum operations
            if dp[i] > temp + dp[i - xx]:
                dp2[i] = temp
            dp[i] = min(dp[i], temp + dp[i - xx])
            xx += temp
            temp += 1

    # Try each possible position to start applying increments
    for i in range(1, n + 1):
        # Check if we can build the sequence from this point
        if gam - i * bet - (((i - 1) * i) // 2) < 0:
            break
        # If valid path exists in DP
        if dp[gam - i * bet - (((i - 1) * i) // 2)] <= n - i:
            print("YES")
            # Initialize sequence with remainders
            ans = [x % y] * (n)
            
            # Add multiples of y to first i elements
            for j in range(i):
                ans[j] += bet * y + j * y
                
            # Extract remaining increments using DP solution
            xx = dp[gam - i * bet - (((i - 1) * i) // 2)]
            cc = gam - i * bet - (((i - 1) * i) // 2)
            ini = i

            # Reconstruct the solution using DP tracking
            while xx > 0:
                for j in range(ini, ini + dp2[cc]):
                    ans[j] += (j - ini) * y
                ini += dp2[cc]
                xx -= dp2[cc]
                cc -= ((dp2[cc] - 1) * (dp2[cc])) // 2
                
            print(*ans)
            return
            
    print("NO")
    return


if __name__ == "__main__":
    for _ in range(II()):
        t()


# https://github.com/VaHiX/CodeForces/