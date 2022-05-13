//
// Created by Charlie Solorzano  on 12/5/22.
//

#include "NeuralNetwork.hpp"
#include "time.h"


using namespace std;


NeuralNetwork::NeuralNetwork(int inputLayer, int hiddenLayer, int outputLayer) {
    this->weightsInputHiddenLayers  = *(new Matrix(hiddenLayer, inputLayer));
    this->weightsHiddenOutputLayers = *(new Matrix(outputLayer, hiddenLayer));
    this->learningRate = 0.01;

    this->biasHiddenLayer  = *(new Matrix(hiddenLayer, 1));
    this->biasOutputLayer  = *(new Matrix(outputLayer, 1));

}


NeuralNetwork::~NeuralNetwork() {

}

vector<double> NeuralNetwork::predict(vector<double> values){
    Matrix input  = Matrix::fromArray(values);
    Matrix hidden = Matrix::multiply(this->weightsInputHiddenLayers, input);
    hidden.addMatrix(this->biasHiddenLayer);
    hidden.sigmoid();

    Matrix output = Matrix::multiply(this->weightsHiddenOutputLayers, hidden);
    output.addMatrix(this->biasOutputLayer);
    output.sigmoid();

    return output.toArray();
}

void NeuralNetwork::train(vector<double> values, vector<double> expectedValues){


    //________________________________________________________________________________________________

    // Primera Capa

    //________________________________________________________________________________________________


    /**
    / Agarra el vector value y lo transforma en matriz para poder utilizar producto punto-
    / entre el valor de cada entrada por los pesos de cada matriz
    /
    */
    Matrix input  = Matrix::fromArray(values);
    Matrix hidden = Matrix::multiply(this->weightsInputHiddenLayers, input);

    // Le suma el bias al resultado de la multiplicacion
    hidden.addMatrix(this->biasHiddenLayer);
    // Le aplica la funcion de activacion al resultado obtenido
    hidden.sigmoid();

    //________________________________________________________________________________________________

    // Segunda capa

    //________________________________________________________________________________________________



    // Despues cada resultado de las neuronas obtenidas se lo multiplica a los pesos de la segunda capa de neuronas
    Matrix output = Matrix::multiply(this->weightsHiddenOutputLayers, hidden);
    // Le suma el segundo set de bias
    output.addMatrix(this->biasOutputLayer);
    // Le aplica la funcion sigmoid a estos segunods resultados
    output.sigmoid();

    //________________________________________________________________________________________________

    //                   Calculo del Descenso por gradiente para mejorar mas rapido

    //________________________________________________________________________________________________


    Matrix target   = Matrix::fromArray(expectedValues); // Crea la matriz target a partir del vector con los resultados esperados
    Matrix error    = Matrix::matrixSubstract(target, output); // Crea la matriz error : Calculando el error de todos los output de nuestra red
    Matrix gradient = output.dsigmoid(); // Obtiene la gradiente de la derivada de la funcion de activacion
    gradient.multiply(error);           // Multiplica la gradiente por la matriz del error y almacena el resultado en error
    gradient.multiply(this->learningRate); // Multiplica los resultados anteriores por el valor de la tasa de aprendizaje

    //________________________________________________________________________________________________

    //                                              BackPropagation

    //________________________________________________________________________________________________


    Matrix hiddenLayerTransposed = Matrix::transpose(hidden);
    Matrix weightsHiddenOutputLayersDelta = Matrix::multiply(gradient, hiddenLayerTransposed);

    weightsHiddenOutputLayers.addMatrix(weightsHiddenOutputLayersDelta);
    this->biasOutputLayer.addMatrix(gradient);

    Matrix weightsHiddenOutputLayersTransposed = Matrix::transpose(this->weightsHiddenOutputLayers);
    Matrix hiddenLayerErrors = Matrix::multiply(weightsHiddenOutputLayersTransposed, error);

    Matrix hiddenLayerGradient = hidden.dsigmoid();
    hiddenLayerGradient.multiply(hiddenLayerErrors);
    hiddenLayerGradient.multiply(this->learningRate);

    Matrix inputTransposed = Matrix::transpose(input);
    Matrix weightsInputHiddenLayersDelta = Matrix::multiply(hiddenLayerGradient, inputTransposed);

    // Almacena los valores en la matriz de pesos inicial corregida
    weightsInputHiddenLayers.addMatrix(weightsInputHiddenLayersDelta);
    this->biasHiddenLayer.addMatrix(hiddenLayerGradient);
}

void NeuralNetwork::fit(vector<vector<double>> values, vector<vector<double>> expectedValues, int epochs){
    srand(time(NULL));
    for (int epoch = 0; epoch < epochs; epoch++){
        //int sampleN = (int)(double)(rand()) / ((double)(RAND_MAX / (1 - -1)))
        int sampleN = (int)rand()/RAND_MAX * values.size();
        this->train(values[sampleN], expectedValues[sampleN]);
    }
}
