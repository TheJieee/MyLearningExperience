#include<iostream>
#include<array>
#include<random>
#include "mySTL.h"
#include<algorithm>

std::random_device sd;
std::default_random_engine engine(sd());

int** create_matrix(int degree)
{
	int* ma = new int[degree * degree];
	int** ret = new int*[degree];
	for (int i = 0; i < degree * degree; i++)
		ma[i] = 0;
	for (int i = 0; i < degree; i++) {
		ret[i] = ma;
		ma += degree;
	}
	return ret;
}

void del_matrix(int** matrix)
{
	delete[] matrix[0];
	delete[] matrix;
}

class sprarse_matrix {
public:
	sprarse_matrix(int degree)
		:m_degree(degree)
	{
		my::Timer timer("constructor");
		std::uniform_int_distribution<int> generator(1, m_degree);
		for (int i = 0; i < 10; i++) {
			vector3& vctr = m_value[i];
			vctr.x = generator(engine);
			vctr.value = generator(engine);
		}
		std::sort(m_value.begin(), m_value.end(), [](const vector3& v1, const vector3& v2) {
			return v1.x < v2.x ? true : false;
			});
		std::vector<int> vct;
		vct.push_back(0);
		for (vector3& vctr : m_value) {
			if (vctr.x != vct[0]) {
				vct.clear();
				vct.push_back(vctr.x);
			}
			auto f = [&](int x) {
				for (int i = 1; i < vct.size(); i++) {
					if (x == vct[i])
						return true;
				}
				return false;
				};
			do{
				vctr.y = generator(engine);
			} while (f(vctr.y));
			vct.push_back(vctr.y);
		}

		rpos = new int[m_degree + 1];
		for (int i = 0; i < m_degree + 1; i++)
			rpos[i] = 1;

		int j = 0;
		for (int i = 0; i < 10;) {
			if (j != m_value[i].x - 1) {
				j++;
				rpos[j + 1] = rpos[j];
			}
			else {
				rpos[j + 1]++;
				i++;
			}
		}
	}

	void transpose()
	{
		int *num = new int[m_degree];
		for (int i = 0; i < m_degree; i++) num[i] = 0;
		for (vector3 vctr : m_value) 
			num[vctr.y - 1]++;

		int* cpot = new int[m_degree];
		cpot[0] = 1;
		for (int i = 1; i < m_degree; i++) 
			cpot[i] = cpot[i - 1] + num[i - 1];
		delete[] num;

		std::array<vector3, 10> value;
		for (int i = 0; i < 10; i++) {
			int col = m_value[i].y;
			int q = cpot[col - 1] - 1;
			value[q].x = m_value[i].y;
			value[q].y = m_value[i].x;
			value[q].value = m_value[i].value;
			cpot[col - 1]++;
		}
		delete[] cpot;

		m_value = value;
	}

	void print()
	{
		for (vector3 vctr : m_value) {
			std::cout << "(" << vctr.x << ", " << vctr.y << ", " << vctr.value << " )\n";
		}
		std::cout << "degree = " << m_degree << std::endl;
		std::cout << "------------------------------\nrow:\t";
		for (int i = 0; i < m_degree; i++) {
			std::cout << i + 1 << "\t";
		}
		std::cout << std::endl;
		std::cout << "\nrpos:\t";

		for (int i = 0; i < m_degree + 1; i++) {
			std::cout << rpos[i] << "\t";
		}
		std::cout << std::endl;
	}

	int** operator* (const sprarse_matrix& other)
	{
		int** result = create_matrix(m_degree);
		if (m_degree and other.m_degree and m_degree == other.m_degree) {
			for (int i = 0; i < m_degree; i++) {
				for (int j = rpos[i]; j < rpos[i + 1]; j++) {
					int other_row = m_value[j - 1].y;

					for (int k = other.rpos[other_row]; k < other.rpos[other_row + 1]; k++) {
						result[i][other.m_value[k-1].y] += m_value[j-1].value * other.m_value[k-1].value;
					}
				}
			}
		}
		return result;
	}

	~sprarse_matrix()
	{
		delete[] rpos;
	}
	
private:
	struct vector3 {
		int x, y;
		int value;
	};
	std::array<vector3, 10> m_value;
	int m_degree;
	int* rpos;
	
};

int main()
{
	my::Tree tree;
	std::vector<float> weight = {1.0f, 1.2f, 1.32f, 3.234f, 4.23424f, 0.43432f, };
	my::Tree* tr = tree.build_Huffman_tree(weight);

}

