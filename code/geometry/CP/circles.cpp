//0 is in circle, 1 on the border and 2 outside the circle
int insideCircle(pt p, pt c, NUM r) {
    NUM d = dist2(p,c), r2 = r * r;
    return d < r2 ? 0 : d == r2 ? 1 : 2; } //inside/border/outside

//c becomes center of the circle through p1 and p2 with radius r
//For other option, reverse p1 and p2
//Requires NUM = ld
bool circle2PtsRad(pt p1, pt p2, NUM r, pt &c) {
    ld d2 = dist2(p1,p2);
    ld det = r * r / d2 - 0.25;
    if (det < 0.0) return false;
    ld h = sqrt(det);
    c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
    c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
    return true; }