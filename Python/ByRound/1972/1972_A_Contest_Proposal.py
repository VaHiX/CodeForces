# Problem: CF 1972 A - Contest Proposal
# https://codeforces.com/contest/1972/problem/A

"""
Algorithm: Two Pointers
Time Complexity: O(n)
Space Complexity: O(1)

This solution uses a two-pointer technique to determine the minimum number of new problems 
that need to be added to make sure each problem in array 'a' is at most the corresponding 
problem difficulty in array 'b'. 

We maintain a pointer 'piv' that tracks how many elements in 'a' have been matched with 
elements in 'b'. For each element in 'b', if the current element in 'a' (pointed by 'piv') 
is greater than the current element in 'b', we need to add a new problem (increment ans). 
Otherwise, we move the 'piv' pointer forward to match the next element in 'a'.

The key insight is that since both arrays are sorted, we can greedily match elements from 'a' 
to 'b' in order, and count how many times we need to "add" a new problem when 'a[piv]' exceeds 'b[i]'.
"""

for _ in range(int(input())):
    x = int(input())
    a = [int(i) for i in input().split()]
    b = [int(i) for i in input().split()]
    ans, piv = 0, 0
    for i in range(x):
        if a[piv] > b[i]:  # If current element in a is greater than in b, we need to add a problem
            ans += 1
        else:
            piv += 1  # Move to next element in a since it can be matched with current b[i]
        if piv == x:  # If all elements of a are processed, stop
            break
    print(ans)


# https://github.com/VaHiX/CodeForces/