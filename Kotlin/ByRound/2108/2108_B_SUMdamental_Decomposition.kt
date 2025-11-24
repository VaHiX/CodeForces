// Problem: CF 2108 B - SUMdamental Decomposition
// https://codeforces.com/contest/2108/problem/B

/*
 * Problem: B. SUMdamental Decomposition
 * Purpose: Given n and x, construct an array of n positive integers such that their XOR equals x,
 *          and find the minimum possible sum of such array elements.
 * 
 * Algorithm:
 * - If x == 0:
 *   - If n is even, output n (can use pairs like [1,1], [2,2], etc.)
 *   - If n is odd and >= 3, construct a sequence with minimal sum using 1, 2, ... up to n-3 and then adjust
 *   - If n < 3 and x == 0, impossible (at least 2 elements required for XOR of 0 with positive integers)
 * - If x != 0:
 *   - Count number of set bits in x (let's call it 'bits')
 *   - If 'bits' > n, output x directly; any array formed will have sum ≥ x
 *   - Otherwise, attempt to reduce the total by placing some 1s in the positions where we can minimize sum
 * 
 * Time Complexity: O(log x) per test case due to counting bits in x.
 * Space Complexity: O(1), only using constant extra space.
 */

import java.util.*

fun main() {
    val scanner = Scanner(System.`in`)
    val numberOfTestCases = scanner.nextInt()   
    for (i in 0 until numberOfTestCases) {      
        solveProblem(scanner)
    }
}

fun solveProblem(scanner: Scanner) {
    val n = scanner.nextInt()
    val x = scanner.nextInt()
    
    if(x == 0) {
        // Special case when XOR needs to be zero
        if(n % 2 == 0) {
            // For even n, we can use pairs of same numbers (e.g., [1,1], [2,2])
            println(n)
            return
        }
        else if(n >= 3){
            // For odd n >= 3, we use 1 + 2 + ... + (n-3) + some larger number to keep XOR = 0
            println(6 + n - 3)
            return
        }
        else {
            // Not enough elements to form valid array for XOR = 0
            println(-1) 
            return
        }
    }

    var copyNumber = x
    var totalCount = 0
    
    // Count number of set bits (1s) in binary representation of x
    while(copyNumber > 0){
        if(copyNumber % 2 == 1) {
            totalCount++
        }
        copyNumber /= 2 
    }

    // If bit count exceeds n, it's impossible to form a valid array with sum less than x
    if(totalCount > n) {
        println(x) 
        return
    }
    else {
        // Try forming the optimal solution
        if((n - totalCount) % 2 == 0){
            // Even difference, can balance using additional small elements
            println(n - totalCount + x)
            return
        }
        else {
            // Odd difference, adjust accordingly
            var current = n - totalCount + x
            if(x == 1) current += 3
            else current += 1
            println(current)
            return
        }
    }
}


// https://github.com/VaHiX/CodeForces/