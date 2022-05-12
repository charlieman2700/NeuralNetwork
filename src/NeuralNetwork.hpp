#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <vector>
#include "Matrix.hpp";

#pragma once
using namespace std;

class NeuralNetwork
{
public:
    Matrix weightsInputHiddenLayers, weightsHiddenOutputLayers,
            biasHiddenLayer, biasOutputLayer;
    double  learningRate = 0.01; 

    NeuralNetwork(int inputLayer, int hiddenLayer, int outputLayer);

    ~NeuralNetwork();

    vector<double> predict(vector<double> values);

    void train(vector<double> values, vector<double> expectedValues);

    void fit(vector<vector<double>> values, vector<vector<double>> expectedValues, int epochs);

};

#endif