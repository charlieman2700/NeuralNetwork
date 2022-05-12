#include <iostream>
#include <vector>
#include "Matrix.hpp"
#include "NeuralNetwork.hpp"

using namespace std;

int main()
{
    vector<vector<double>> values { 
        vector<double>{0,0}, 
        vector<double>{1,0}, 
        vector<double>{0,1},
        vector<double>{1,1} 
    };

    vector<vector<double>> expectedValues { 
        vector<double>{0,1,1,0}
    }; 

    vector<vector<double>> input { 
        vector<double>{0,0}, {0,1}, {1,0}, {1,1}
    }; 

    NeuralNetwork *neuralNetwork = new NeuralNetwork(2,10,1);
    vector<double> output;
    
    neuralNetwork->fit(values, expectedValues, 5000);

    for(auto value : input)
    {
        output = neuralNetwork->predict(value);
    } 
}
