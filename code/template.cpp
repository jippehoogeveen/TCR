#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> ii;
typedef vector<ll> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef vector<ld> vd;
typedef vector<vd> vvd;
typedef vector<string> vs;

#define x first
#define y second
#define pb push_back
#define eb emplace_back
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define REP(i,n) rep(i,0,n)
#define all(v) begin(v), end(v)
#define sz(v) ((int) (v).size())
#define rs resize

namespace std { template<class T1, class T2>
struct hash<pair<T1,T2>> { public:
	size_t operator()(const pair<T1,T2> &p) const {
		size_t x = hash<T1>()(p.x), y = hash<T2>()(p.y);
		return x ^ (y + 0x9e3779b9 + (x<<6) + (x>>2));
	}
}; }

void run() {
	
}

signed main() {
	// DON'T MIX "scanf" and "cin"!
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout << fixed << setprecision(20);
	run();
	return 0;
}
