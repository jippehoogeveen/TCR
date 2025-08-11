// the convex hull consists of: { pts[ret[0]], pts[ret[1]], ... pts[ret.back()] } in counterclockwise order
vi convexHull(const poly &pts) {
	if (pts.empty()) return vi();
	vi ret, ord;
	int n = sz(pts), st = min_element(all(pts)) - pts.begin();
	REP(i, n)
		if (pts[i] != pts[st]) ord.pb(i);
	sort(all(ord), [&pts,&st] (int a, int b) {
		pt p = pts[a] - pts[st], q = pts[b] - pts[st];
		return (p ^ q) != 0 ? (p ^ q) > 0 : p * p > q * q;
	});
	ord.pb(st); ret.pb(st);
	for (int i : ord) {
		// use '>=' in ccw to include ALL points on the hull-line
		for(int s = sz(ret) - 1; s > 1 && !ccw(pts[ret[s - 1]], pts[ret[s]], pts[i]); s--)
			ret.pop_back();
		ret.pb(i);
	}
	ret.pop_back();
	return ret;
}