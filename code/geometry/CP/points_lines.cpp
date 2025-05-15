ld DEG_to_RAD(ld d) { return d*PI/180.0; }
ld RAD_to_DEG(ld r) { return r*180.0/PI; }

// rotate p by rad RADIANS CCW w.r.t origin (0, 0)
// NUM has to be ld
pt rotate(pt p, ld rad) {
  return make_pair(p.x*cos(rad) - p.y*sin(rad),
         p.x*sin(rad) + p.y*cos(rad));
}

// lines are (x,y) s.t. ax + by = c. AND b=0,1.
struct line { ld a, b, c; };

// gives line through p1, p2
line pointsToLine(pt p1, pt p2) {
  if (fabs(p1.x - p2.x) < EPS) // vertical line
    return { 1.0, 0.0, -(ld)p1.x };
  else {
    ld a =-(ld)(p1.y - p2.y) / (p1.x - p2.x);
    return {
      a,
      1.0,
      -(ld)(a * p1.x) - p1.y
    };
  }
}

// returns the reflection of p on the line through a and b
//NUM has to be ld
pt reflectionPoint(pt p, pt a, pt b) {
  pt m = proj(p, a, b);
  return m * 2 - p; }

// returns angle aob in rad in [0, 2 PI)
ld angle(pt a, pt o, pt b) {
  pt oa = a - o, ob = b - o;
  ld antw = atan2(ob.y, ob.x) - atan2(oa.y, oa.x);
  if(antw < 0)
    antw += 2 * PI;
  return antw;
}

// note: to accept collinear points, change `> 0'
// returns true if r is on the left side of line pq
bool ccw(pt p, pt q, pt r) {
  return ((q - p) ^ (r - p)) > 0; }