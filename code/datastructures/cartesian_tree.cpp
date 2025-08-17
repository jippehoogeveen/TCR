struct node {
  	ll x, y, size;
    node *l, *r;
    node(ll _x = 0, ll _y = 0)
      : x(_x), y(_y), size(1), l(NULL), r(NULL) { } };
ll tsize(node* t) { return t ? t->size : 0; }
ll tsum(node* t) { return t ? t->sum : 0; }
void augment(node *t) { //update all information here
    t->size = 1 + tsize(t->l) + tsize(t->r);
}
pair<node*,node*> split(node *t, ll x) {
    if (!t) return {NULL,NULL};
    if (t->x < x) {
        pair<node*,node*> res = split(t->r, x);
        t->r = res.x; augment(t);
        return make_pair(t, res.y); }
    pair<node*,node*> res = split(t->l, x);
    t->l = res.y; augment(t);
    return make_pair(res.x, t); }
node* merge(node *l, node *r) {
    if (!l) return r; if (!r) return l;
    if (l->y < r->y) {
        l->r = merge(l->r, r); augment(l); return l; }
    r->l = merge(l, r->l); augment(r); return r; }
node* find(node *t, ll x) {
    while (t) {
        if (x < t->x) t = t->l;
        else if (t->x < x) t = t->r;
        else return t; }
    return NULL; }
node* insert(node *t, ll x, ll y) {
    pair<node*,node*> res = split(t, x);
    return merge(res.x, merge(new node(x, y), res.y));
}
node* erase(node *t, ll x) {
    if (!t) return NULL;
    if (t->x < x) t->r = erase(t->r, x);
    else if (x < t->x) t->l = erase(t->l, x);
    else{node *old=t; t=merge(t->l,t->r); delete old;}
    if (t) augment(t); return t;
}
ll kth(node *t, ll k) {
    if (k < tsize(t->l)) return kth(t->l, k);
    if (k == tsize(t->l)) return t->x;
    return kth(t->r, k - tsize(t->l) - 1);
}