﻿#include <vector>
#include <iostream>


struct Edge
{
	int src;
	int dst;
	int weight;

	Edge(int src, int dst, int weight)
	{
		this->src = src;
		this->dst = dst;
		this->weight = weight;
	}
};


// std::vector<int> OutDistance(VertexNum, INT_MAX)
bool BellmanFord(std::vector<int>* OutDistance, const std::vector<Edge>& Edges, int Start)
{
	std::vector<int>& distance = *OutDistance;
	const int VertexNum = distance.size();
	distance[Start] = 0;

	for (int i = 1; i <= VertexNum; i++)
	{
		bool Change = false;
		for (const Edge& e : Edges)
		{
			if (distance[e.src] == INT_MAX)
				continue;

			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				distance[e.dst] = distance[e.src] + e.weight;
				Change = true;

				// N 라운드에서 가중치 변경은 음의 폐로를 의미함
				if (i == VertexNum)
					return false;
			}
		}

		if (!Change)
			break;
	}

	return true;
}

int main()
{
	std::vector<Edge> Nav;
	Nav.emplace_back(0, 1, 3);
	Nav.emplace_back(0, 2, 2);
	Nav.emplace_back(0, 3, 5);
	Nav.emplace_back(1, 2, 2);
	Nav.emplace_back(2, 3, -1);
	Nav.emplace_back(3, 1, -5);

	std::vector<int> distance(4, INT_MAX);
	bool Success = BellmanFord(&distance, Nav, 0);

	return 0;
}
