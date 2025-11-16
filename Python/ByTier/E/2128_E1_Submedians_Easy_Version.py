# Problem: CF 2128 E1 - Submedians (Easy Version)
# https://codeforces.com/contest/2128/problem/E1

"""
E1. Submedians (Easy Version)
Algorithms/Techniques: Binary search on answer + prefix sum + sliding window.

Time Complexity: O(n * log(n)) per test case, where n is the length of the array.
Space Complexity: O(n) for the prefix sum array and other auxiliary variables.

This solution finds the maximum submedian v_max and a corresponding subarray [l,r] 
of length at least k such that v_max is a median of that subarray. It uses binary 
search on the answer to determine the maximum possible value of v_max, and for each 
candidate v, it checks if there exists a valid subarray of length at least k where 
v is a median. The check uses prefix sums and sliding window technique to efficiently 
validate the condition.
"""

def possible(n, k, l, v):
    sommePref = [0]  # Prefix sum array to track validity of elements >= v
    for i in range(len(l)):
        sommePref.append(sommePref[-1] + (1 if l[i] >= v else -1))  # Increment by 1 if element >= v, else -1
    
    deb = 0  # Start index of current window
    for i in range(k, len(l) + 1):
        # Update the starting position of the window with minimum prefix sum so far
        if sommePref[i - k] < sommePref[deb]:
            deb = i - k
        # If current prefix sum is >= the minimum prefix sum in the valid window, return indices
        if sommePref[i] >= sommePref[deb]:
            return [deb, i - 1]
    return 0  # No valid subarray found


tests = int(input())
for _ in range(tests):
    n, k = list(map(int, input().split()))
    l = list(map(int, input().split()))
    
    resu = 0  # Binary search result for maximum submedian
    intervalle = [0, 0]
    v = 2**20  # Initial value for binary search (large enough to cover all possible elements)
    
    # Binary search on the answer
    while v:
        if resu + v <= len(l) and possible(n, k, l, resu + v):
            resu += v  # Update result if valid subarray exists for this value
        v = v // 2  # Reduce step size
    
    res = possible(n, k, l, resu)  # Final check for max possible value
    print(resu, res[0] + 1, res[1] + 1)  # Print result: max submedian and indices (1-based)


# https://github.com/VaHiX/codeForces/