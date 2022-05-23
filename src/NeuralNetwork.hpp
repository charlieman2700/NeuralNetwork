//
// Created by Charlie Solorzano  on 12/5/22.
//

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
    void trainNuevo(vector<double> values, vector<double> expectedValues);



    void fit(vector<vector<double> > values, vector<vector<double> > expectedValues, int epochs);
};


#endif //NEURALNETWORK_NEURALNETWORK_HPP
