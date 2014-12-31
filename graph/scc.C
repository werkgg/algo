#include <iostream>
#include <stack>
#include <list>
#include <set>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cmath>

class Graph
{
    int n;
    std::list<int> *adj;
    std::list< std::list<int> > scc;

    void Tarjan(int u, int * discovery, int * low,
            std::stack<int> * st, bool * stackMember, int * time);

    public:
    Graph(int n);
    void AddEdge(int u, int v);
    void RandomInit(int edge_n);
    void SCC();
    friend std::ostream& operator<< (std::ostream& os, const Graph& graph);
};

Graph::Graph(int n)
{
    this->n=n;
    adj = new std::list<int>[n];
}

void Graph::AddEdge(int u, int v)
{
    adj[u].push_back(v);
}

void Graph::RandomInit(int edge_n)
{
    typedef std::pair<int,int> v;
    std::set<v> random_v;
    std::srand(std::time(0));
    while(random_v.size() != edge_n)
    {
        int x,y;
        x = random()%n;
        y = random()%n;
        if(x != y)
            random_v.insert(v(x,y));

    }
    for(std::set<v>::iterator it = random_v.begin(); it != random_v.end(); it++)
        AddEdge(it->first, it->second);
}

void Graph::Tarjan(int u, int * discovery, int * low,
        std::stack<int> * st, bool * stackMember, int * time)
{
    discovery[u] = low[u] = ++(*time);
    st->push(u);
    stackMember[u] = true;

    for(std::list<int>::iterator it = adj[u].begin(); it != adj[u].end(); it++)
    {
        int v = *it;
        if(discovery[v] == -1)
        {
            Tarjan(v, discovery, low, st, stackMember, time);
            low[u] = std::min(low[u], low[v]);
        }
        else if(stackMember[v] == true)
            low[u] = std::min(low[u], discovery[v]);
    }
    std::list<int> components;
    if(low[u] == discovery[u])
    {
        int w;
        do
        {
            w = st->top();
            components.push_back(w);
            stackMember[w] = false;
            st->pop();
        }
        while(w != u);
    }
    scc.push_back(components);
}

void Graph::SCC()
{
    int * discovery = new int[n];
    int * low  = new int[n];
    bool * stackMember = new bool[n];
    int * time = new int(0);
    std::stack<int> * st = new std::stack<int>;

    for(int i = 0; i < n; i++)
    {
        discovery[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }
    for(int i = 0; i < n; i++)
        if(discovery[i] == -1)
            Tarjan(i, discovery, low, st, stackMember, time);
}

std::ostream& operator<< (std::ostream& os, const Graph& graph)
{
    /*
    os << "Graph Adjacency Link:" << std::endl;
    for(int i = 0; i < graph.n; i++)
    {
        os << i << "->";
        for(std::list<int>::iterator it = graph.adj[i].begin(); it != graph.adj[i].end(); it++)
            os << (*it) << ", ";
        os << std::endl;
    }
    */
    os << "Strongly Connected Component:" << std::endl;

    for(std::list< std::list<int> >::const_iterator it = graph.scc.begin();
            it != graph.scc.end(); it++)
    {
        for(std::list<int>::const_iterator v = it->begin(); v != it->end(); v++)
            os << (*v) << ", ";
        if(it->size() > 0)os << std::endl;
    }

    return os;
}

int main(int argc, char const* argv[])
{
    if(argc != 2)
    {
        std::cout << "./scc n" << std::endl;
        return 1;
    }
    int n = atoi(argv[1]);
    Graph graph(n);
    graph.RandomInit((int)(n * log2(n)));
    /*
    Graph graph(8);
    graph.AddEdge(0,1);
    graph.AddEdge(1,2);
    graph.AddEdge(1,4);
    graph.AddEdge(1,5);
    graph.AddEdge(2,3);
    graph.AddEdge(2,6);
    graph.AddEdge(3,2);
    graph.AddEdge(3,7);
    graph.AddEdge(4,0);
    graph.AddEdge(4,5);
    graph.AddEdge(5,6);
    graph.AddEdge(6,5);
    graph.AddEdge(6,7);
    graph.AddEdge(7,7);
    */
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    graph.SCC();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start);
    std::cout<<graph;
    std::cout << "SCC function elapsed " << elapsed.count() << " nanoseconds" << std::endl;
    return 0;
}
