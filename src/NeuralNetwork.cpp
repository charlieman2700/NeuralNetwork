//
// Created by Charlie Solorzano  on 12/5/22.
//

#include <iostream>
#include "NeuralNetwork.hpp"
#include <random>




using namespace std;


NeuralNetwork::NeuralNetwork(int inputLayer, int neuronCount, int outputLayer) {
    this->weightsInputHiddenLayers  = *(new Matrix(neuronCount, inputLayer));

    this->weightsHiddenOutputLayers = *(new Matrix(outputLayer, neuronCount));
    this->learningRate = 0.01;


    this->biasHiddenLayer  = *(new Matrix(neuronCount, 1));
    this->biasOutputLayer  = *(new Matrix(outputLayer, 1));

}


NeuralNetwork::~NeuralNetwork() {

}

vector<double> NeuralNetwork::predict(vector<double> values){
    Matrix input  = Matrix::fromArray(values); // Queda una matriz con una sola columna

    Matrix hidden = Matrix::multiply(this->weightsInputHiddenLayers, input); // Explicacion debajo
    /*
     * Queda una matriz con las filas de weights input hidden layer =  neuron count y las columnas de input = 1
     */
    hidden.addMatrix(this->biasHiddenLayer); // Se le suman los bias al matriz anterior
    hidden.sigmoid();

    //2 Capa
    // Hidden tiene almacenado el resultado final de esta capa

    Matrix output = Matrix::multiply(this->weightsHiddenOutputLayers, hidden);
    output.addMatrix(this->biasOutputLayer);
    output.sigmoid();

    return output.toArray();
}







void NeuralNetwork::trainNuevo(vector<double> entrada, vector<double> expectedOutputValue){
    Matrix input  = Matrix::fromArray(entrada); //columna
    Matrix inputForLayer  = Matrix::fromArray(entrada); //columna

    vector<int> neuronasPorCapa = {4,5,6};
    vector<Matrix> biases;
    vector<Matrix> capas;
    int inputCount = entrada.size();

    //Creacion de pesos aleatorios y biases para una red de 3 capas
    for (int indexCapa = 0; indexCapa < 3; ++indexCapa){
        capas.push_back(*(new Matrix( neuronasPorCapa[indexCapa] , inputCount)));
        biases.push_back(*(new Matrix( neuronasPorCapa[indexCapa] , 1)));
        inputCount = neuronasPorCapa[indexCapa];
    }

    // Training.
    // for (int epoch = 0; epoch < 5000; ++epoch) {

        // Forward propagation de 3 capas
        for (int indexCapa = 0; indexCapa < 3; ++indexCapa) {

             Matrix tempResults = Matrix::multiply(capas[indexCapa], inputForLayer);
             tempResults.addMatrix(biases[indexCapa]);
             tempResults.sigmoid();
             inputForLayer = tempResults;

	 
        }
    
        // Calcular error en última capa y ajustar gradiente.
    
	// for (int indexCapa = 3; indexCapa > 0; --indexCapa) {
        //	backPropagation
        //}
    
    //}

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
    Matrix input  = Matrix::fromArray(values); //columna
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
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(0,values.size()-1);
    for (int epoch = 0; epoch < epochs; epoch++){
        int sampleN = distribution(generator);;
        this->train(values[sampleN], expectedValues[sampleN]);
    }
}
