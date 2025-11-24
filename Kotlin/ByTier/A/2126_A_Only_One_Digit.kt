// Problem: CF 2126 A - Only One Digit
// https://codeforces.com/contest/2126/problem/A

/*
A. Only One Digit
Algorithms/Techniques: Greedy algorithm using frequency counting of digits
Time Complexity: O(t * |s|) where t is number of test cases and |s| is length of string representation of x
Space Complexity: O(1) as we use a fixed-size BooleanArray of size 10

The problem asks to find the smallest non-negative integer y such that x and y share at least one common digit.
We use a greedy approach:
- For each test case, we first identify which digits appear in x
- Then we iterate from 0 to 9 to find the smallest digit that appears in x
- That digit is our answer since it's the smallest number (0-9) that shares a digit with x
*/
fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    repeat(t) {
        val s = readLine()!! // Read the string representation of the number x
        val f = BooleanArray(10) // Create a boolean array to track which digits (0-9) appear in s
        for (c in s) {
            f[c - '0'] = true // Mark the digit corresponding to character c as present
        }
        for (d in 0..9) {
            if (f[d]) {
                println(d) // Print the smallest digit that appears in x
                break
            }
        }
    }
}
fun <T> printa(a: List<T>) {
    println(a.joinToString(" "))
}
fun <T> print2d(vv: List<List<T>>) {
    for (r in vv) {
        println(r.joinToString(" "))
    }
}


// https://github.com/VaHiX/CodeForces/