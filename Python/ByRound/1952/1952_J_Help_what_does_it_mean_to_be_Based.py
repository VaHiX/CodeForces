# Problem: CF 1952 J - Help, what does it mean to be "Based"
# https://codeforces.com/contest/1952/problem/J

"""
Based Code Generator

This program generates different "based" code snippets depending on the input value x (1 to 4).
The snippets use a humorous programming language with slang terms to perform basic operations:

1. Sum of two integers (O(1) time, O(1) space)
2. Absolute value computation (O(1) time, O(1) space)
3. Finding maximum element in array (O(n) time, O(1) space)
4. Finding k-th largest element in array (O(n^2) worst case time, O(1) space)

Note: The actual implementation uses bubble sort for k-th largest element in this slang-based language.
"""

t = int(input())

if t == 1:
    print(
        """yoink a
yoink b
*slaps a on top of b*
yeet b
go touch some grass"""
    )

if t == 2:
    print(
        """yoink a
bruh b is lowkey just 0
rip this b fell off by a
vibe check a ratios b
simp for 7
bruh a is lowkey just b
yeet a
go touch some grass"""
    )

if t == 3:
    print(
        """yoink n
yoink a
bruh m is lowkey just a[0]
bruh i is lowkey just 1
vibe check n ratios i
simp for 9
yeet m
go touch some grass
vibe check a[i] ratios m
bruh m is lowkey just a[i]
*slaps 1 on top of i*
simp for 5"""
    )

if t == 4:
    print(
        """yoink n
yoink a
bruh i is lowkey just 0
vibe check n ratios i
simp for 10
yoink k
rip this k fell off by 1
yeet a[k]
go touch some grass
bruh j is lowkey just 0
bruh k is lowkey just 1
bruh l is lowkey just 2
vibe check l ratios n
simp for 24
vibe check a[j] ratios a[k]
simp for 20
bruh t is lowkey just a[j]
bruh a[j] is lowkey just a[k]
bruh a[k] is lowkey just t
*slaps 1 on top of j*
*slaps 1 on top of k*
*slaps 1 on top of l*
simp for 13
*slaps 1 on top of i*
simp for 4"""
    )


# https://github.com/VaHiX/CodeForces/