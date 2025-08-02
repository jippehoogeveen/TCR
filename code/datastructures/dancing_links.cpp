template <class T>
struct dancing_links {
  struct node {
    T item;
    node *l, *r;
	node(const T &_item, node *_l=NULL, node *_r=NULL)
      : item(_item), l(_l), r(_r) {
      if (l) l->r = this;
      if (r) r->l = this; } };
  node *front, *back;
  dancing_links() { front = back = NULL; }
  node *push_back(const T &item) {
    back = new node(item, back, NULL);
    if (!front) front = back;
    return back; }
  node *push_front(const T &item) {
    front = new node(item, NULL, front);
    if (!back) back = front;
    return front; }
  void erase(node *n) {
    if (!n->l) front = n->r; else n->l->r = n->r;
    if (!n->r) back = n->l; else n->r->l = n->l; }
  void restore(node *n) {
    if (!n->l) front = n; else n->l->r = n;
    if (!n->r) back = n; else n->r->l = n; } };

//1-based r[0] is front and l[0] is back
struct linked_list{
  vi l, r;
  ll size;
  linked_list(){ l.pb(0); r.pb(0);}
  linked_list(int n) : size(n) {
    l = vi(n + 1); r = vi(n + 1);
    REP(i,n + 1) l[i] = i - 1, r[i] = i + 1;
    r[n] = 0; l[0] = n; }
  void insert(ll i, ll il) {//Insert i after il (il = 0 is at front)
    ll ir = r[il];
    l[i] = il; r[i] = ir;
    r[il] = i; l[ir] = i;
    size++; }
  void push_back() {
    l.pb(-1), r.pb(-1);
    insert(sz(l) - 1, l[0]); }
  void erase(ll i) {
    ll il = l[i], ir = r[i];
    l[i] = -1; r[i] = -1;
    r[il] = ir; l[ir] = il;
    size--; }
  bool present(ll i) { return l[i] != -1;}
  vi list() {
    vi res;
    for(ll i = r[0]; i != 0; i = r[i]) res.pb(i);
    return res; } };