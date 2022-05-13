/*
    Created by Josef Ruzicka, Carlos Solorzano and Javier Molina.
    12/5/22.

    This code is adapted from the one shown in the following tutorial:
    https://towardsdatascience.com/understanding-and-implementing-neural-networks-in-java-from-scratch-61421bb6352c
    for learning purposes only.
*/

#include <iostream>
#include <vector>
#include "NeuralNetwork.hpp"


using namespace std;

int main()
{
    vector<vector<double> > values {
            vector<double>{0,0,0},
            vector<double>{1,0,0},
            vector<double>{1,1,0},
            vector<double>{1,1,1},
            vector<double>{0,1,0},
            vector<double>{0,1,1},
            vector<double>{0,0,1},
            vector<double>{1,0,1},

    };

    vector<vector<double>> expectedValues {
            vector<double>{0},
            vector<double>{1},
            vector<double>{0},
            vector<double>{1},
            vector<double>{1},
            vector<double>{0},
            vector<double>{1},
            vector<double>{0},




    };



    NeuralNetwork *neuralNetwork = new NeuralNetwork(3,100,1);
    vector<double> output;

    neuralNetwork->fit(values, expectedValues, 50000);



    vector<vector<double>> input {
            vector<double>{0,0}, {0,1}, {1,0}, {1,1}
    };

    for(auto value : values)
    {
       output.push_back( neuralNetwork->predict(value)[0]);

    }
    for (auto i:output) {
        cout<<i << endl;
    }


}
