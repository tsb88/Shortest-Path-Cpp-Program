#include<iostream>
#include<stdio.h>
#include<limits.h>
#include<iomanip>
#include<time.h>
#include<vector>
#include<ctime>
using namespace std;

double totalDistance = 0;
double averageDistance;

int minDistance(int array[], bool vertexSet[], int size)
{
    int min; int minIndex = 0;
    min = 1000;
    
    for (int i = 0; i < size; i++)
    {
        if (vertexSet[i] == false && array[i] <= min)
        {
            min = array[i];
            minIndex = i;
        }
    }
    
    return minIndex;
}

void shortestPath(vector<vector<int>> const& graphMatrix, int size, int weightArray[])
{
    
    int n = size; int minIndex = 0;
    bool vertexSet[n];
    
    for (int i = 0; i < n; i++)
    {
        weightArray[i] = graphMatrix[0][i];
    }
    
    
    for (int j = 0; j < n; j++)
    {
        vertexSet[j] = false;
    }
    
    weightArray[0] = 0;
    
    for (int k = 0; k < n; k++)
    {
        
        minIndex = minDistance(weightArray, vertexSet, size);
        
        vertexSet[minIndex] = true;
        
        for (int v = 0; v < n; v++)
        {
            if ((!vertexSet[v]) && (graphMatrix[minIndex][v] && weightArray[minIndex] != 1000)
                && (weightArray[minIndex] + graphMatrix[minIndex][v] < weightArray[v]))
            {
                weightArray[v] = weightArray[minIndex] + graphMatrix[minIndex][v];
            }
        }
        
    }
    
    int randomVertex = rand() % size + 1;
    cout << "Source Vertex: " << 0 << endl;
    cout << "Destination Vertex (Random): " << randomVertex << endl;
    cout << "Distance: " << weightArray[randomVertex] << endl;
    cout << endl;
    
    totalDistance = totalDistance + weightArray[randomVertex];
}

int main()
{
    for (int i = 0; i < 86; i++)
    {
       totalDistance = 0;
        
        
        unsigned long start_s=clock();
    
        int size;
    
        srand(static_cast<unsigned int>(time(0)));

        for (int i = 0; i < 100; i++)
        {
        
            size = rand() % 8192 + 64;
    
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
    
            int weight[size];
    
            shortestPath(graph, size, weight);
        }
    
        cout << "Average distance: " << totalDistance/100 << endl;
    
        unsigned long stop_s=clock();
    
        cout << "Time: " << ((stop_s-start_s)/double(CLOCKS_PER_SEC)*1000)/1000 << " seconds" << endl;
    }
    
    return 0;
}
