#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cmath> 

using namespace std;

typedef CGAL::Exact_predicates_exact_constructions_kernel K;

typedef CGAL::Triangulation_vertex_base_2<K> Vb;
typedef CGAL::Triangulation_face_base_with_info_2<K::FT, K> Fb;
typedef CGAL::Triangulation_data_structure_2<Vb, Fb> Tds;
typedef CGAL::Delaunay_triangulation_2<K, Tds> Triangulation;
typedef K::Point_2 P;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        long long n, m, r;
        cin >> n >> m >> r;
        vector<P> trees;
        trees.reserve(n);
        for (int i = 0; i < n; i++) {
            long long x, y;
            cin >> x >> y;
            trees.emplace_back(P((double)x, (double)y));
        }

        Triangulation t;
        t.insert(trees.begin(), trees.end());

        priority_queue<pair<K::FT, Triangulation::Face_handle>> pq;
        K::FT huge_val = K::FT(pow(2.0, 102)); 

        // initialize all faces
        for (auto f = t.all_faces_begin(); f != t.all_faces_end(); ++f) {
            if (t.is_infinite(f)) {
                f->info() = huge_val;
            } else {
                P p1 = f->vertex(0)->point();
                P p2 = f->vertex(1)->point();
                P p3 = f->vertex(2)->point();
                P center = CGAL::circumcenter(p1, p2, p3);
                f->info() = CGAL::squared_distance(center, p1);
            }
            pq.push({f->info(), f});
        }

        // widest path
        while (!pq.empty()) {
            K::FT width = pq.top().first;
            auto u = pq.top().second;
            pq.pop();
            
            if (width < u->info()) continue;

            for (int i = 0; i < 3; i++) {
                auto v = u->neighbor(i);
                
                K::FT gate_width;
                auto v1 = u->vertex(Triangulation::cw(i));
                auto v2 = u->vertex(Triangulation::ccw(i));

                if (t.is_infinite(v1) || t.is_infinite(v2)) {
                    gate_width = huge_val; 
                } else {
                    gate_width = CGAL::squared_distance(v1->point(), v2->point());
                }

                K::FT new_path_width = min(width, gate_width);

                if (new_path_width > v->info()) {
                    v->info() = new_path_width;
                    pq.push({new_path_width, v});
                }
            }
        }

        // balloons
        for (int i = 0; i < m; i++) {
            long long x, y, s;
            cin >> x >> y >> s;
            
            P b((double)x, (double)y);
            
            double combined_rad = (double)r + (double)s;
            K::FT min_dist_sq = K::FT(combined_rad) * K::FT(combined_rad); // (r+s)^2
            
            // required clearance is distance 2(r+s) => squared 4(r+s)^2
            K::FT req_w = K::FT(4.0) * min_dist_sq; 

            // immediate collision
            P nearest = t.nearest_vertex(b)->point();
            if (CGAL::squared_distance(b, nearest) < min_dist_sq) {
                cout << "n";
                continue;
            }
            //check takeoff
            auto start_face = t.locate(b);
            if (start_face->info() >= req_w) {
                cout << "y";
            } else {
                cout << "n";
            }
        }
        cout << "\n";
    }
    return 0;
}