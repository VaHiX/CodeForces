// Problem: CF 1999 A - A+B Again?
// https://codeforces.com/contest/1999/problem/A

/*
* Problem: A+B Again?
* Algorithm: Extract digits using integer division and modulo operations
* Time Complexity: O(t) where t is the number of test cases
* Space Complexity: O(1) - only using constant extra space
* 
* Techniques:
* - Extract first digit: n / 10
* - Extract second digit: n % 10
* - Sum the digits: (n / 10) + (n % 10)
*/

fun main() {
    val t = readLine()!!.toInt() // Read number of test cases
    for (test in 1..t) {
        val n = readLine()!!.toInt() // Read the two-digit number
        print("${n / 10 + n % 10}\n") // Calculate and print sum of digits
    }
}


// https://github.com/VaHiX/CodeForces/