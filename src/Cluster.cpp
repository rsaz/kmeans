#include "Cluster.h"
#include "ArrayHelper.h"
#include "ExceptionHelper.h"
#include "Jaro.h"
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

Cluster::Cluster(const string& fileName)
{
	this->fileName = fileName;
	ReadDataFromFile();
}

Cluster::~Cluster() {}

void Cluster::RunCluster(int noOfClusters)
{
	this->noOfClusters = noOfClusters;
	AddinDataToCentroids();
	runCluster(data, noOfClusters, centroid);
}

vector<vector<string>> Cluster::runCluster(vector<string>& data, int noOfClusters, vector<vector<string>>& centroid)
{
	vector<vector<double>> distance = RectangularVectors::RectangularDoubleVector(noOfClusters, data.size());
	cluster = std::vector<int>(data.size());
	vector<double> clusterCount(noOfClusters);

	centroid[0] = centroid[1];

	//Using Jaro-Wrinkler to calculate distance
	for (int i = 0; i < noOfClusters; i++)
	{
		for (int j = 0; j < data.size(); j++)
		{
			distance[i][j] = jro::WinklerDistance(data[j], centroid[0][i]);
			std::wcout << distance[i][j] << L" ,";
		}

		std::cout << std::endl;
	}

	//Rank data based on the distance
	for (int i = 0; i < distance[0].size(); i++)
	{
		int row = 0;
		double max = 0.0;
		int j;
		for (j = 0; j < distance.size(); j++)
		{
			if (distance[j][i] > max)
			{
				max = distance[j][i];
				row = j;

			}
		}
		
		centroid[1][row] = centroid[1][row] + data[j];
		clusterCount[row] = clusterCount[row] + 1;

		cluster[i] = row;
	}

	std::cout << std::endl;
	std::wcout << L"Clusters: " << std::endl;

	for (int i = 0; i < noOfClusters; i++)
	{
		for (int l = 0; l < data.size(); l++)
		{
			if (cluster[l] == i)
			{
				std::cout << data[l] << L" ,";
			}
		}
		std::wcout << std::endl;
	}
	
    std::cout << std::endl;

	//Verify matching of the clusters based on distance
	double disSum = 0.0;
	bool done = true;
	for (int i = 0; i < noOfClusters; i++)
	{
		for (int j = 0; j < numOfRows; j++)
		{
			disSum += distance[i][j];
		}

	}

	std::wcout << L"Total Distance:" << disSum << std::endl;
	std::wcout << L"Avg Distance from Centroids: " << (disSum / ((double)numOfRows * noOfClusters)) << std::endl;

	if ((disSum / ((double)numOfRows * noOfClusters)) <= THRESHOLD && itrCounter < ITERATIONS)
	{
		done = false;
		AddinDataToCentroids();
	}

	if (!done)
	{
		itrCounter++;
		runCluster(data, noOfClusters, centroid);
	}
	else
	{
		WriteDataToFile();
	}

	return centroid;
}

void Cluster::WriteDataToFile()
{
	
	try
	{
		
		for (int i = 0; i < noOfClusters; i++)
		{
            std::ofstream out;
			out.open(FileNameGenerator("cluster", noOfClusters, ".txt"), std::ios::out);

			for (int j = 0; j < data.size(); j++)
			{
				if (cluster[j] == i) out << data[i] << " ," << std::endl;
			}
			
			out.close();
		}
	}
	catch (const IOException& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void Cluster::AddinDataToCentroids()
{
	srand((unsigned)time(0));
	centroid = RectangularVectors::RectangularStdWstringVector(DIMENSIONS, noOfClusters);
	std::vector<int> listWithRandoms;
	int index = 0;

	for (int i = 0; i < noOfClusters; i++)
	{
		do
		{
			index = rand() % numOfRows;
		} while (std::find(listWithRandoms.begin(), listWithRandoms.end(), index) != listWithRandoms.end());
		listWithRandoms.push_back(index);
	}

	for (int i = 0; i < noOfClusters; i++)
		centroid[1][i] = data[listWithRandoms[i]];
}

bool Cluster::ReadDataFromFile()
{
	try
	{
		std::ifstream in(fileName.c_str());

		if (!in)
		{
			std::cerr << "Failed to open the file : " << fileName << std::endl;
			return false;
		}
		
		std::string line;
		while (std::getline(in, line))
		{
			if (line.size() > 0)
			{
				data.push_back(line);
				numOfRows++;
			}
		}

		in.close();

		return true;
	}
	catch (const IOException& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

std::string Cluster::FileNameGenerator(std::string pHeader, int pIndex, std::string pExt)
{
	std::string header = pHeader;
	int clusterNumber = pIndex;
	std::string extension = pExt;
	std::string file = header.append(std::to_string(clusterNumber)).append(extension);
	return file;
}

int Cluster::GetNumOfRows()
{
	return numOfRows;
}