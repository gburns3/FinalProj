#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <cmath>
#include <time.h>

using namespace std;

template <typename T>
class KMeansCluster {

	T data;
	int dimensions;
	vector<vector<float> > groupCenters;
	vector<int> groups;

	public:
		KMeansCluster(T data);
		void cluster(int numGroups, int epochs);
		void printGroupCenters();
		void printGroups();
};

template <typename T>
KMeansCluster<T>::KMeansCluster(T testData) {
	this->data = testData;
	this->dimensions = data[0].size();
	this->groups.resize(data.size());

	srand(time(NULL));
}

template <typename T>
void KMeansCluster<T>::cluster(int numGroups, int epochs) {

	// Reset groupCenters and initialize to random points.
	this->groupCenters.resize(0);

	for (int i = 0; i < numGroups; i++) {
		this->groupCenters.push_back(vector<float>());

		for (int j = 0; j < this->data[0].size(); j++) {
			this->groupCenters[i].push_back(rand() % 5);
		}
	}

	for (int epoch = 0; epoch < epochs; epoch++) {

		// Determine which group each point is closest to.
		for (int point = 0; point < data.size(); point++) {
			multimap<float, int> centerDistances;
			
			// Determine distance from each group.
			for (int i = 0; i < groupCenters.size(); i++) {
				float centerDistance = 0;

				for (int j = 0; j < groupCenters[i].size(); j++) {
					centerDistance += pow((data[point][j] - groupCenters[i][j]), 2);
				}

				centerDistance = sqrt(centerDistance);
				centerDistances.insert(make_pair(centerDistance, i));
			}

			groups[point] = centerDistances.begin()->second;
		}

		// For each group, determine how many points belong to it, and sum all 
		// vectors in that group.
		for (int group = 0; group < groupCenters.size(); group++) {
			float numInGroup = 0;
			vector<float> pointSums(data[0].size(), 0); 

			for (int i = 0; i < groups.size(); i++) {

				if (groups[i] == group) {
					numInGroup++;

					for (int j = 0; j < data[i].size(); j++) {
						pointSums[j] += data[i][j];
					}
				}
			}


			// Set group center to the average of all points currently in group.
			for (int i = 0; i < groupCenters[group].size(); i++) {

				if (numInGroup) {
					groupCenters[group][i] = pointSums[i] / numInGroup;
				}
			}
		}	
	}
}

template <typename T>
void KMeansCluster<T>::printGroupCenters() {

	for (int i = 0; i < groupCenters.size(); i++) {

		for (int j = 0; j < groupCenters[i].size(); j++) {
			cout << groupCenters[i][j] << " ";
		}
		cout << endl;
	}
}

template <typename T>
void KMeansCluster<T>::printGroups() {
	for (int i = 0; i < groups.size(); i++) {
		cout << groups[i] << endl;
	}
}
