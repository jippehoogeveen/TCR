#include <bits/extc++.h>
using namespace __gnu_pbds;
template<class TK,class TM> using order_tree = tree<TK,TM,less<TK>,rb_tree_tag, tree_order_statistics_node_update>;
template<class TK> using order_set = order_tree<TK,null_type>;

vi s;
order_set<ii> t;
void update( ll k, ll v ) {
	t.erase( ii{ s[k], k } );
	s[k] = v;
	t.insert( ii{ s[k], k } );
}

signed main() {
	ll n = 4;
	s.resize(n,0);
	rep(i,0,n) t.insert(ii{0,i});
	update( 2, 3 );
	cout << t.find_by_order( 2 )->y << endl;
	cout << t.order_of_key( ii{s[3],3} ) << endl;
}
/*
orderset<ll> s;
s.insert(5);
s.insert(2);
s.insert(3);
s.find_by_order(2);//5
s.order_of_key(3);//1
s.order_of_key(4);//2*/