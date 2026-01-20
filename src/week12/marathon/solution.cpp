///1

#include <iostream>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
using namespace std;


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS,
  boost::no_property, 
  boost::property<boost::edge_weight_t, int,
  boost::property<boost::edge_capacity_t, int> // add this
  > 
> weighted_graph;

typedef boost::property_map<weighted_graph, boost::edge_weight_t>::type weight_map;
typedef boost::property_map<weighted_graph, boost::edge_capacity_t>::type width_map; // add this
typedef boost::graph_traits<weighted_graph>::edge_descriptor            edge_desc;
typedef boost::graph_traits<weighted_graph>::vertex_descriptor          vertex_desc;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

static vector<int> dijkstra_dist(const weighted_graph &G, int s) {
  int n = boost::num_vertices(G);
  std::vector<int> dist_map(n);

  boost::dijkstra_shortest_paths(G, s,
    boost::distance_map(boost::make_iterator_property_map(
      dist_map.begin(), boost::get(boost::vertex_index, G))));

  return dist_map;
}

class edge_adder {
  graph &G;

 public:
  explicit edge_adder(graph &G) : G(G) {}

  void add_edge(int from, int to, long capacity) {
    auto c_map = boost::get(boost::edge_capacity, G);
    auto r_map = boost::get(boost::edge_reverse, G);
    const auto e = boost::add_edge(from, to, G).first;
    const auto rev_e = boost::add_edge(to, from, G).first;
    c_map[e] = capacity;
    c_map[rev_e] = 0; // reverse edge has no capacity!
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int main(){
  int T;
  cin >> T;
  while(T--){
    int n,m,s,f;
    cin >> n >> m >> s >> f;
    weighted_graph G(n);
    weight_map weights = boost::get(boost::edge_weight, G);
    width_map widths = boost::get(boost::edge_capacity, G);

    for(int i = 0; i < m; i++){
      int a,b,c,d; cin >> a >> b >> c >> d;
      edge_desc e1 = boost::add_edge(a, b, G).first; weights[e1]=d; widths[e1] = c; // two way streets
      edge_desc e2 = boost::add_edge(b, a, G).first; weights[e2]=d; widths[e2] = c;
    }
    
    vector<int> dist_from_s = dijkstra_dist(G, s);
    vector<int> dist_from_f = dijkstra_dist(G, f);
    int min_dist = min(dist_from_s[f], dist_from_f[s]);
    
    graph G2(n);
    edge_adder adder(G2);  
    auto edge_iters = boost::edges(G);
    for (auto edge_it = edge_iters.first; edge_it != edge_iters.second; ++edge_it) {
      int u =  boost::source(*edge_it, G);
      int v =  boost::target(*edge_it, G);
      if(dist_from_s[u] + weights[*edge_it] + dist_from_f[v] == min_dist){
        adder.add_edge(u,v, widths[*edge_it]);
      }
    }
    long flow = boost::push_relabel_max_flow(G2, s, f);
    cout << flow << "\n";
  }
}