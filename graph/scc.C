#include <iostream>
#include <stack>
#include <list>
#include <set>
#include <cstdlib>
#include <ctime>

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
    std::list<v> vertex;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(i != j)
                vertex.push_back(v(i,j));
    std::set<v> random_v;
    std::srand(std::time(0));
    while(random_v.size() != edge_n)
        random_v.insert(v(random()%n, random()%n));
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
    os << "Graph Adjacency Link:" << std::endl;
    for(int i = 0; i < graph.n; i++)
    {
        os << i << "->";
        for(std::list<int>::iterator it = graph.adj[i].begin(); it != graph.adj[i].end(); it++)
            os << (*it) << ", ";
        os << std::endl;
    }

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
    Graph graph(10);
    graph.RandomInit(10);
    /*
    graph.AddEdge(0,3);
    graph.AddEdge(0,6);
    graph.AddEdge(1,7);
    graph.AddEdge(1,8);
    graph.AddEdge(2,1);
    graph.AddEdge(4,7);
    graph.AddEdge(6,0);
    graph.AddEdge(7,0);
    graph.AddEdge(8,7);
    graph.AddEdge(8,9);
    */
    graph.SCC();
    std::cout<<graph;
    return 0;
}
