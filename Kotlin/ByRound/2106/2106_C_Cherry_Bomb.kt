// Problem: CF 2106 C - Cherry Bomb
// https://codeforces.com/contest/2106/problem/C

/*
C. Cherry Bomb
Purpose: Count the number of ways to fill missing elements in array `b` such that arrays `a` and `b` are complementary.
Algorithm: 
    - For complementary arrays, there must exist a constant x where a[i] + b[i] = x for all i.
    - If there are missing entries (denoted by -1), we check if they can be filled such that the condition holds.
    - Use constraints to validate if valid combinations are possible.

Time Complexity: O(n) per test case, due to single passes through arrays.
Space Complexity: O(1) excluding input storage, as only a few variables are used.
*/

fun main() = repeat(readLine()!!.toInt()){
    var (n, k) = readLine()!!.split(' ').map {it.toInt()} // Read n and k
    var a = readLine()!!.split(' ').map {it.toInt()}.toMutableList() // Read array a
    var b = readLine()!!.split(' ').map {it.toInt()}.toMutableList() // Read array b with possible -1s
    var c = 0 // Flag to check if any element in b is not -1
    var d = a.max()!! // Maximum value in array a
    var e = a.min()!! // Minimum value in array a
    var f = 1 // Result counter (1 means possible, 0 means impossible)
    
    // Check if any non-missing elements exist in b
    for (i in 0..n-1) {
       if(b[i]>-1) c=1 
    }
    
    // If no elements are present in b, then the only valid configuration is to make all a[i]+b[i] = k - d + e + 1
    if (c==0) f=k-d+e+1
    else {
        var g = -1 // To store the constant x that makes a[i] + b[i] = x
        for (i in 0..n-1) {
            // If current element is not missing
            if (b[i]>-1) {
                // Set x to be a[i] + b[i]
                if(g==-1) g=a[i]+b[i]
                else {
                    // Check consistency of x - if different values of x exist, impossible
                    if(g!=a[i]+b[i]) f=0                    
                }
            }
        }
        
        // Validate all elements satisfy constraints
        for (i in 0..n-1) {
            // If a[i] + b[i] exceeds k, it's invalid
            if(g-a[i]>k) f=0
            // If a[i] is greater than g, then b[i] must be negative (impossible since values are non-negative)
            if(a[i]>g) f=0
        }
    }
    println(f)
}


// https://github.com/VaHiX/CodeForces/