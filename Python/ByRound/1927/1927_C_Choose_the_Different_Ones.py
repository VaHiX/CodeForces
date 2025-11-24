# Problem: CF 1927 C - Choose the Different Ones!
# https://codeforces.com/contest/1927/problem/C

"""
Problem: C. Choose the Different Ones!
Algorithm: 
    - Use bitmasks to track which numbers (from 1 to k) are present in each array.
    - For each number from 1 to k, check if it exists in array 'a', array 'b', or both.
    - Count how many numbers fall into each category (only in a, only in b, in both, not in either).
    - Check if it's possible to choose exactly k/2 elements from each array such that all numbers from 1 to k are covered.
Time Complexity: O(n + m + k)
Space Complexity: O(k)
"""

def solve():
    n, m, k = map(int, input().split())
    first = list(map(int, input().split()))
    second = list(map(int, input().split()))
    
    # counts[i] will hold a bitmask:
    # 1 if number i is in array 'a'
    # 2 if number i is in array 'b'
    # 3 if number i is in both arrays
    counts = [0] * (k + 1)
    
    # Mark presence of numbers in array 'a'
    for num in first:
        if num <= k:
            counts[num] |= 1  # Set the least significant bit
            
    # Mark presence of numbers in array 'b'
    for num in second:
        if num <= k:
            counts[num] |= 2  # Set the second least significant bit
            
    # c[i] counts how many numbers from 1 to k fall into category i:
    # 0: not present in either array
    # 1: present in 'a' only
    # 2: present in 'b' only
    # 3: present in both arrays
    c = [0] * 4
    for num in counts:
        c[num] += 1
    
    # If there are too many numbers only in 'a' or only in 'b', or not enough total numbers to cover [1..k]
    if c[1] > k // 2 or c[2] > k // 2 or c[1] + c[2] + c[3] < k:
        print("NO")
    else:
        print("YES")


def main():
    tc = int(input())
    for _ in range(tc):
        solve()


main()


# https://github.com/VaHiX/CodeForces/