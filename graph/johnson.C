#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <set>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include <boost/heap/fibonacci_heap.hpp>

#define WEIGHT_MAX 100
#define DIST_INFINITY 100000000
#define NIL -1

class Graph
{

    struct Edge{
        int dest;
        int weight;
        int positive;
        Edge(int dest, int weight)
        {
            this->dest = dest;
            this->weight = weight;
        }
    };

    struct Verx{
        int id;
        int distance;
        int pre;
        Verx(int id = NIL, int distance = DIST_INFINITY, int pre = NIL)
        {
            this->id = id;
            this->distance = distance;
            this->pre = pre;
        }
    };
    struct VerxComp{
        bool operator() (const Verx& d1, const Verx& d2) const
        {
            return d1.distance > d2.distance;
        }
    };


    int n;
    std::vector<std::list<Edge> > adj;
    int ** dijkstraDist;
    int ** dijkstraPrev;
    int * bellmanFordDist;
    bool negative_cycle;

    public:
    Graph(int n);
    void AddEdge(int u, int v, int weight);
    void RandomInit(int edge_n);
    friend std::ostream& operator<< (std::ostream& os, const Graph& graph);

    void Dijkstra(int s);
    void BellmanFord();
    void Johnson();
};

Graph::Graph(int n)
{
    this->n=n;
    adj = std::vector<std::list<Edge> >(n);
    dijkstraDist = new int *[n];
    dijkstraPrev = new int *[n];
    negative_cycle = true;
}

void Graph::AddEdge(int u, int v, int weight)
{
    adj[u].push_back(Edge(v,weight));
    adj[v].push_back(Edge(u,weight));
}

void Graph::RandomInit(int edge_n)
{
    typedef std::pair<int,int> v;
    std::set<v> random_v;
    std::set<int> vertex;
    std::srand(std::time(0));
    while(vertex.size() != n)
    {
        int x,y;
        x = random()%n;
        y = random()%n;
        if(x < y && (vertex.size() == 0
                    || (vertex.count(x) + vertex.count(y)) == 1 ))
        {
            random_v.insert(v(x,y));
            vertex.insert(x);
            vertex.insert(y);
        }
    }
    while(random_v.size() != edge_n)
    {
        int x,y;
        x = random()%n;
        y = random()%n;
        if(x < y)
            random_v.insert(v(x,y));
    }
    #ifdef DEBUG
    for(std::set<v>::iterator it = random_v.begin(); it != random_v.end(); it++)
    {
        std::cout << it->first << it->second << " random (u,v)\n";
    }
    #endif
    for(std::set<v>::iterator it = random_v.begin(); it != random_v.end(); it++)
        AddEdge(it->first, it->second, random()%WEIGHT_MAX - 10);
}

std::ostream& operator<< (std::ostream& os, const Graph& graph)
{
    os << "Graph Adjacency Link:" << std::endl;
    for(int i = 0; i < graph.n; i++)
    {
        os << i << "->";
        for(std::list<Graph::Edge>::const_iterator it = graph.adj[i].begin(); it != graph.adj[i].end(); it++)
            os << it->dest << '(' << it->weight << ')' << ", ";
        os << std::endl;
    }
    if(graph.negative_cycle == false)
    {
        os << "Johnson Result:" << std::endl;
        for(int i = 0; i < graph.n; i++)
        {
            for(int j = 0; j < graph.n - i; j++)
                os << std::setw(4) << graph.dijkstraDist[i][j];
            os << std::endl;
        }
    }
    else
    {
        os << "Graph contains a negative-weight cycle" << std::endl;
    }

    return os;
}

void Graph::Dijkstra(int s)
{
    // check if the edge weight < 0;
    dijkstraDist[s] = new int [n];
    dijkstraPrev[s] = new int [n];
    boost::heap::fibonacci_heap<Verx, boost::heap::compare<VerxComp> >::handle_type * dijkstraHandle =
        new boost::heap::fibonacci_heap<Verx, boost::heap::compare<VerxComp> >::handle_type [n];
    boost::heap::fibonacci_heap<Verx, boost::heap::compare<VerxComp> > Q;
    for(int i = 0; i < n; i++)
    {
        if(i == s)
        {
            dijkstraHandle[i] = Q.push(Verx(i,0));
            dijkstraDist[s][i] = 0;
            dijkstraPrev[s][i] = NIL;
        }
        else
        {
            dijkstraHandle[i] = Q.push(Verx(i));
            dijkstraDist[s][i] = DIST_INFINITY;
            dijkstraPrev[s][i] = NIL;
        }
    }
    while(Q.size() != 0)
    {
        Verx v = Q.top();
        Q.pop();
        for(std::list<Edge>::iterator it = adj[v.id].begin(); it != adj[v.id].end(); it++)
        {
            //v is v.id, u is it->dest
            // v->u
            int alt = dijkstraDist[s][v.id] + it->weight;
            if(alt < dijkstraDist[s][it->dest])
            {
                dijkstraDist[s][it->dest] = alt;
                dijkstraPrev[s][it->dest] = v.id;
                Q.update(dijkstraHandle[it->dest], Verx(it->dest,alt));
            }
        }
    }
    #ifdef DEBUG
    for(int i = 0; i < n; i++)
    {
        if(i == s) continue;
        int t1 = dijkstraDist[s][i];
        int t2 = dijkstraPrev[s][i];
        std::cout << i << " " << t1 << std::endl;
    }
    #endif
}

void Graph::BellmanFord()
{
    int source = n; // n+1 nodes now
    adj.push_back(std::list<Edge>());
    bellmanFordDist = new int [n+1];
    for(int i = 0; i < n; i++)
        AddEdge(source, i, 0);
    for(int i = 0; i <= n; i++)
        if(i == source)
            bellmanFordDist[i] = 0;
        else
            bellmanFordDist[i] = DIST_INFINITY;
    for(int i = 0; i < n; i++)
    {
        // v->u
        // u is it->dest
        for(int v = 0; v <= n; v++)
            for(std::list<Edge>::iterator it = adj[v].begin(); it != adj[v].end(); it++)
            {
                int alt = bellmanFordDist[v] + it->weight;
                if(alt < bellmanFordDist[it->dest])
                    bellmanFordDist[it->dest] = alt;
            }
    }
    #ifdef DEBUG
    for(int i = 0; i <=n; i++)
        std::cout << bellmanFordDist[i] << ", ";
    std::cout << std::endl;
    #endif
    negative_cycle = false;
    // v->u
    // u is it->dest
    for(int v = 0; v <= n && negative_cycle == false; v++)
        for(std::list<Edge>::iterator it = adj[v].begin();
                it != adj[v].end() && negative_cycle == false; it++)
            if(bellmanFordDist[v] + it->weight < bellmanFordDist[it->dest])
                negative_cycle = true;
    adj.pop_back();
}

void Graph::Johnson()
{
    BellmanFord();
    if(negative_cycle == false)
    {
        // because it is undirected graph,
        // so no negative cycle means no negative edge
        for(int i = 0; i < n; i++)
            Dijkstra(i);
    }
}

int main(int argc, char const* argv[])
{
    /*
    if(argc != 2)
    {
        std::cout << "./scc n" << std::endl;
        return 1;
    }
    int n = atoi(argv[1]);
    Graph graph(n);
    graph.RandomInit((int)(n * log2(n)));
    */
    Graph graph(4);

    for(int i =0; i < 4; i++)
    {
        int x,y,w;
        std::cin >> x >> y >> w;
        graph.AddEdge(x,y,w);
    }

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    graph.Johnson();

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::nanoseconds elapsed = std::chrono::duration_cast<std::chrono::nanoseconds> (end - start);

    std::cout<<graph;
    std::cout << "Johnson function elapsed " << elapsed.count() << " nanoseconds" << std::endl;

    return 0;
}
