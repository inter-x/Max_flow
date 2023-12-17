#include <stdio.h> 
#include <limits.h> 
#include <string.h> 
#include <stdbool.h> 
#include <stdlib.h>

// Number of vertices in given graph 
#define V 20 

/* Returns true if there is a path from source 's' to sink 't' in 
residual graph. Also fills parent[] to store the path */
bool bfs(int rGraph[V][V], int s, int t, int parent[]) 
{ 
    // Create a visited array and mark all vertices as not visited 
    bool visited[V]; 
    memset(visited, 0, sizeof(visited)); 

    // Create a queue, enqueue source vertex and mark source vertex 
    // as visited 
    int q[V];
    int front = 0, rear = 0;
    q[rear++] = s; 
    visited[s] = true; 
    parent[s] = -1; 

    // Standard BFS Loop 
    while (front != rear) 
    { 
        int u = q[front++]; 
		int v;
        for (v=0; v<V; v++) 
        { 
            if (!visited[v] && rGraph[u][v] > 0) 
            { 
                q[rear++] = v; 
                parent[v] = u; 
                visited[v] = true; 
            } 
        } 
    } 

    // If we reached sink in BFS starting from source, then return 
    // true, else false 
    return visited[t]; 
} 

// Returns the maximum flow from s to t in the given graph 
int fordFulkerson(int graph[V][V], int s, int t) 
{ 
    int u, v; 

    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates 
                    // residual capacity of edge from i to j (if there 
                    // is an edge. If rGraph[i][j] is 0, then there is not) 
    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
            rGraph[u][v] = graph[u][v]; 

    int parent[V]; // This array is filled by BFS and to store path 

    int max_flow = 0; // There is no flow initially 

    // Augment the flow while there is a path from source to sink 
    while (bfs(rGraph, s, t, parent)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        int path_flow = INT_MAX; 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = path_flow < rGraph[u][v] ? path_flow : rGraph[u][v]; 
        } 

        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 

        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 

    // Return the overall flow 
    return max_flow; 
} 

// Driver program to test above functions 
int main() 
{ 
    // Let us create a graph shown in the above example 
    int graph[V][V] = { {0, 8, 12, 0, 0, 0}, 
                        {0, 0, 0, 6, 10, 0}, 
                        {0, 2, 0, 10, 0, 0}, 
                        {0, 0, 0, 0, 0, 8}, 
                        {0, 0, 0, 2, 0, 10}, 
                        {0, 0, 0, 0, 0, 0} 
                    }; 

    printf("The maximum possible flow is %d\n", fordFulkerson(graph, 0, 5)); 

    return 0; 
} 

