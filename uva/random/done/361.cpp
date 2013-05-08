#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cmath>
#include <algorithm>
#include <utility>
#include <stack>
#include <vector>
#include <queue>
#include <set>
#include <map>

using namespace std;

#define fori(i, n) for(int i=0;i<(n);i++)
#define forr(i, ini, fim) for(int i=ini;i<=(fim);i++)
#define tr(T, i) for (typeof(T.begin()) i=T.begin(); i != T.end(); i++)
#define sz size()
#define all(x) (x).begin(), (x).end()
#define pb push_back
#define mp make_pair
#define TRACE(x...) x
#define WATCH(x) TRACE(cout << #x"=" << x << endl)
#define EPS 1e-6
#define INF 1e12
const double PI = 2*acos(0);

typedef pair<double, double> pdd;
typedef vector<pdd> vpdd;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

//compara dois doubles, retornando 1 se x > y, 0 se x == y e -1 se x < y
int cmpD(double x, double y=0, double tol = EPS) { return (x <= y+tol) ? (x+tol < y) ? -1 : 0 : 1; }

//retorna um angulo entre 0 e 2*PI
double positive_angle(double a) {
    while(cmpD(a) < 0) a += 2*PI;
    while(cmpD(a, 2*PI) >= 0) a -= 2*PI;
    return a;
}

//recebe um angulo entre 0 e 360, retorna um angulo entre -PI e PI
double canonic_angle(double a) {
    a = a * PI / 180;
    while(cmpD(a) < -PI) a += 2*PI;
    while(cmpD(a, PI) >= 0) a -= 2*PI;
    return a;
}

//verifica se o angulo b esta entre os angulos a e c
bool between(double a, double b, double c) { 
    a = positive_angle(a); b = positive_angle(b); c = positive_angle(c);
    int ret = b <= max(a, c) && b >= min(a, c);
    if(cmpD(fabs(c-a), PI) > 0) return 1 - ret;
    return ret;
}

struct pt {
    double x, y;

    pt(double x=0, double y=0): x(x), y(y) {}

    pt operator +(pt p) { return pt(x+p.x, y+p.y); }
    pt operator -(pt p) { return pt(x-p.x, y-p.y); }
    pt operator *(double c) { return pt(x*c, y*c); }
    pt operator /(double c) { return pt(x/c, y/c); }
    double operator *(pt p) { return x*p.x + y*p.y; }
    double operator %(pt p) { return x*p.y - y*p.x; }
    int cmp(pt p) const { 
        int t = cmpD(x, p.x);
        return t ? t : cmpD(y, p.y);
    }
    bool operator ==(pt p) { return cmp(p) == 0; }
    bool operator !=(pt p) { return cmp(p) != 0; }
    bool operator <(const pt &p)const { return cmp(p) < 0; }
    bool operator >(const pt &p)const { return cmp(p) > 0; }
    friend ostream& operator <<(ostream& o, pt p) { return o << "(" << p.x << "," << p.y << ")"; }
};

pt pivot;

typedef vector<pair<pt, pt> > vppp;
typedef vector<pt> polygon;
typedef pair<pt, pt> segment;

//retorna distancia entre dois pontos, se apenas um for passado, considera o outro a origem
double abs(pt p, pt q = pt()) { return hypot(p.x-q.x, p.y-q.y); }

//retorna o argumento do ponto p
double arg(pt p) { return atan2(p.y, p.x); }

//retorna 0 se o ponto r esta na reta pq, 1 se esta na esquerda e -1 se esta na direita
int ccw(pt p, pt q, pt r) { return cmpD((q-p) % (r-p)); }

//verifica se o ponto q esta entre os pontos p e r
bool between(pt p, pt q, pt r) { return ccw(p, q, r) == 0 && cmpD((p-q) * (r-q)) <= 0; }

//retorna o valor do menor angulo pqr
double angle(pt p, pt q, pt r) { pt u=p-q, v=r-q; return atan2(u % v, u * v); }

//retorna true se o angulo pqr eh maior que PI e false cc
bool large_angle(pt p, pt q, pt r) { return ccw(p, r, q) < 0; }

//retorna a projecao do ponto a no ponto b
pt project(pt a, pt b) { return b * ((a*b) / (b*b)); }

//normaliza um vetor, retornando false caso ele seja o vetor nulo
bool normalize(pt &p) {
    double r = abs(p);
    if(!cmpD(r)) return false;
    p.x /= r; p.y /= r;
    return true;
}

//determina o ponto de intersecao entre as retas pq e rs
pt line_intersect(pt p, pt q, pt r, pt s) {
    pt a=q-p, b=s-r, c(p%q, r%s);
    if(cmpD(a % b) == 0) return pt(INF, INF);
    return pt(pt(a.x, b.x) % c , pt(a.y, b.y) % c) / (a % b);
}

//true se os segmentos pq e rs tem intersecao, false cc
bool seg_intersect(pt p, pt q, pt r, pt s) {
    if(between(p, r, q) || between(p, s, q) || between(r, p, s) || between(r, q, s)) return true;
    pt a = line_intersect(p, q, r, s);
    return between(p, a, q) && between(r, a, s);
}

//distancia entre um ponto e uma reta
double dist_pt_line(pt p, pt a, pt b = pt()) { return abs(p, a + project(p-a, b-a)); }

//distancia entre um ponto e um segmento de reta
double dist_pt_seg(pt p, pt a, pt b) {
    pt pp = a + project(p-a, b-a);
    if(between(a, pp, b)) return abs(p, pp);
    return min(abs(p, a), abs(p, b));
}

//distancia entre dois segmentos de reta
double dist_seg_seg(pt p, pt q, pt r, pt s) {
	if(seg_intersect(p, q, r, s)) return 0;
    return min(min(dist_pt_seg(p, r, s), dist_pt_seg(q, r, s)), min(dist_pt_seg(r, p, q), dist_pt_seg(s, p, q)));
}

//retorna 1 se p esta fora da circunferencia, 0 se esta em cima e -1 se esta dentro
int in_circle(pt p, pt o, double r) { return cmpD(abs(p, o), r); }

//retorna o circuncentro do triangulo pqr
pt circumcenter(pt p, pt q, pt r) {
    pt a=p-r, b=q-r, c=pt(a*(p+r)/2, b*(q+r)/2);
    return pt(c % pt(a.y, b.y), pt(a.x, b.x) % c / (a % b));
}

//dados o ponto p e a circunferencia definida por o e r
//retorna os dois pontos de tangencia de p para a circunferencia
pair<pt, pt> tangents(pt p, pt o, double r) {
    double a, b, c, teta1, teta2;
    a = (o.x-p.x)*(o.x-p.x) - r*r;
    b = -2*(o.x-p.x)*(o.y-p.y);
    c = (o.y-p.y)*(o.y-p.y) - r*r;
    if(cmpD(a) == 0) {
        teta1 = acos(0);
        teta2 = atan2(-c, b);
    } else {
        teta1 = atan2(-b+sqrt(b*b-4*a*c), 2*a);
        teta2 = atan2(-b-sqrt(b*b-4*a*c), 2*a);
    }
    pt p1 = p + project(o-p, pt(cos(teta1), sin(teta1))); 
    pt p2 = p + project(o-p, pt(cos(teta2), sin(teta2))); 
    return mp(p1, p2);
}


//dadas a reta definida pelos pontos a e b, o centro o da circunferencia e o raio r
//retorna um vetor com os pontos de intersecao entre a reta e a circunferencia
//o vetor pode ter tamanhos 0, 1 ou 2, dependendo da quantidade de pontos de intersecao
vector<pt> cuts(pt a, pt b, pt o, double r) {
    vector<pt> resp;
    pt op = a+project(o-a, b-a);
    int flag = cmpD(abs(op, o), r);
    if(flag == 0) resp.pb(op);
    if(flag == -1) {
        double d = sqrt(r*r - (o-op)*(o-op));
        resp.pb(op - (b-a)*d/abs(b-a));
        resp.pb(op + (b-a)*d/abs(b-a));
    }
    return resp;
}

//dados o ponto p em que se localiza um canhao, o centro o da circunferencia, o raio r,
//o angulo de disparo a e o angulo de espalhamento t
//determina a area que o tiro faz na circunferencia
double cannon_area(pt p, pt o, double r, double a, double t) {
    double ST,S1,S2,h1,h2,teta1,teta2,ang1,ang2,angtg1,angtg2;
    ST = PI * r * r;
    ang1 = (a - t/2)*PI/180;
    ang2 = (a + t/2)*PI/180;
    pair<pt, pt> tg = tangents(p, o, r);
    angtg1 = arg(tg.first-p);
    angtg2 = arg(tg.second-p);
    h1 = min(dist_pt_line(o, p, p+pt(cos(ang1), sin(ang1))), r);
    h2 = min(dist_pt_line(o, p, p+pt(cos(ang2), sin(ang2))), r);
    teta1 = acos(h1/r);
    S1 = between(angtg1, ang1, angtg2) * r * r * (teta1  - sin(2*teta1)/2);
    teta2 = acos(h2/r);
    S2 = between(angtg1, ang2, angtg2) * r * r * (teta2  - sin(2*teta2)/2); 
    if(between(ang1, arg(o-p), ang2)) return ST - S1 - S2;
    return fabs(S1 - S2);
}

//dado um vetor qualquer v de segmentos de reta
//retorna um vetor com a uniao de todos esses segmentos (segmentos disjuntos e ordenados)
vppp join(vppp v) {
    vppp u;
    if(v.empty()) return v;
    sort(all(v));
    u.pb(v[0]);
    for(int i=1; i<v.sz;i++) {
        if(v[i].first > u[u.sz-1].second) u.pb(v[i]);
        else u[u.sz-1].second = max(u[u.sz-1].second, v[i].second);
    }
    return u;
}

//dados um vetor v disjunto e ordenado de segmentos de reta e os pontos ini e fim
//retorna um vetor com a uniao de todos os segmentos que estao contidos no segmento (ini,fim) e nao possuem intersecao com v
vppp reverse(vppp v, pt ini, pt fim) {
    vppp u;
    if(v.empty()) u.pb(mp(ini, fim));
    else {
        fori(i, v.sz) {
            v[i].first = min(fim, max(ini, v[i].first));
            v[i].second = min(fim, max(ini, v[i].second));
        }
        if(v[0].first != ini) u.pb(mp(ini, v[0].first));
        for(int i=1;i<v.sz;i++) if(v[i].first > v[i-1].second) u.pb(mp(v[i-1].second, v[i].first));
        if(v[v.sz-1].second != fim) u.pb(mp(v[v.sz-1].second, fim));
    }
    return u;
}

//dados o ponto p em que esta uma lampada, o centro da circunferencia, o raio e os pontos ini e fim que definem um anteparo
//retorna o segmento de reta (p1,p2) aonde estara localizada a sombra produzida pela lampada no anteparo
//se nenhuma sombra for produzida, retorna um segmento de comprimento nulo
pair<pt, pt> shadow(pt p, pt o, double r, pt ini, pt fim) {
    double d1 = dist_pt_line(p, ini, fim);
    double d2 = dist_pt_line(o, ini, fim);
    if(cmpD(d1, d2-r) <= 0) return mp(pt(), pt());
    pair<pt, pt> tg = tangents(p, o, r);
    pt p1 = line_intersect(p, tg.first, ini, fim);  
    pt p2 = line_intersect(p, tg.second, ini, fim);  
    if(p1 > p2) swap(p1, p2);
    if(cmpD(d1, d2+r) <= 0) {
        pt pl = ini + project(p, fim - ini);
        pt pc = ini + project(o, fim - ini);
        if(p2 == pt(INF, INF)) {
            if(pl > pc) p2 = pt(-INF, -INF);
            else swap(p1, p2);
        } 
        else if(pl > pc) p2 = pt(-INF, -INF);
        else p1 = pt(INF, INF);
        swap(p1, p2);
    }
    return mp(p1, p2);
}

//dado um ponto inicial, o angulo de tiro e a distancia d, retorna o ponto de destino
pt shot(pt p, double teta, double d=1) { return p + pt(cos(teta), sin(teta))*d;  }

//funcao para ordenar os pontos em sentido horario
bool clockwise(pt p, pt q) {
    double a = positive_angle(arg(p-pivot));
    double b = positive_angle(arg(q-pivot));
    if(cmpD(a, b) == 0) return abs(p, pivot) < abs(q, pivot);
    return a < b;
}

bool radial_lt(pt p, pt q) {
    pt P = p - pivot, Q = q - pivot;
    double R = P % Q;
    if(cmpD(R)) return cmpD(R) > 0;
    return cmpD(P*P, Q*Q) < 0;
}

//GRAHAM SCAN
polygon convex_hull(vector<pt>& T) {
    int i, j=0, k, n=T.sz; polygon U(n);
    pivot = *min_element(all(T));
    sort(all(T), radial_lt);
    for(k=n-2; k>=0 && ccw(T[0], T[n-1], T[k]) == 0; k--) ;
    reverse((k+1) + all(T));
    for(i=0;i<n;i++) {
        while(j>1 && ccw(U[j-1], U[j-2], T[i]) >= 0) j--;
        U[j++] = T[i];
    }
    U.erase(j + all(U));
    return U;
}

//JARVIS MARCH
polygon jarvis_convex_hull(vector<pt> v) {
    int vis[10000], p=0, np;
    polygon u;
    fori(i, v.sz) {
        vis[i]=0;
        if(v[i] < v[p]) p = i;
    }
    while(!vis[p]) {
        vis[p] = 1; u.pb(v[p]); np = -1;
        fori(i, v.sz) if(i != p) if(np == -1 || ccw(v[p], v[np], v[i]) == -1) np = i;
        p = np;
    }
    return u;
}

double poly_area(polygon T) {
    double s=0; int n=T.sz;
    fori(i, n) s += T[i] % T[(i+1)%n];
    return s/2;
}

// Retorna 1 se o ponto p está dentro do polígono T
// o polígono p precisa estar ordenado no sentido horário
int in_poly(pt p, polygon T)
{
    if(T.sz > 2)
    {
        if(ccw(T[T.sz-1],T[0],p) < 0) return 0;
        for(int i=1;i<T.sz;i++) if(ccw(T[i-1],T[i],p) < 0) return 0;
        return 1;
    }
    else if(T.sz == 2) if(between(T[0],p,T[1])) return 1;
    else if(T.sz == 1) if(T[0] == p) return 1;
    return 0;
}

int main()
{
    int c, r, o;
    int i, x, y, t=1;
    pt cit;
    vector <pt> cops, robs;
    polygon cop, rob;
    while(scanf("%d%d%d", &c, &r, &o) && (c || r || o))
    {
        cops.clear();
        robs.clear();
        cop.clear();
        rob.clear();
        for(i=0;i<c;i++)
        {
            scanf("%d%d", &x, &y);
            cops.pb(pt(x,y));
        }
        for(i=0;i<r;i++)
        {
            scanf("%d%d", &x, &y);
            robs.pb(pt(x,y));
        }
        if(c > 2) cop = convex_hull(cops);
        if(r > 2) rob = convex_hull(robs);
        printf("Data set %d:\n", t++);
        for(i=0;i<o;i++)
        {
            scanf("%d%d", &x, &y);
            cit = pt(x,y);
            printf("     Citizen at (%d,%d) is ", x, y);
            if(in_poly(cit,cop)) printf("safe.\n");
            else if(in_poly(cit,rob)) printf("robbed.\n");
            else printf("neither.\n");
        }
        printf("\n");
    }
    return 0;
}

