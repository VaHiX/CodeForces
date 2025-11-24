# Problem: CF 1884 E - Hard Design
# https://codeforces.com/contest/1884/problem/E

"""
Algorithm: Hard Design
Purpose: For each cyclic shift of an array, determine the minimum number of operations (cnt) and the maximum coins (cost) obtainable.
Time Complexity: O(n) per test case
Space Complexity: O(n) per test case

The solution uses a combination of:
1. Sliding window techniques for maintaining maximum values
2. Stack-based computations to efficiently handle range updates
3. Prefix sums to calculate cost efficiently
4. Modular arithmetic for large numbers
"""

for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    ma = max(a)
    ans = ma - a[0] # Calculate base cnt for first element
    for i in range(1, n):
        ans += max(0, a[i - 1] - a[i]) # Add difference to cnt
    
    st = [0] # Stack to keep indices for monotonic processing
    hi = [0] * n # Array to store prefix sums of coins
    actvis = a[0] # Current active value for processing stack
    for i in range(1, n):
        if a[i] > actvis:
            hi[0] += i * (a[i] - actvis) # Update prefix sum for increasing values
            actvis = a[i]
    
    dob = [0] * (2 * n + 1) # Difference array for range updates
    kon = [0] * (2 * n + 1) # Storage for previous values
    
    for i in range(1, n):
        actvis = 0
        while True:
            if len(st) == 0: # Stack is empty, add contribution from start
                kon[i] += (a[i] - actvis) * i
                break
            if a[st[-1]] >= a[i]: # Current element is greater or equal
                kon[i] += (a[i] - actvis) * (i - st[-1] - 1)
                dob[st[-1] + 1] += (a[i] - actvis) * (i - st[-1] - 1)
                break
            if a[st[-1]] > actvis: # Process previous element's contribution
                kon[i] += (a[st[-1]] - actvis) * (i - st[-1] - 1)
                dob[st[-1] + 1] += (a[st[-1]] - actvis) * (i - st[-1] - 1)
                actvis = a[st[-1]]
            st.pop() # Remove processed element
        st.append(i) # Push current index
    
    dob2 = dob.copy() # Copy difference array for later use
    st3 = st.copy() # Copy stack for later use
    actvis = 0
    while True: # Process stack elements for final update
        if len(st3) == 0:
            break
        if a[st3[-1]] >= ma:
            dob2[st3[-1] + 1] += (a[st3[-1]] - actvis) * (n - st3[-1] - 1)
            break
        if a[st3[-1]] > actvis:
            dob2[st3[-1] + 1] += (a[st3[-1]] - actvis) * (n - st3[-1] - 1)
            actvis = a[st3[-1]]
        st3.pop()
    
    for i in range(1, n): # Calculate hi array from dob2
        if a[i] > a[i - 1]:
            hi[i] = hi[i - 1] - kon[i]
        else:
            hi[i] = hi[i - 1] + dob2[i]
    
    ans2 = sum(hi) % (10**9 + 7) # Final cost calculation
    st2 = []
    vich = 0
    for i in range(n):
        if i > 0:
            if a[i] > a[i - 1]:
                hi[i] = hi[i - 1] - kon[i]
            else:
                hi[i] = hi[i - 1] + dob[i]
        print(ans, ans2 % (10**9 + 7)) # Output results
        actvis = 0
        while True: # Process stack for vich updates
            if len(st2) == 0:
                vich -= (a[i] - actvis) * i
                break
            if a[st2[-1]] >= a[i]:
                vich -= (a[i] - actvis) * (i - st2[-1] - 1)
                break
            if a[st2[-1]] > actvis:
                vich -= (a[st2[-1]] - actvis) * (i - st2[-1] - 1)
                actvis = a[st2[-1]]
            st2.pop()
        st2.append(i)
        ans2 -= 2 * (hi[i] - vich) - (ma - a[i]) # Update ans2
        ans2 %= 10**9 + 7

        vich += ma - a[i] # Update vich for next iteration
        kon2 = 0
        actvis = 0

        while True: # Update stack and compute kon2
            if len(st) == 0:
                kon2 += (a[i] - actvis) * (i + n)
                break
            if a[st[-1]] >= a[i]:
                kon2 += (a[i] - actvis) * (n + i - st[-1] - 1)
                dob[st[-1] + 1] += (a[i] - actvis) * (n + i - st[-1] - 1)
                break
            if a[st[-1]] > actvis:
                kon2 += (a[st[-1]] - actvis) * (n + i - st[-1] - 1)
                dob[st[-1] + 1] += (a[st[-1]] - actvis) * (n + i - st[-1] - 1)
                actvis = a[st[-1]]
            st.pop()
        st.append(i + n)
        if a[i] < a[n + i - 1]:
            hi.append(hi[-1])
            ans2 += hi[-1]
            ans2 %= 10**9 + 7
            hi[-1] += ma - a[i]
            ans2 += hi[-1]
            ans2 %= 10**9 + 7
        else:
            hi.append(hi[-1])
            hi[-1] -= kon2
            ans2 += hi[-1]
            ans2 %= 10**9 + 7
            hi[-1] += ma - a[i]
            ans2 += hi[-1]
            ans2 %= 10**9 + 7
        ans -= ma - a[i]
        ans += ma - a[(i + 1) % n]
        ans -= max(0, a[i] - a[(i + 1) % n])
        ans += max(0, a[(n + i - 1) % n] - a[i])
        a.append(a[i])


# https://github.com/VaHiX/CodeForces/