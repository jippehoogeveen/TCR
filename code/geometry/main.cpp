const ld EPS = 1e-7, PI = acos(-1.0);
typedef ld NUM; // EITHER ld OR ll
typedef pair<NUM, NUM> pt;
typedef vector<pt> poly;

pt operator+(pt p,pt q){ return {p.x+q.x,p.y+q.y}; }
pt operator-(pt p,pt q){ return {p.x-q.x,p.y-q.y}; }
pt operator*(pt p, NUM n) { return {p.x*n, p.y*n}; }

pt& operator+=(pt &p, pt q) { return p = p+q; }
pt& operator-=(pt &p, pt q) { return p = p-q; }

NUM operator*(pt p, pt q){ return p.x*q.x+p.y*q.y; }
NUM operator^(pt p, pt q){ return p.x*q.y-p.y*q.x; }

// square distance from p to q
NUM dist2(pt p, pt q){
  return (q - p) * (q - p);
 }

//Normal distance from p to q
ld dist(pt p, pt q) { return sqrt(dist2(p,q)); }

// distance from p to line ab
ld distPtLine(pt p, pt a, pt b) {
	p -= a; b -= a;
	return sqrt(ld(p^b) * (p^b) / (b*b));
}

// distance from p to linesegment ab
ld distPtSegment(pt p, pt a, pt b) {
	p -= a; b -= a;
	NUM dot = p*b, len = b*b;
	if (dot <= 0) return sqrt(p*p);
	if (dot >= len) return sqrt((p-b)*(p-b));
	return sqrt(p*p - ld(dot)*dot/len);
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

// Test if p is on line segment ab
bool segmentHasPoint(pt p, pt a, pt b) {
	pt u = p-a, v = p-b;
	return abs(u^v) < EPS && u*v <= 0;
}

// Check lines intersect!
// NUM has to be ld
pt lineLineIntersection(pt a, pt b, pt c, pt d) {
	ld det = (a-b) ^ (c-d);
	return ((c-d)*(a^b) - (a-b)*(c^d)) * (1.0/det);
}

// Check lines intersect!
// Num has to be ld
bool segmentIntersection(pt a, pt b, pt c, pt d, pt& res) {
	res = lineLineIntersection(a, b, c, d);
	return segmentHasPoint(res,a,b) && segmentHasPoint(res, c, d);
}

// Lines can be parallel: segments overlap from seg(start, end)
// 0 = no intersect, 1 = 1 lines not parallel (res = start), 2 = lines parallel
// Num has to be ld
int segmentIntersection(pt a, pt b, pt c, pt d, pt& start, pt& end) {
	pt d1 = b - a, d2 = d - c;
	if(abs(d1 ^ d2) > EPS) return segmentIntersection(a, b, c, d, start);
	if(abs((c - a) ^ d1) > EPS) return 0;
	if(d1 * d2 < 0) swap(c,d), d2 = d - c;
	ld s = max((ld)0, (c - a) * d1), e = min(d1 * d1, (d - a) * d1);
	s /= (d1 * d1), e /= (d1 * d1);
	if(s > e + EPS) return 0;
	start = a + d1 * s; end = a + d1 * e; return 2;
}

// line segment p-q intersect with line A-B.
// NUM has to be ld!
bool lineIntersectSeg(pt p, pt q, pt a, pt b, pt& res) {
	res = lineLineIntersection(p,q,a,b);
	return segmentHasPoint(res,p,q);
}