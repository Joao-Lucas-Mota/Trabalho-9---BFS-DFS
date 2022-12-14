/* Joao Lucas Mota Nogueira da Costa
Sua  tarefa  será  imprimir  a  Pilha  do  DFS  e  a  Fila  do  BFS  quando
aplicadas  a  um  grafo  de  100 vértices cujos índices serão criados a partir
de números aleatórias gerados entre 1 e 1000. Nesta tarefa você pode usar todos
os algoritmos que desenvolveu ao longo desta disciplina.
*/

#include <iostream>
#include <list>
#include <map>
#include <random>
#include <stack>

using namespace std;

class TNo {
public:
  int w;
  TNo *prox;
};

class TGrafo {
private:
  int n;
  int m;
  TNo **list_adj;
  vector<list<int>> adjBFS;
  map<int, list<int>> adjDFS;
  map<int, bool> visDFS;

public:
  TGrafo(int n);
  void insereA(int v, int w);
  void show();
  void createFiles();
  void BFS(int s);
  void DFS(int v);
  ~TGrafo();
};

TGrafo::TGrafo(int n) {
  this->n = n;
  this->m = 0;
  TNo **list_adjac = new TNo *[n];
  for (int i = 0; i < n; i++)
    list_adjac[i] = nullptr;
  list_adj = list_adjac;
  adjBFS.resize(n);
}

TGrafo::~TGrafo() {
  for (int i = 0; i < n; i++) {
    TNo *no = list_adj[i];
    TNo *ant = nullptr;
    while (no) {
      ant = no;
      no = no->prox;
      delete ant;
    }
  }
  delete[] list_adj;
}

void TGrafo::insereA(int v, int w) {
  TNo *novoNo;
  TNo *no = list_adj[v];
  TNo *ant = nullptr;
  while (no && w >= no->w) {
    if (w == no->w)
      return;
    ant = no;
    no = no->prox;
  };
  novoNo = new TNo;
  novoNo->w = w;
  novoNo->prox = no;
  if (ant == nullptr) {
    list_adj[v] = novoNo;
  } else {
    ant->prox = novoNo;
  }
  adjBFS[v].push_back(w);
  adjDFS[v].push_back(w);
}

void TGrafo::show() {
  cout << "Numero de vertices: " << n << endl;
  cout << "Numero de arestas: " << m << endl;
  cout << "\nLista de Adjacencia:";
  for (int i = 0; i < n; i++) {
    cout << "\n" << i << ": ";
    // Percorre a lista na posição i do vetor
    TNo *no = list_adj[i];
    while (no) {
      cout << no->w << " ";
      no = no->prox;
    }
  }
  cout << endl << "\nFim da impressao da lista do grafo.\n" << endl;
}

void TGrafo::BFS(int s) {
  vector<bool> visited;
  visited.resize(n, false);
  list<int> queue;
  visited[s] = true;
  queue.push_back(s);
  while (!queue.empty()) {
    s = queue.front();
    cout << s << " ";
    queue.pop_front();
    for (auto adjecent : adjBFS[s]) {
      if (!visited[adjecent]) {
        visited[adjecent] = true;
        queue.push_back(adjecent);
      }
    }
  }
}

void TGrafo::DFS(int v) {
  visDFS[v] = true;
  cout << v << " ";
  list<int>::iterator i;
  for (i = adjDFS[v].begin(); i != adjDFS[v].end(); ++i) {
    if (!visDFS[*i]) {
      DFS(*i);
    }
  }
}

int main() {
  random_device a;
  mt19937 gerador(a());
  uniform_int_distribution<int> range(0, 99);
  TGrafo g(100);
  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < 3; j++) {
      int x = range(gerador);
      if (i != x)
        g.insereA(i, x);
    }
  }
  g.show();
  cout << "BFS: \n[ ";
  g.BFS(0);
  cout << "]" << endl;
  cout << "\nDFS:\n[ ";
  g.DFS(0);
  cout << "]" << endl;
}
