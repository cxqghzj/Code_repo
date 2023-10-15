#include <iostream>
#include <algorithm>
#include <cstdio>
#include <array>
using namespace std;
#ifdef ONLINE_JUDGE

/* #define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1 << 21, stdin), p1 == p2) ? EOF : *p1+) */
/* char buf[1 << 23], *p1 = buf, *p2 = buf, ubuf[1 << 23], *u = ubuf; */

#endif
int read() {
	int p = 0, flg = 1;
	char c = getchar();
	while (c < '0' || c > '9') {
		if (c == '-') flg = -1;
		c = getchar();
	}
	while (c >= '0' && c <= '9') {
		p = p * 10 + c - '0';
		c = getchar();
	}
	return p * flg;
}
void write(int x) {
	if (x < 0) {
		x = -x;
		putchar('-');
	}
	if (x > 9) {
		write(x / 10);
	}
	putchar(x % 10 + '0');
}
const int N = 355;
array <array <array <short, N>, N>, N> f;
array <int, N> s, isl;
int k, siz;

int dfs(int l, int r, int k) {
	if (~f[l][r][k]) return f[l][r][k];
	if (k > ::k) return f[l][r][k] = 0;
	bool ans = 0;
	ans |= (!dfs(l + 1, r, siz - (k + s[l]) - (isl[r] - isl[l])));
	ans |= (!dfs(l, r - 1, siz - (k + s[r]) - (isl[r - 1] - isl[l - 1])));
	return f[l][r][k] = ans;
}
char strbuf[N];
int main() {
	freopen("beach.in", "r", stdin);
	freopen("beach.out", "w", stdout);
	for (int i = 0; i <= 350; i++)
		for (int j = 0; j <= 350; j++)
			for (int k = 0; k <= 350; k++)
				f[i][j][k] = -1;
	int n = read();
	k = read();
	scanf("%s", strbuf);
	string s = strbuf;
	s = " " + s;
	for (int i = 1; i <= n; i++)
		::s[i] = (s[i] == 'C') ? (siz++, 1) : 0;
	for (int i = 1; i <= n; i++)
		isl[i] = isl[i - 1] + ::s[i];
	/* for (int i = 1; i <= n; i++) */
		/* write(isl[i]), putchar(32); */
	/* puts(""); */
	if (dfs(1, n, 0)) puts("DA");
	else puts("NE");
	/* write(f[3][8][0]), puts(""); */
	return 0;
}
