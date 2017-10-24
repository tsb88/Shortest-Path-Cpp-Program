//
// The range of vertices was scaled down for this algorith to 64 to 512 because the efficiency of this
// algorith is O(V*E) which makes it very slow for large amounts of vertices
//

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>
#include <limits.h>
using namespace std;

double totalDistance = 0;
double averageDistance;

typedef struct {
    
    int u, v, w;
} Edge;

#define INFINITY INT_MAX

void BellmanFord(int source, int size, int edgeCount, vector<Edge> edgesArray, int distanceArray[])
{
    for (int i = 0; i < size; ++i)
    {
        distanceArray[i] = INFINITY;
    }
    
    distanceArray[source] = 0;
    
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < edgeCount; ++j)
        {
            if (distanceArray[edgesArray[j].u] + edgesArray[j].w < distanceArray[edgesArray[j].v])
            {
                distanceArray[edgesArray[j].v] = distanceArray[edgesArray[j].u] + edgesArray[j].w;
            }
        }
    }
    
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < edgeCount; ++j)
        {
            if (distanceArray[edgesArray[j].u] + edgesArray[j].w < distanceArray[edgesArray[j].v])
            {
                cout << "Graph contains a negative-weight cycle" << endl;
                exit(1);
            }
        }
    }
}

int main()
{
    for (int i = 0; i < 100; i++)
    {
        totalDistance = 0;
    
        unsigned long start_s=clock();
    
        srand(static_cast<unsigned int>(time(0)));
    
        for (int x = 0; x < 100; x++)
        {
            int size = rand() % 512 + 64;
    
            vector<vector<int>> graph((size), vector<int> (size));
    
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    graph[i][j] = rand() % 5 + 1;
                }
            }
    
            int k = 0; int m = 0;
    
            while ((k < size) && (m < size))
            {
                graph[k][m] = 0;
                k++;
                m++;
            }
    
            int edgeCount = size*size;
    
            vector<Edge> edgesArray(edgeCount);
            int distanceArray[size];

            k = 0;
    
            for (int i = 0; i < size; ++i)
            {
                for (int j = 0; j < size; ++j)
                {
                edgesArray[k].u = i;
                edgesArray[k].v = j;
                edgesArray[k].w = graph[i][j];
                k++;
                }
            }
    
            BellmanFord(0, size, edgeCount, edgesArray, distanceArray);
        
            int randomVertex = rand() % size + 1;
        
            cout << "Source Vertex: " << 0 << endl;
            cout << "Destination Vertex (Random): " << randomVertex << endl;
            cout << "Distance: " << distanceArray[randomVertex] << endl;
            totalDistance = totalDistance + distanceArray[randomVertex];
        
        }
    
        cout << endl;
        cout << "Average Distance: " << totalDistance/100 << endl;
    
        unsigned long stop_s=clock();
    
        cout << "Time: " << ((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000)/1000 << " seconds" << endl;
    }
    
    return 0;
}
