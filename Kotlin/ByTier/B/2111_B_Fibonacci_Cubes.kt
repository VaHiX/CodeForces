// Problem: CF 2111 B - Fibonacci Cubes
// https://codeforces.com/contest/2111/problem/B

/*
B. Fibonacci Cubes
Algorithms/Techniques: Fibonacci sequence generation, sorting, greedy placement check

Time Complexity: O(n + m * log(m)) where n is the number of cubes and m is the number of boxes.
Space Complexity: O(n) for storing Fibonacci numbers.

There are n Fibonacci cubes, where the side of the i-th cube is equal to f_i,
where f_i is the i-th Fibonacci number.
In this problem, the Fibonacci numbers are defined as follows:
f_1 = 1
f_2 = 2
f_i = f_{i-1} + f_{i-2} for i > 2

There are also m empty boxes, where the i-th box has a width of w_i, a length of l_i,
and a height of h_i.

For each of the m boxes, you need to determine whether all the cubes can fit inside that box.
The cubes must be placed in the box following these rules:
- The cubes can only be stacked in the box such that the sides of the cubes are parallel to the sides of the box;
- Every cube must be placed either on the bottom of the box or on top of other cubes in such a way that all space below the cube is occupied;
- A larger cube cannot be placed on top of a smaller cube.

Input:
Each test consists of several test cases. The first line contains a single integer t (1 ≤ t ≤ 10^3) —
the number of test cases. The description of the test cases follows.
In the first line of each test case, there are two integers n and m (2 ≤ n ≤ 10, 1 ≤ m ≤ 2*10^5) —
the number of cubes and the number of empty boxes.
The next m lines of each test case contain 3 integers w_i, l_i, and h_i (1 ≤ w_i, l_i, h_i ≤ 150) —
the dimensions of the i-th box.

Output:
For each test case, output a string of length m, where the i-th character is equal to "1" if all n cubes
can fit into the i-th box; otherwise, the i-th character is equal to "0".
*/

fun main() = repeat(readLine()!!.toInt()){
    var (n, m) = readLine()!!.split(' ').map {it.toInt()} // Read n and m for current test case
    
    // Precompute Fibonacci numbers up to n
    val fib = IntArray(n + 1) { 0 }
    fib[1] = 1
    if (n > 1) fib[2] = 2
    for (i in 3..n) {
        fib[i] = fib[i-1] + fib[i-2]
    }

    // For each box, check if all cubes can fit
    for(i in 0..m-1) {
        var a = readLine()!!.split(' ').map {it.toInt()}.sorted() // Read and sort box dimensions
        
        // Compute required values using Fibonacci logic to simulate stacking constraints
        var b = 1
        var c = 2
        var d = 3    
        for (i in 3..n+1) {
            d = b + c // Generate next Fibonacci number - this is actually the pattern used here
            b = c
            c = d
        }
        
        // Check if all cubes fit; we compare against generated thresholds based on Fibonacci sequence
        if(a[0] >= b && a[1] >= b && a[2] >= c) print(1)
        else print(0)
    }
    println()
}


// https://github.com/VaHiX/CodeForces/