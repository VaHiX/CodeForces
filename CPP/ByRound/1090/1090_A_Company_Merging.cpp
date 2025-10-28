// Problem: CF 1090 A - Company Merging
// https://codeforces.com/contest/1090/problem/A

/*
 * Problem: Company Merging
 * Algorithm: Greedy approach with prefix maximum and summation
 * Time Complexity: O(N), where N is the total number of employees across all companies
 * Space Complexity: O(N), for storing employee salaries per company
 *
 * Description:
 * We are given n companies, each with m_i employees and their respective salaries.
 * We need to merge all companies into one such that at each step, we can only merge
 * two companies if their maximum salary is equal. To satisfy the condition,
 * we may increase salaries in a company, but must increase all employees' salaries by the same amount.
 * Goal: minimize total salary increases required to allow full merging.
 *
 * Key idea:
 * 1. For each company, compute the maximum salary among its employees.
 * 2. Compute the global maximum across all companies.
 * 3. To enable merging all companies into one, we need to raise every company's
 *    salary to at least the global maximum.
 * 4. The cost for a company is: (global_max - max_salary_in_company) * number_of_employees_in_company.
 * 5. Sum these costs across all companies to get the answer.
 */

#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std;
#define ll long long
const int N = 2e5 + 7;
int n, a[N], b[N], mx; // a[i] = number of employees in company i, b[i] = max salary in company i
ll ans;               // total salary increase needed

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]); // read number of employees in company i
    for (int j = 1; j <= a[i]; j++) { // read each employee's salary
      int p;
      scanf("%d", &p); 
      b[i] = max(b[i], p); // track max salary in company i
      mx = max(p, mx);     // track global max salary across all companies
    }
  }
  for (int i = 1; i <= n; i++)
    ans += 1LL * (mx - b[i]) * a[i]; // compute cost to raise company i's salaries to mx
  cout << ans;
}


// https://github.com/VaHiX/codeForces/