# Problem: CF 1955 C - Inhabitant of the Deep Sea
# https://codeforces.com/contest/1955/problem/C

"""
Algorithm: Inhabitant of the Deep Sea
Purpose: Determine how many ships are sunk after k attacks by the Kraken, 
         where attacks alternate between the first and last alive ship.
Techniques:
    - Simulation with optimized attack pattern
    - Prefix sums to quickly determine how many ships are attacked
Time Complexity: O(n), where n is the number of ships
Space Complexity: O(1), only using a few variables for computation
"""

def sol(n: int, k: int, lst: list):
    # If total durability is less than or equal to k, all ships sink
    if sum(lst) <= k:
        return n
    
    # Calculate how many times the Kraken attacks from left and right
    # If k is even, both left and right get k//2 attacks
    # If k is odd, left gets one more attack (k//2 + 1), right gets k//2
    if k % 2 == 0:
        left = k // 2
        right = k // 2
    else:
        left = k // 2 + 1
        right = k // 2
    
    # Find how many ships are sunk from the left side
    ind = 0
    pre_sum = 0
    for ele in lst:
        pre_sum += ele
        if pre_sum > left:
            break
        ind += 1
    
    # Find how many ships are sunk from the right side
    pre_sum = 0
    for i in range(len(lst) - 1, -1, -1):
        pre_sum += lst[i]
        if pre_sum > right:
            break
        ind += 1
    
    # Return the number of ships sunk overall
    return ind


if __name__ == "__main__":
    for _ in range(int(input())):
        n, k = map(int, input().split())
        lst = list(map(int, input().split()))
        print(sol(n, k, lst))


# https://github.com/VaHiX/CodeForces/