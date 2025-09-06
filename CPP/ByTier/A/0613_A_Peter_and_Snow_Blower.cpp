/*
 * Problem URL : https://codeforces.com/contest/613/problem/A
 * Submit Date : 2025-09-04
 */

#include <stdio.h>
#include <math.h>
#include <algorithm>
#define nmax 100010
#define PI 3.14159265358979323846
#define eps 1e-8

using namespace std;

struct point
{
	int x, y;
};

int n;
point p, polygon[nmax];

double maxDist, minDist;

double sqr(double x)
{
	return x * x;
}

double dist(const point a, const point b)
{
	return sqrt(sqr(abs(a.x - b.x)) + sqr(abs(a.y - b.y)));
}

int main()
{
	scanf("%d %d %d", &n, &p.x, &p.y);

	maxDist = 0;
	minDist = 1e18;

	for (int i = 1; i <= n; i++) scanf("%d %d", &polygon[i].x, &polygon[i].y);

	polygon[0] = polygon[n];

	for (int i = 0; i < n; i++) {

		double ap = dist(p, polygon[i]);
		double bp = dist(p, polygon[i + 1]);
		double ab = dist(polygon[i], polygon[i + 1]);

		maxDist = max(maxDist, ap);
		maxDist = max(maxDist, bp);
		minDist = min(minDist, ap);
		minDist = min(minDist, bp);

		if (sqr(ap) + sqr(ab) < sqr(bp) || sqr(bp) + sqr(ab) < sqr(ap)) continue;

		double p = (ap + bp + ab) / 2;
		double S = sqrt(p * (p - ap) * (p - bp) * (p - ab));
		double h = 2 * S / ab;

		minDist = min(minDist, h);
	}

	printf("%.8f", PI * (sqr(maxDist) - sqr(minDist)));

	return 0;
}