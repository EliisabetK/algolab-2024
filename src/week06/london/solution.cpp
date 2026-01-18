///5
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/push_relabel_max_flow.hpp>

using namespace std;

typedef boost::adjacency_list_traits<boost::vecS, boost::vecS, boost::directedS> traits;
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, boost::no_property,
    boost::property<boost::edge_capacity_t, long,
        boost::property<boost::edge_residual_capacity_t, long,
            boost::property<boost::edge_reverse_t, traits::edge_descriptor>>>> graph;

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

int main(){
  ios::sync_with_stdio(false); cin.tie(nullptr);
  int T; cin >> T;
  while(T--){
    int h,w; cin >> h >> w;
    string word; cin >> word;
    map<int,int> freq_word;
    for(char c : word){
      freq_word[c-'A']++;
    }
    int letters = freq_word.size();
    vector<vector<int>> input(2*h,vector<int>(w));
    for(int i = 0; i < 2*h; i++){
        for(int j = 0; j < w; j++){
          char c; cin >> c;
          input[i][j] = c -'A';
      }
    }
    map<pair<int,int>, int> tile_freq;
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
          int front = input[i][j];
          int back = input[i+h][w-j-1];
          tile_freq[{front,back}]++;
      }
    }
    int N = 26*26 + 2 + letters;
    graph G(N);
    edge_adder adder(G);
    const int v_source = 0;
    const int tiles_start = 1;
    const int letter_start = 26*26 + 1;
    const int v_sink = letter_start + letters;
    int i = 0;
    for(auto& tile : tile_freq) {
      int freq = tile.second;
      if(freq > 0) adder.add_edge(v_source, tiles_start + i, freq);
      i++;
    }
    i = 0;
    for(auto& tile : tile_freq) {
      int j = 0;
      for(auto& letter : freq_word) {
        int front = tile.first.first;
        int back = tile.first.second;
        int freq = tile.second;
        int l = letter.first;
        if(back != front && front == l) adder.add_edge(tiles_start + i, letter_start + j, freq);
        else{
          if(front == l) adder.add_edge(tiles_start + i, letter_start + j, freq);
          if(back == l) adder.add_edge(tiles_start + i, letter_start + j, freq);
        }
        j++;
      }
      i++;
    }
    i = 0;
    
    for(auto& letter : freq_word) {
      int count = letter.second;
      adder.add_edge(letter_start + i, v_sink, count);
      i++;
    }
    
    long flow = boost::push_relabel_max_flow(G, v_source, v_sink);
    if (flow == word.size()) cout << "Yes\n";
    else cout << "No" << endl;
  }
}