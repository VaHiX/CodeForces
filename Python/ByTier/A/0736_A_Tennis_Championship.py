# Contest 736, Problem A: Tennis Championship
# URL: https://codeforces.com/contest/736/problem/A

fib = [1, 1]
while fib[-1] <= 10**18:
    a, b = fib[-2], fib[-1]
    fib.append(a+b)
def process(n):   
    for i in range(len(fib)-1):
        if fib[i] <= n < fib[i+1]:
            return i-1
    
n = int(input())
print(process(n))
