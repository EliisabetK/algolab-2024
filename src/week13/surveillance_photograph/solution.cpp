///1
#include <iostream>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>
#include <unordered_map>
#include <vector>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

typedef traits::vertex_descriptor vertex_desc;
typedef traits::edge_descriptor edge_desc;
const int INF = 1000000000;
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
    c_map[rev_e] = 0;
    r_map[e] = rev_e;
    r_map[rev_e] = e;
  }
};

int main() {
  int T;
  cin >> T;
  while(T--){
    int n,m,k,l;
    cin >> n >> m >> k >> l;
    
    map<int,int> stations;
    for(int i = 0; i < k; i++){
      int s; cin >> s;
      stations[s]++;
    }
    
    map<int,int> photographs;
    for(int i = 0; i < l; i++){
      int p; cin >> p;
      photographs[p]++;
    }
    
    int N = 2 + 2*n;
    graph G(N);
    edge_adder adder(G);
    const int v_source = 0;
    const int v_sink = N-1;
    
    for(auto& s : stations){
      adder.add_edge(v_source, 1+s.first, s.second);
      adder.add_edge(1+s.first+n, v_sink, s.second);
    }
    
    for(int i = 0; i < m; i++){
      int x,y;
      cin >> x >> y;
      adder.add_edge(1+x, 1+y, INF);
      adder.add_edge(1+x+n, 1+y+n, 1);
    }
    
    for(auto& p : photographs){
      adder.add_edge(1+p.first, 1+p.first+n, p.second);
    }
    
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    cout << flow << "\n";
  }
  return 0;
}
