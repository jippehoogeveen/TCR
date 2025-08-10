typedef vector<pt> poly;

// returns the perimeter: sum of Euclidean distances
// of consecutive line segments (polygon edges)
ld perimeter(const poly &P) {
	ld result = 0.0;
	REP(i, sz(P)-1)
	  result += dist(P[i], P[i+1]);
	return result; }

// Returns TWICE the area of a polygon (for integers)
NUM polygonTwiceArea(const poly &P) {
	NUM area = 0;
	REP(i,sz(P) - 1)
		area += P[i] ^ P[i + 1];
	return abs(area); // area < 0 <=> p ccw
}

// returns true if we always make the same turn
// throughout the polygon (strict)
bool isConvex(const poly &P) {
	int n = sz(P);
	if (n <= 3) return false; // point=2; line=3
	bool isLeft = ccw(P[0], P[1], P[2]);
	REP(i, n-2) if (ccw(P[i], P[i+1],
		  P[(i+2) == n ? 1 : i+2]) != isLeft ||
		  col(P[i], P[i+1], P[(i+2) == n ? 1 : i+2]))
		return false; // different sign -> concave
	return true; } // convex


bool insidePolygon(const poly &P, pt p, bool strict = true) {
	int n = 0;
	REP(i, sz(P) - 1) {
		// if p is on edge of polygon
		if (segmentHasPoint(p, P[i], P[i + 1])) return !strict;
		// or: if(distPtSegmentSq(p, pts[i], pts[i + 1]) <= EPS) return !strict;

		// increment n if segment intersects line from p
		n += (max(P[i].y, P[i + 1].y) > p.y && min(P[i].y, P[i + 1].y) <= p.y &&
			(((P[i + 1] - P[i])^(p-P[i])) > 0) == (P[i].y <= p.y));
	}
	return n & 1; // inside if odd number of intersections
}

// cuts polygon Q along the line formed by a -> b
// (note: Q[0] == Q[n-1] is assumed)
// NUM has to be ld
poly cutPolygon(pt a, pt b, const poly &Q) {
	poly P;
	REP(i, sz(Q)) {
		ld left1 = (b - a) ^ (Q[i] - a);
		ld left2 = 0;
		if (i != sz(Q)-1)
			left2 = (b - a) ^ (Q[i+1] - a);
		if (left1 > -EPS)
			P.pb(Q[i]); // Q[i] is left of ab
		if (left1 * left2 < -EPS)
			// edge Q[i]--Q[i+1] crosses line ab
				P.pb(pt()); lineIntersectSeg(Q[i], Q[i+1], a, b, P.back());
	}
	if (!P.empty() && !(P.back() == P.front()))
		P.pb(P.front()); // make P[0] == P[n-1]
	return P; }