// returns the max squared distance between 2 points in hull
NUM maxDist2(vector<pt> &hull) {
	int n = hull.size(), b = 1;
	if (n <= 1) return 0;
	NUM ret = 0;
	for (int a = 0; a < n; a++) {
		pt e = hull[(a + 1) % n] - hull[a];
		while ((e ^ (hull[(b + 1) % n] - hull[b])) > 0) b++;
		ret = max(ret, dist2(hull[a], hull[b]));
	}
	return ret;
}
// returns the squared width of the convex hull
ld width2(vector<pt> &hull) {
	int n = hull.size(), b = 1;
	if (n <= 1) return 0;
	ld ret = 1e20;
	for (int a = 0; a < n; a++) {
		pt e = hull[(a + 1) % n] - hull[a];
		while ((e ^ (hull[(b + 1) % n] - hull[b])) > 0) b = (b + 1) % n;
		ret = min(ret, (ld)(e ^ (hull[b] - hull[a])) / sqrt(e * e));
	}
	return ret;
}