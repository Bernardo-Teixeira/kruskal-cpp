#include <bits/stdc++.h>
using namespace std;

// Mesma estrutura de GrafoListaPeso.cpp: lista de adjacência com pesos
typedef vector<vector<pair<int,double>>> LP;
// Aresta (u, v, peso), usada na ordenação do Kruskal
typedef tuple<double,int,int> Aresta;

void leituraGrafo(LP &, int);
void escritaGrafo(LP &);
vector<Aresta> listaArestas(LP &);
int  encontrar(vector<int> &, int);
bool unir(vector<int> &, vector<int> &, int, int);
double kruskal(LP &, vector<Aresta> &);

int main()
{
    int n, m;
    cin >> n >> m;
    LP Grafo;
    Grafo.assign(n, vector<pair<int, double>>());
    leituraGrafo(Grafo, m);
    escritaGrafo(Grafo);

    vector<Aresta> agm;
    double custo = kruskal(Grafo, agm);

    cout << "Arestas da Arvore Geradora Minima:" << endl;
    for (auto &e : agm)
        cout << "(" << get<1>(e) << "," << get<2>(e) << ") w: " << get<0>(e) << endl;
    if ((int)agm.size() < n - 1)
        cout << "Grafo desconexo: floresta geradora minima." << endl;
    cout << "Custo total: " << custo << endl;
    cout << "Total Vertices: " << n << endl;
    cout << "Total Arestas: " << m << endl;
    return 0;
}

void leituraGrafo(LP &G, int m)
{
    int a, b;
    double c;
    while (m--)
    {
        cin >> a >> b >> c;
        G[a].push_back(make_pair(b, c));
        G[b].push_back(make_pair(a, c)); // grafo não direcionado
    }
}

void escritaGrafo(LP &G)
{
    int n = G.size();
    cout << "Lista de Adjacencia:" << endl;
    for (int u = 0; u < n; u++)
    {
        cout << u << ": ";
        for (auto v : G[u])
            cout << "[(" << u << "," << v.first << ") w: " << v.second << "] ";
        cout << endl;
    }
}

// Extrai cada aresta uma única vez (u < v) da lista de adjacência
vector<Aresta> listaArestas(LP &G)
{
    vector<Aresta> E;
    for (int u = 0; u < (int)G.size(); u++)
        for (auto &p : G[u])
            if (u < p.first)
                E.push_back(make_tuple(p.second, u, p.first));
    return E;
}

// Union-Find: busca com compressão de caminho
int encontrar(vector<int> &raiz, int x)
{
    if (raiz[x] != x)
        raiz[x] = encontrar(raiz, raiz[x]);
    return raiz[x];
}

// Union-Find: união por altura; retorna false se já estão no mesmo conjunto
bool unir(vector<int> &raiz, vector<int> &altura, int a, int b)
{
    a = encontrar(raiz, a);
    b = encontrar(raiz, b);
    if (a == b) return false;
    if (altura[a] < altura[b]) swap(a, b);
    raiz[b] = a;
    if (altura[a] == altura[b]) altura[a]++;
    return true;
}

double kruskal(LP &G, vector<Aresta> &agm)
{
    int n = G.size();
    vector<Aresta> E = listaArestas(G);
    sort(E.begin(), E.end());           // ordem não decrescente de peso

    vector<int> raiz(n), altura(n, 0);
    iota(raiz.begin(), raiz.end(), 0);    // cada vértice é seu próprio conjunto

    double custo = 0;
    for (auto &e : E)
    {
        double w; int u, v;
        tie(w, u, v) = e;
        if (unir(raiz, altura, u, v))     // aresta não forma ciclo
        {
            agm.push_back(e);
            custo += w;
            if ((int)agm.size() == n - 1) break;
        }
    }
    return custo;
}
