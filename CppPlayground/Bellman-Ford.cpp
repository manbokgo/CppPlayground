#include <vector>
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

const int INF = INT_MAX;
std::vector<int> BellmanFord(std::vector<Edge> Edges, int VertexNum, int Start)
{
	std::vector<int> distance(VertexNum, INF);
	distance[Start] = 0;

	for (int i = 1; i <= VertexNum; i++)
	{
		bool Change = false;
		for (Edge& e : Edges)
		{
			if (distance[e.src] == INF)
				continue;

			if (distance[e.dst] > distance[e.src] + e.weight)
			{
				distance[e.dst] = distance[e.src] + e.weight;
				Change = true;
			}
		}

		if (!Change)
		{
			std::cout << "최단 경로 찾기 완료 " << i << std::endl;
			break;
		}

		if (i == VertexNum && Change)
		{
			std::cout << "음의 폐로" << std::endl;
			break;
		}
	}

	return distance;
}

int main ()
{
	std::vector<Edge> Nav;
	Nav.emplace_back(0, 1, 3);
	Nav.emplace_back(0, 2, 2);
	Nav.emplace_back(0, 3, 5);
	Nav.emplace_back(1, 2, 2);
	Nav.emplace_back(2, 3, -1);
	Nav.emplace_back(3, 1, -2);

	std::vector<int> result = BellmanFord(Nav, 4, 0);

	return 0;
}