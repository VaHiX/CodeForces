// Problem: CF 1488 A - From Zero To Y
// https://codeforces.com/contest/1488/problem/A

/*
 * Problem: A. From Zero To Y
 * 
 * Algorithm/Technique: Mathematical approach to minimize operations.
 * 
 * The key insight is to decompose the target value y into parts:
 * - First, we use the largest possible multiples of x (using 10^p) to reduce the number of operations.
 * - Then, we handle the remainder using single unit additions.
 * 
 * For a given x and y:
 * 1. Compute y/x to determine how many times x fits into y (as a base number).
 * 2. Convert this base number to string and sum its digits — each digit corresponds to an operation of adding x * 10^p.
 * 3. Add the remainder (y % x) which requires unit additions.
 * 
 * Time Complexity: O(log y) per test case due to digit sum calculation.
 * Space Complexity: O(log y) for storing the string representation of y/x.
 */

fun main() =
    repeat(readLine()!!.toInt()) {
      val (x, y) = readLine()!!.split(" ").map { it.toInt() }
      println((y / x).toString().sumOf { it - '0' } + y % x)
    }


// https://github.com/VaHiX/CodeForces/