#include <iostream>

using std::cin;
using std::cout;
using std::endl;

const int BORD = 10000;
int matrix[BORD][BORD] = { 0 };
int max_matrix[BORD][BORD] = { 0 };

void fill_random(int, int);
void print_result(int, int);

int main()
{
	cout << "Write row lenght:" << endl;
	int row_len; cin >> row_len;

	cout << "Write column lenght:" << endl;
	int column_len; cin >> column_len;

	//при заполнении 10000 на 10000 закаментируйте иначе работать не будет ибо заполнение сложностью o(n^2)
	fill_random(row_len, column_len);

	int column_count = column_len - 1;
	int row_count = 0;

	max_matrix[column_count][row_count] = matrix[column_len - 1][0];

	//поиск максимумов последней строки
	for (int i = 1; i < row_len; ++i)
	{
		if (matrix[column_len - 1][i] > max_matrix[column_count][row_count])
		{
			++row_count;
			max_matrix[column_count][row_count] = matrix[column_len - 1][i];
		}
		else
		{
			++row_count;
			max_matrix[column_count][row_count] = max_matrix[column_count][row_count - 1];
		}
	}

	row_count = 0;
	column_count = column_len - 1;

	//поиск максимумов первого столбца
	for (int i = column_len - 2; i >= 0; --i)
	{
		if (matrix[i][0] > max_matrix[column_count][row_count])
		{
			--column_count;
			max_matrix[column_count][row_count] = matrix[i][0];
		}
		else
		{
			--column_count;
			max_matrix[column_count][row_count] = max_matrix[column_count + 1][row_count];
		}
	}

	//поиск остальных максимумов 
	for (int i = column_len - 2; i >= 0; --i)
	{
		for (int j = 1; j < row_len; ++j)
		{
			if (matrix[i][j] > max_matrix[i + 1][j] && matrix[i][j] > max_matrix[i][j - 1])
			{
				max_matrix[i][j] = matrix[i][j];
				continue;
			}

			if (max_matrix[i + 1][j] > max_matrix[i][j - 1])
			{
				max_matrix[i][j] = max_matrix[i + 1][j];
			}
			else
			{
				max_matrix[i][j] = max_matrix[i][j - 1];
			}
		}
	}

	print_result(row_len, column_len);
}

//Функция заполнения матрицы случайными числами 
void fill_random(int row_len, int column_len)
{
	const int RIGHT_BORD = 100;
	const int LEFT_BORD = -100;

	for (int i = 0; i < column_len; ++i)
	{
		for (int n = 0; n < row_len; ++n)
		{
			matrix[i][n] = rand() % (RIGHT_BORD - LEFT_BORD + 1) + LEFT_BORD;
		}
	}
}

//Функция вывода матриц
void print_result(int row_len, int column_len)
{
	cout << "Start matrix:" << endl;

	for (int i = 0; i < column_len; ++i)
	{
		for (int n = 0; n < row_len; ++n)
		{
			cout << matrix[i][n] << '\t';
		}
		cout << endl;
	}

	cout << endl << "Max of start matrix" << endl;

	for (int i = 0; i < column_len; ++i)
	{
		for (int n = 0; n < row_len; ++n)
		{
			cout << max_matrix[i][n] << '\t';
		}
		cout << endl;
	}
}