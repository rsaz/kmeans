#ifndef CLUSTER_H
#define CLUSTER_H
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class Cluster
{
private:
	static constexpr double THRESHOLD = 0.7;
	static constexpr int ITERATIONS = 10;
	static constexpr int DIMENSIONS = 2;

	int numOfRows = 0;
	int itrCounter = 0;
	int noOfClusters = 0;
	string fileName;

	vector<int> cluster;
	vector<vector<string>> centroid;
	vector<string> data;

public:
	virtual ~Cluster();
	Cluster(const string& fileName);
	virtual void RunCluster(int noOfClusters);
	virtual int GetNumOfRows();

private:
	vector<vector<string>> runCluster(vector<string>& data, int noOfClusters, vector<vector<string>>& centroid);
	void WriteDataToFile();
	void AddinDataToCentroids();
	bool ReadDataFromFile();
	std::string FileNameGenerator(std::string pHeader, int pIndex, std::string pExt);
};

#endif