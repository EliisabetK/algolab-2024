#### Topic
Max flow

#### Explanation
There exist n intersections, some have photographs and stations. After picking up the photograph you can bring it to any station to store it, each station can store 1. You can only use a street once after picking up a photograph.

Solution:
1. Use a frequency map to store station and photograph locations and keep the count of how many per intersection. Or you can use a vector of pairs, index i shows intersection i, where first is number of stations and second is number of photos.
2. Build a graph with 2+2n nodes, where there is an edge with capacity of number of stations in that intersection from the source to each intersection where there is a station. Then add another column of intersections, where there is an edge between intersection i and i+n with capacity(num photographs) if the intersection has a photograph. Then from each intersection i+n with a station add an edge to the sink with capacity equal to the number of stations.
3. Read in the streets m, and connect the left column of intersections with capacity INF and the right column with capacity 1 to show that you can't use streets more than once afer picking up a photo.
4. Answer is equal to max flow.