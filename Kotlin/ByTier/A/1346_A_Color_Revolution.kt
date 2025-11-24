// Problem: CF 1346 A - Color Revolution
// https://codeforces.com/contest/1346/problem/A

/*
 * Problem: Color Revolution
 * 
 * Purpose: Given total participants 'n' and multiplier 'k', distribute participants
 *          across 4 divisions such that:
 *          n2 = k * n1, n3 = k * n2, n4 = k * n3, and n1 + n2 + n3 + n4 = n
 * 
 * Algorithm:
 *   - Let n1 = x, then n2 = k*x, n3 = k^2*x, n4 = k^3*x
 *   - Total: x * (1 + k + k^2 + k^3) = n
 *   - So x = n / (1 + k + k^2 + k^3)
 *   - Then compute n1, n2, n3, n4 using x and k
 * 
 * Time Complexity: O(t) where t is number of test cases
 * Space Complexity: O(1) - only using a few variables
 */

fun main() =
    repeat(readLine()!!.toInt()) {
      val (n, k) = readLine()!!.split(" ").map { it.toInt() }
      // Calculate n1 as the base unit
      val n1 = n / (1 + k + k * k + k * k * k)
      // Print n1, n2, n3, n4 using the relationship n_i = k^(i-1) * n1
      println("$n1 ${n1*k} ${n1*k*k} ${n1*k*k*k}")
    }


// https://github.com/VaHiX/CodeForces/