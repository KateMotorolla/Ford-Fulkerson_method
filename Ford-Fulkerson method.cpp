#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

void print_matrix(const vector<vector<int>>& matrix)
{
	int n = matrix.size();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
			cout << matrix[i][j] << "\t";
		cout << endl;
	}
}
bool only_source_path_count(vector<vector<int>>& source_matrix, vector<vector<int>>& reverse_matrix, set<int>& used,
	int index, int end_vertex, int& min)
{
	int n = source_matrix.size(); 
	used.insert(index); 
	if (index == end_vertex) 
		return true;  
	for (int j = 0; j < n; ++j) 
	{
		if (source_matrix[index][j] != 0 && used.find(j) == used.end()) 
		{
			if (source_matrix[index][j] < min)
				min = source_matrix[index][j];
			if (only_source_path_count(source_matrix, reverse_matrix, used, j, end_vertex, min))
			{
				source_matrix[index][j] -= min; 
				reverse_matrix[j][index] += min; 
				return true;
			}
		}
	}
	return false;
}

int only_source_max_stream_count(vector<vector<int>>& source_matrix, vector<vector<int>>& reverse_matrix, int begin_vertex, int end_vertex) 
{
	set<int> used;
	int min = 999, sum = 0;
	while (only_source_path_count(source_matrix, reverse_matrix, used, begin_vertex, end_vertex, min))
	{
		used.clear();
		cout << "Some iteration source matrix(Min: " << min << "): " << endl;
		print_matrix(source_matrix);
		cout << "Some iteration reverse matrix(Min: " << min << "): " << endl;
		print_matrix(reverse_matrix);
		sum += min;
		min = 999;
	}
	return sum;
}

int main()
{
	cout << "Pick pls:" << endl;
	cout << "1 - Load data from file" << endl;
	cout << "2 - Console input" << endl;
	string pick;
	cin >> pick;
	int vertex_count, begin_vertex, end_vertex;
	vector<vector<int>> source_matrix;
	vector<vector<int>> reverse_matrix;
	if (pick[0] == '1')
	{
		ifstream fin("input.txt");
		fin >> vertex_count >> begin_vertex >> end_vertex;
		source_matrix = vector<vector<int>>(vertex_count, vector<int>(vertex_count));
		reverse_matrix = vector<vector<int>>(vertex_count, vector<int>(vertex_count));
		for (int i = 0; i < vertex_count; ++i)
		{
			for (int j = 0; j < vertex_count; ++j)
				fin >> source_matrix[i][j];
		}
		fin.close();
		cout << "Vertex count: " << vertex_count << endl;
		cout << "Begin vertex number: " << begin_vertex << endl;
		cout << "End vertex number: " << end_vertex << endl;
		cout << "Source matrix: " << endl;
		print_matrix(source_matrix);
	}
	else
	{
		cout << "Input vertex count: ";
		cin >> vertex_count;
		cout << "Input begin vertex number: ";
		cin >> begin_vertex;
		cout << "Input end vertex number: ";
		cin	>> end_vertex;
		cout << "Input source matrix: ";
		source_matrix = vector<vector<int>>(vertex_count, vector<int>(vertex_count));
		reverse_matrix = vector<vector<int>>(vertex_count, vector<int>(vertex_count));
		for (int i = 0; i < vertex_count; ++i)
		{
			for (int j = 0; j < vertex_count; ++j)
				cin >> source_matrix[i][j];
		}
	}
	int sum = only_source_max_stream_count(source_matrix, reverse_matrix, begin_vertex, end_vertex);
	cout << "Sum: " << sum << endl;
	for (int i = 0; i < vertex_count; ++i)
	{
		for (int j = 0; j < vertex_count; ++j)
		{
			if (reverse_matrix[i][j] != 0)
				source_matrix[i][j] = reverse_matrix[i][j];
		}
	}
	sum += only_source_max_stream_count(source_matrix, reverse_matrix, begin_vertex, end_vertex);
	cout << "Sum: " << sum << endl;
	return 0;
}