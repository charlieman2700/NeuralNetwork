#include <iostream>
#include <vector>
#include "./src/NeuralNetwork.hpp"

using namespace std;

int main()
{
    vector<vector<double>> values{
            vector<double>{0, 0, 0},
            vector<double>{1, 0, 0},
            vector<double>{1, 1, 0},
            vector<double>{1, 1, 1},
            vector<double>{0, 1, 0},
            vector<double>{0, 1, 1},
            vector<double>{0, 0, 1},
            vector<double>{1, 0, 1},

    };

    vector<vector<double>> expectedValues{
            vector<double>{0},
            vector<double>{1},
            vector<double>{0},
            vector<double>{1},
            vector<double>{1},
            vector<double>{0},
            vector<double>{1},
            vector<double>{0},

    };

    vector<int> layers = {10,10,10};
    NeuralNetwork neuralNetwork = NeuralNetwork(layers);

    // neuralNetwork->trainNuevo(values[0], expectedValues[0]);
    vector<double> output;
    // std::cout << "de vuelta en main";
    //
    neuralNetwork.fit(values, expectedValues, 50000);
    //
    //
    //
    //
    // neuralNetwork->trainNuevo(values, expectedValues, 20000);
    vector<vector<double>> input{
            vector<double>{0, 0, 0}, /*{0,1,0}, {1,0,0}, {1,1,1}*/
    };

    for (auto value : values)
    {

        output.push_back(neuralNetwork.predict(value)[0]);

        //
    }

    for (auto i : output)
    {
        std::cout << i << endl;
        if (i > 0.5)
        {
            cout << 1 << endl;
        }
        else
        {
            cout << 0 << endl;
        }
    }
}
