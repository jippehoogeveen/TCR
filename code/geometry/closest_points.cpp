poly pts;

struct byY {
	bool operator()(int a, int b) const { return pts[a].y < pts[b].y; }
};

inline NUM dist(ii p) { pt a = (pts[p.x] - pts[p.y]); return a * a; }

ii minpt(ii p1, ii p2) { return dist(p1) < dist(p2) ? p1 : p2; }

// closest pts (by index) inside pts[l ... r - 1], with sorted y values in ys
// check pts is sorted on x!
ii closest(int l, int r, vi &ys) {
	if (r - l == 2) { // don't assume 1 here.
		ys = { l, l + 1 };
		sort(all(ys), byY());
		return ii(l, l + 1);
	} else if (r - l == 3) { // brute-force
		ys = { l, l + 1, l + 2 };
		sort(all(ys), byY());
		return minpt(ii(l, l + 1), minpt(ii(l, l + 2), ii(l + 1, l + 2)));
	}
	int m = (l + r) / 2; vi yl, yr;
	ii delta = minpt(closest(l, m, yl), closest(m, r, yr));
	NUM ddelta = dist(delta), xm = (pts[m-1].x + pts[m].x) / 2;
	merge(all(yl), all(yr), back_inserter(ys), byY());
	deque<int> q;
	for (int i : ys) if (abs(pts[i].x - xm) <= ddelta) {
		for (int j : q) delta = minpt(delta, ii(i, j));
		q.pb(i);
		if (sz(q) > 8) q.pop_front(); // magic from Introduction to Algorithms.
	}
	return delta;
}