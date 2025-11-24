// Problem: CF 1201 A - Important Exam
// https://codeforces.com/contest/1201/problem/A

/*
 * Problem: A. Important Exam
 * Purpose: Given a multiple-choice test with n students and m questions,
 *          find the maximum possible total score for all students.
 *          Each question has 5 possible answers (A-E), and each question
 *          has a point value. Students' answers are known but correct
 *          answers are not. We are to assign correct answers optimally
 *          to maximize the sum of scores across all students.
 *
 * Algorithm:
 *   For each question, count how many times each answer (A-E) appears
 *   among students' responses. Assign the correct answer for that question
 *   to be the one which maximizes the number of students who get it right.
 *   Multiply this count by the point value of that question and accumulate.
 *
 * Time Complexity: O(n * m), where n is number of students, m is number of questions.
 * Space Complexity: O(n + m), for storing student answers and point values.
 */

#include <iostream>
#include <vector>
#include <string>

int main() {
  long n, m;
  std::cin >> n >> m;
  std::vector<std::string> w(n); // Store students' answers
  for (long p = 0; p < n; p++) {
    std::cin >> w[p]; // Read each student's answers
  }
  std::vector<long> a(m); // Store point values for each question
  for (long p = 0; p < m; p++) {
    std::cin >> a[p]; // Read point values
  }
  long total(0); // Total score accumulator
  for (long p = 0; p < m; p++) { // For each question
    std::vector<long> s(5, 0); // Count of each answer (A-E) for current question
    for (long u = 0; u < n; u++) { // Count answers from all students
      ++s[w[u][p] - 'A']; // Increment count for that letter
    }
    long mx(0); // Maximum count among A-E
    for (long u = 0; u < s.size(); u++) {
      mx = (mx > s[u]) ? mx : s[u]; // Find max count
    }
    total += a[p] * mx; // Add contribution of this question to total score
  }
  std::cout << total << std::endl;
  return 0;
}


// https://github.com/VaHiX/codeForces/