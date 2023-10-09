//#define LawrenceSivan

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define INF 0x3f3f3f3f
#define re register
#define debug cout<<"!!!!!!!!!"<<endl;

const int maxn=2e5+5;

int n,m;

int a[maxn];

namespace Splay{
    int c[maxn][2],fa[maxn],size[maxn],val[maxn],mx[maxn],rub[maxn],top,tot,root,l[maxn],r[maxn],sum[maxn];
    #define ls(x) c[x][0]
    #define rs(x) c[x][1]

    inline void write(int u){
        if(ls(u))write(ls(u));
        printf("%d ",val[u]);
        if(rs(u))write(rs(u));
    }

    inline int dir(int x){
        return x==ls(fa[x])?0:1;
    }

    inline void set(int x,int px,int d){
        c[px][d]=x;
        fa[x]=px;
    }

    inline int rubbish(){
        return !top?++tot:rub[top--];
    }

    inline void push_up(int x){
        sum[x]=sum[ls(x)]+val[x]+sum[rs(x)];
        size[x]=size[ls(x)]+size[rs(x)]+1;
        mx[x]=max(max(mx[ls(x)],mx[rs(x)]),r[ls(x)]+val[x]+l[rs(x)]);
        l[x]=max(l[ls(x)],sum[ls(x)]+val[x]+l[rs(x)]);
        r[x]=max(r[rs(x)],sum[rs(x)]+val[x]+r[ls(x)]);
    }

    inline void rotate(int x){
        int f=fa[x],d=!dir(x);
        set(c[x][d],f,!d);
        set(x,fa[f],dir(f));
        set(f,x,d);
        push_up(f);
    }

    inline void splay(int x,int goal){
        for(;fa[x]!=goal;rotate(x))
            if(fa[fa[x]]!=goal)
                rotate(dir(x)^dir(fa[x])?x:fa[x]);
        push_up(x);
        if(goal==0)root=x;
    }

    inline int new_node(int x){
        int u=rubbish();
        ls(u)=rs(u)=fa[u]=0;
        size[u]=1;
        val[u]=mx[u]=sum[u]=x;
        l[u]=r[u]=max(x,0);
        return u;
    }

    inline int build(int l,int r){
        if(l>r)return 0;

        if(l==r)return new_node(a[l]);

        int mid=(l+r)>>1,u=new_node(a[mid]);

        ls(u)=build(l,mid-1);
        rs(u)=build(mid+1,r);

        fa[ls(u)]=fa[rs(u)]=u;

        push_up(u);

        return u;
    }

    inline int kth(int x) {
        int u=root;
        while(1) {
            if(x<size[ls(u)]+1)u=ls(u);
            else if(x==size[ls(u)]+1)return u;
            else x-=size[ls(u)]+1,u=rs(u);
        }
    }

    inline void insert(int pos,int w){
        int x=kth(pos),y=kth(pos+1);
        splay(x,0);splay(y,x);
        int u=new_node(w);
        ls(y)=u;
        fa[u]=y;
        push_up(y);push_up(x);
    }    

    inline void remove(int u){
        rub[++top]=u;
    }

    inline void Delete(int pos){
        int x=kth(pos),y=kth(pos+2);
        splay(x,0);splay(y,x);
        remove(ls(y));
        ls(y)=0;
        push_up(y);push_up(x);
    }

    inline int split(int l,int r){
        l=kth(l);r=kth(r+2);
        splay(l,0);
        splay(r,l);
        return ls(r);
    }

    inline int query(int l,int r){
        int u=split(l,r);
        return mx[u];
    }

    inline void update(int pos,int w){
        pos=kth(pos+1);
        splay(pos,0);
        val[pos]=w;
        push_up(pos);
    }
}   

using namespace Splay;

char op[5];

template<typename T>
inline void read(T &x){
    x=0;T f=1;char ch=getchar();
    while (!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
    while (isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    x*=f;
}

signed main() {
/* #ifdef LawrenceSivan */
    /* freopen("aa.in","r", stdin); */
    /* freopen("aa.out","w", stdout); */
/* #endif */
    read(n);

    mx[0]=a[1]=a[n+2]=-INF;
    for(re int i=1;i<=n;i++){
        read(a[i+1]);
    }
    
    root=build(1,n+2);

    // write(root);
    
    read(m);

    for(re int i=1;i<=m;i++){
        cin>>op;
        if(op[0]=='I'){
            int pos,w;
            read(pos),read(w);
            insert(pos,w);
            // write(root);

        }
        if(op[0]=='D'){
            int pos;
            read(pos);
            Delete(pos);
            // write(root);
        }
        if(op[0]=='R'){
            int pos,w;
            read(pos),read(w);
            update(pos,w);
            // write(root);
        }
        if(op[0]=='Q'){
            int l,r;
            read(l),read(r);
            printf("%d\n",query(l,r));
            // write(root);
        }

    }


    return 0;
}
