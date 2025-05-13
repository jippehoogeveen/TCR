#include <bits/extc++.h>
using namespace __gnu_pbds;
template<class TK,class TM> using order_tree = tree<TK,TM,less<TK>,rb_tree_tag, tree_order_statistics_node_update>;
template<class TK> using order_set = order_tree<TK,null_type>;

order_set<ll> s;
s.insert(5);
s.insert(2);
s.insert(3);
s.find_by_order(2);//5
s.order_of_key(3);//1
s.order_of_key(4);//2