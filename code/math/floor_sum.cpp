ll floor_sum(ll n, ll a, ll b, ll c) {
    if(a < 0) c -= n * a, a *= -1;
    if (c == 0) return 1;
    if (c < 0) return 0;
    n = min(n, c / a);
    if (a % b == 0) return (n+1)*(c/b+1)-n*(n+1)/2*a/b;
    if (a >= b) return floor_sum(n,a%b,b,c)-a/b*n*(n+1)/2;
    ll t = (c-a*n+b)/b;
    return floor_sum((c-b*t)/b,b,a,c-b*t)+t*(n+1); }