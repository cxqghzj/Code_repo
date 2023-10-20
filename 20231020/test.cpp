#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000050;
void read(int &x) {
	char ch; while(ch = getchar(), ch < '!'); x = ch - 48;
	while(ch = getchar(), ch > '!') x = (x << 3) + (x << 1) + ch - 48;
}
struct Q {int l, p;}; vector <Q> s[MAXN];
int n, m, a[MAXN], ans[MAXN][30], las[MAXN]; bool vis[MAXN];
struct D {
	int p, c;
	bool operator < (const D &b) const {return p > b.p;}
};
struct BITS {
	int t[MAXN];
	void modify(int x, int k) {for(; x; t[x] += k, x -= x&-x);}
	int query(int x) {int z = 0; for(; x <= n; z += t[x], x += x&-x); return z;}
} t[30];
int main() {
	read(n); read(m); for(int i = 1; i <= n; ++i) read(a[i]);
	for(int l, r, i = 1; i <= m; ++i) read(l), read(r), s[r].push_back((Q) {l, i});
	for(int i = 1; i <= n; ++i) {
		vector <D> q; vector <int> del;
		for(int j = max(1, a[i] - 11); j <= a[i] + 11; ++j)
			if(las[j] && las[j] > las[a[i]]) q.push_back((D) {las[j], j});
		vis[a[i]] = 1; q.push_back((D) {las[a[i]], -1}); q.push_back((D) {i, a[i]});
		sort(q.begin(), q.end());
		for(int U, L = 0, R = 0, j = 0; j < q.size() - 1; ++j) {
			if(~q[j].c) vis[q[j].c] = 1, del.push_back(q[j].c);
			for(; vis[a[i]-L-1]; ++L); for(; vis[a[i]+R+1]; ++R);
			U = L + R + 1;
			if(1 <= L && L <= 10) t[L].modify(q[j].p, -1), t[L].modify(q[j+1].p, 1);
			if(1 <= R && R <= 10) t[R].modify(q[j].p, -1), t[R].modify(q[j+1].p, 1);
			if(1 <= U && U <= 10) t[U].modify(q[j].p, 1), t[U].modify(q[j+1].p, -1);
		} vis[a[i]] = 0;
		for(int j = 0; j < del.size(); ++j) vis[del[j]] = 0;
		for(int j = 0; j < s[i].size(); ++j)
			for(int k = 1; k <= 10; ++k)
				ans[s[i][j].p][k] = t[k].query(s[i][j].l);
		las[a[i]] = i;
	}
	for(int i = 1; i <= m; ++i) {
		for(int j = 1; j <= 10; ++j)
			putchar(ans[i][j] % 10 + 48);
		putchar('\n');
	}
}


