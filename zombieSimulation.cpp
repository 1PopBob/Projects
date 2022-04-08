#include <iostream>
#include <cmath>
#include <climits>
#include <stdlib.h>
using namespace std;

int main()
{
	int N, k, M, seed;
	int personBitten = 0, nights = 0, maxNights = 0, minNights = 0;
	double averageNights = 0, totalNights = 0;
	bool pop[500];
	cout << "Enter the following: N k M seed " << endl;;
	cin >> N >> k >> M >> seed;
	int infected = k, tempk = k;
	srand(seed);

	for(int i = 0; i < M; i++) // determines amount of simulations to run
	{
		for(int j = 0; j < k; j++)
		{
			pop[j] = true;
		}
		for(int j = k; j < N; j++)
		{
			pop[j] = false;
		}
		while(N != k && N > k) // iterates until all humans are zombies
		{
			for(int j = 0; j < k; j++) // gives k zombies a chance to bite | one completion of this loop gives a night
			{
				personBitten = rand()%N; // represents the person/zombie the zombie will bite
				if(pop[personBitten] != true)
				{
					pop[personBitten] = true;
					infected++;
				}
				else if(pop[personBitten] == true)
				{
					continue;
				}
			}
			k = infected;
			nights++;
		}
		if(nights > maxNights)
		{
			maxNights = nights;
		}	
		if(i == 0)
		{
			minNights = nights;
		}	
		else if(nights < minNights)
		{
			minNights = nights;
		}
		totalNights += nights;
		nights = 0;
		k = tempk;
		infected = k;
	}
	averageNights = totalNights / M;

	if(N > k)
	{
		cout << "Average Nights: " << averageNights << endl;
		cout << "Max Nights: " << maxNights << endl;
		cout << "Min Nights: " << minNights << endl;
	}

	return 0;
}
