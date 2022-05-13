/*
    Created by Josef Ruzicka, Carlos Solorzano and Javier Molina.
    12/5/22.

    This code is adapted from the one shown in the following tutorial:
    https://towardsdatascience.com/understanding-and-implementing-neural-networks-in-java-from-scratch-61421bb6352c
    for learning purposes only.
*/

#ifndef NEURALNETWORK_NEURALNETWORK_HPP
#define NEURALNETWORK_NEURALNETWORK_HPP


#include "Matrix.hpp"
#include <vector>

class NeuralNetwork {
public:
    Matrix weightsInputHiddenLayers, weightsHiddenOutputLayers,
            biasHiddenLayer, biasOutputLayer;

    double learningRate;

    NeuralNetwork(int inputLayer, int neuronCount, int outputLayer);

    virtual ~NeuralNetwork();

    vector<double> predict(vector<double> values);

    void train(vector<double> values, vector<double> expectedValues);

    void fit(vector<vector<double> > values, vector<vector<double> > expectedValues, int epochs);
};


#endif //NEURALNETWORK_NEURALNETWORK_HPP
