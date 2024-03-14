#include <iostream>
#include <memory.h>
#include <fstream>
#include <string>
using namespace std;

const int max_vertex = 7; // Maximum number of vertices
int number_vertex; // The number of vertices in the graph
const int inf = 1000;
int stream_matrix[max_vertex][max_vertex];
int capacity_matrix[max_vertex][max_vertex];
int temp[max_vertex];
int link[max_vertex];
int queue[max_vertex]; //Putting everything in the queue
int  begin_queue, number_elem;
int find_path(int start_vertex, int end_vertex) 
{
    begin_queue = 0; number_elem = 1; queue[0] = start_vertex;
    link[end_vertex] = -1; 
    int vertex_begin;
    memset(temp, 0, sizeof(int) * number_vertex); // At the beginning, 0 flows from all vertices except the source
    temp[start_vertex] = inf; // And as much as you want can flow out of the source
    while (link[end_vertex] == -1 && begin_queue < number_elem)
    {
        vertex_begin = queue[begin_queue];
        for (int i = 0; i < number_vertex; i++)
            if ((capacity_matrix[vertex_begin][i] - stream_matrix[vertex_begin][i]) > 0 && temp[i] == 0)
            {
                queue[number_elem] = i; 
                number_elem++;
                link[i] = vertex_begin; 
                if (capacity_matrix[vertex_begin][i] - stream_matrix[vertex_begin][i] < temp[vertex_begin])
                    temp[i] = capacity_matrix[vertex_begin][i];
                else
                    temp[i] = temp[vertex_begin];
            }
        begin_queue++;
    }
    if (link[end_vertex] == -1) return 0; 
    vertex_begin = end_vertex;
    while (vertex_begin != start_vertex)
    {
        stream_matrix[link[vertex_begin]][vertex_begin] += temp[end_vertex];
        vertex_begin = link[vertex_begin];
    }
    return temp[end_vertex];
}
// The main function of maximum flow search
int max_stream(int start_vertex, int end_vertex) 
{
    memset(stream_matrix, 0, sizeof(int) * max_vertex * max_vertex); // Nothing flows through the graph
    int max_s = 0; 
    int add_fw;
    do
    {
        add_fw = find_path(start_vertex, end_vertex);
        max_s += add_fw;
    } while (add_fw > 0);
    return max_s;
}

int main()
{
    int start_vertex, end_vertex; // Determining the source and drain
    string survey;
    bool is_continue = true;
    ifstream fin;
    while (is_continue)
    {
        cout << "Choose a solution option:" << endl;
        cout << "1 - Enter the matrix yourself " << endl;
        cout << "2 - Read the matrix from the file " << endl;
        cout << "1/2:  ";
        cin >> survey;
        if (survey.length() > 1)
        {
            cout << "Error" << endl;
            continue;
        }
        switch (survey[0])
        {
        case '1':
            cout << endl << "Enter the number of vertices(2-7): ";
            cin >> number_vertex;
            cout << "The initial vertex : ";
            cin >> start_vertex;
            cout << "The final vertex: ";
            cin >> end_vertex;
            cout << "Enter an array of arc loads:" << endl;
            for (int i = 0; i < number_vertex; i++)
                for (int j = 0; j < number_vertex; j++)
                    cin >> capacity_matrix[i][j];
            cout << "Maximum flow = " << max_stream(start_vertex, end_vertex) << endl;
            is_continue = false;
            break;
        case '2':
            fin.open("input");
            fin >> number_vertex;
            fin >> start_vertex;
            fin >> end_vertex;
            for (int i = 0; i < number_vertex; i++)
                for (int j = 0; j < number_vertex; j++)
                    fin >> capacity_matrix[i][j];
            cout << "Maximum flow = " << max_stream(start_vertex, end_vertex) << endl;
            fin.close();
            is_continue = false;
            break;
        default:
            cout << "Error" << endl;
            break;
        }
    }

    system("pause");
}