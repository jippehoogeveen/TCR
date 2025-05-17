const ld EPS = 1e-7, PI = acos(-1.0);
typedef ld NUM; // EITHER ld OR ll
typedef pair<NUM, NUM> pt;

pt operator+(pt p,pt q){ return {p.x+q.x,p.y+q.y}; }
pt operator-(pt p,pt q){ return {p.x-q.x,p.y-q.y}; }
pt operator*(pt p, NUM n) { return {p.x*n, p.y*n}; }

pt& operator+=(pt &p, pt q) { return p = p+q; }
pt& operator-=(pt &p, pt q) { return p = p-q; }

NUM operator*(pt p, pt q){ return p.x*q.x+p.y*q.y; }
NUM operator^(pt p, pt q){ return p.x*q.y-p.y*q.x; }

// square distance from p to q
NUM dist(pt p, pt q){
  return (q - p) * (q - p);
 }

// square distance from p to line ab
ld distPtLineSq(pt p, pt a, pt b) {
	p -= a; b -= a;
	return ld(p^b) * (p^b) / (b*b);
}
// square distance from p to linesegment ab
ld distPtSegmentSq(pt p, pt a, pt b) {
	p -= a; b -= a;
	NUM dot = p*b, len = b*b;
	if (dot <= 0) return p*p;
	if (dot >= len) return (p-b)*(p-b);
	return p*p - ld(dot)*dot/len;
}
// Test if p is on line segment ab
bool segmentHasPoint(pt p, pt a, pt b) {
	pt u = p-a, v = p-b;
	return abs(u^v) < EPS && u*v <= 0;
}

// projects p onto the line ab
// NUM has to be ld
pt proj(pt p, pt a, pt b) {
	p -= a; b -= a;
	return a + b*((b*p) / (b*b));
}

bool col(pt a, pt b, pt c) {
	return abs((a-b) ^ (a-c)) < EPS;
}

// note: to accept collinear points, change `> 0'
// returns true if r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
	return ((q - p) ^ (r - p)) > 0; }

// true => 1 intersection, false => parallel or same
bool linesIntersect(pt a, pt b, pt c, pt d) {
	return abs((a-b) ^ (c-d)) > EPS;
}

// Check lines intersect!
// NUM has to be ld
pt lineLineIntersection(pt a, pt b, pt c, pt d) {
	ld det = (a-b) ^ (c-d);
	return ((c-d)*(a^b) - (a-b)*(c^d)) * (1.0/det);
}

// dp, dq are directions from p, q
// intersection at p + t_i dp, for 0 <= i < return value
int segmentIntersection(pt p, pt dp, pt q, pt dq,
		pt &A, pt &B) {
	if (abs(dp * dp)<EPS)
		swap(p,q), swap(dp,dq); // dq=0
	if (abs(dp * dp)<EPS) {
		A = p; // dp = dq = 0
		return p == q;
	}

	pt dpq = q-p;
	NUM c = dp^dq, c0 = dpq^dp, c1 = dpq^dq;
	if (abs(c) < EPS) { // parallel, dp > 0, dq >= 0
		if (abs(c0) > EPS) return 0; // not collinear
		NUM v0 = dpq*dp, v1 = v0 + dq*dp, dp2 = dp*dp;
		if (v1 < v0) swap(v0, v1);

		v0 = max(v0, NUM(0));
		v1 = min(v1, dp2);

		A = p + dp * (ld(v0) / dp2);
		B = p + dp * (ld(v1) / dp2);

		return (v0 <= v1) + (v0 < v1);
	}

	if (c < 0) {
		c = -c; c0 = -c0; c1 = -c1;
	}

	A = p + dp * (ld(c1)/c);
	return 0 <= min(c0,c1) && max(c0,c1) <= c;
}

// line segment p-q intersect with line A-B.
// NUM has to be ld!
pt lineIntersectSeg(pt p, pt q,
	  pt A, pt B) {
	ld a = B.y - A.y;
	ld b = A.x - B.x;
	ld c = B.x * A.y - A.x * B.y;
	ld u = fabs(a * p.x + b * p.y + c);
	ld v = fabs(a * q.x + b * q.y + c);
	return make_pair((p.x*v + q.x*u) / (u+v),
				 (p.y*v + q.y*u) / (u+v)); }