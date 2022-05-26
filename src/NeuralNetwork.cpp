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
    Matrix target   = Matrix::fromArray(expectedOutputValue); // Crea la matriz target a partir del vector con los resultados esperados
    Matrix error;
    Matrix gradient;
    Matrix networkOutput;
    int outputLayer =1;
    vector<int> neuronasPorCapa = {5,6};
    int setDePesos = neuronasPorCapa.size()+1;
    vector<Matrix> biases;
    vector<Matrix> pesos;
    vector<Matrix> layerOutputs;

    int inputCount = entrada.size();

    //Creacion de pesos aleatorios y biases para una red de setsdePesos-1  pesos
    for (int indexCapa = 0; indexCapa < setDePesos-1; ++indexCapa){
        pesos.push_back(*(new Matrix(neuronasPorCapa[indexCapa] , inputCount)));
        biases.push_back(*(new Matrix( neuronasPorCapa[indexCapa] , 1)));
        inputCount = neuronasPorCapa[indexCapa];
    }
    //Ultimo set de pesos
    pesos.push_back(*(new Matrix(outputLayer , neuronasPorCapa[-1])));
    biases.push_back(*(new Matrix( neuronasPorCapa[-1] , 1)));



    // Training.
    // for (int epoch = 0; epoch < 5000; ++epoch) {

        // Forward propagation de 3 pesos
        for (int indexPeso = 0; indexPeso < setDePesos; ++indexPeso) {

             Matrix tempResults = Matrix::multiply(pesos[indexPeso], inputForLayer);
             tempResults.addMatrix(biases[indexPeso]);
             tempResults.sigmoid();
             layerOutputs.push_back(tempResults);
             inputForLayer = tempResults;
        }
    networkOutput = inputForLayer;

    // Calcular error en última capa y ajustar gradiente. layer[layersCount-2
    error    = Matrix::matrixSubstract(target, networkOutput/* Epoch Output */); // Crea la matriz error : Calculando el error de todos los output de nuestra red

    gradient = networkOutput.dsigmoid(); // Obtiene la gradiente de la derivada de la funcion de activacion
    gradient.multiply(error);           // Multiplica la gradiente por la matriz del error y almacena en la matriz gradiente
    gradient.multiply(this->learningRate); // Multiplica los resultados anteriores por el valor de la tasa de aprendizaje

    //transponer el output de la capa anterior
    Matrix previousLayerOutputTransposed = Matrix::transpose(layerOutputs[setDePesos - 2]);
    //Multiplica la gradiente por la transpuesta
    Matrix weightsPreviousLayerOutputDelta = Matrix::multiply(gradient, previousLayerOutputTransposed);

    pesos[-1].addMatrix(weightsPreviousLayerOutputDelta);
    biases[-1].addMatrix(gradient);


    Matrix weightsNextLayer = pesos[setDePesos - 1];
    Matrix weightsNextLayerTransposed;
    Matrix layerGradient;
    Matrix hiddenLayerErrors;
    Matrix weightsPreviousLayerDelta;
    for (int indexCapa = setDePesos - 2; indexCapa > 0; --indexCapa) {
        //transponer el output de la capa anterior
        //Multiplica la gradiente por la transpuesta de la capa anterior = pesosDeCapaDelta = lo que vamos
        //Sumar los pesos de la capa con el delta
        ///////////////////////////////////////////////////////////////////////////////////////////////////
        weightsNextLayerTransposed = Matrix::transpose(weightsNextLayer);
        hiddenLayerErrors = Matrix::multiply(weightsNextLayerTransposed, error);

        layerGradient = layerOutputs[indexCapa].dsigmoid();
        layerGradient.multiply(hiddenLayerErrors);
        layerGradient.multiply(this->learningRate);

        previousLayerOutputTransposed = Matrix::transpose(layerOutputs[indexCapa-1]);
        weightsPreviousLayerDelta = Matrix::multiply(layerGradient, previousLayerOutputTransposed);

        // Almacena los valores en la matriz de pesos inicial corregida
        pesos[indexCapa].addMatrix(weightsPreviousLayerDelta);
        biases[indexCapa].addMatrix(layerGradient);

        weightsNextLayer = pesos[indexCapa];
        //Matrix inputTransposed = Matrix::transpose(input);
        //Matrix weightsInputHiddenLayersDelta = Matrix::multiply(layerGradient, inputTransposed);

        // Almacena los valores en la matriz de pesos inicial corregida
        //weightsInputHiddenLayers.addMatrix(weightsInputHiddenLayersDelta);
        //this->biasHiddenLayer.addMatrix(layerGradient);
    }

    weightsNextLayerTransposed = Matrix::transpose(weightsNextLayer);
    hiddenLayerErrors = Matrix::multiply(weightsNextLayerTransposed, error);

    layerGradient = layerOutputs[0].dsigmoid();
    layerGradient.multiply(hiddenLayerErrors);
    layerGradient.multiply(this->learningRate);

    previousLayerOutputTransposed = Matrix::transpose(input);
    weightsPreviousLayerDelta = Matrix::multiply(layerGradient, previousLayerOutputTransposed);

    // Almacena los valores en la matriz de pesos inicial corregida
    pesos[0].addMatrix(weightsPreviousLayerDelta);
    biases[0].addMatrix(layerGradient);
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

    //Inicio del for

    Matrix gradient = output.dsigmoid(); // Obtiene la gradiente de la derivada de la funcion de activacion
    gradient.multiply(error);           // Multiplica la gradiente por la matriz del error y almacena el resultado en error
    gradient.multiply(this->learningRate); // Multiplica los resultados anteriores por el valor de la tasa de aprendizaje

    Matrix hiddenLayerTransposed = Matrix::transpose(hidden);
    //se calcula cuanto deben cambiar los pesos
    Matrix weightsHiddenOutputLayersDelta = Matrix::multiply(gradient, hiddenLayerTransposed);

    weightsHiddenOutputLayers.addMatrix(weightsHiddenOutputLayersDelta);
    this->biasOutputLayer.addMatrix(gradient);
    //////////////////////////////////////////////////////////////////////////////////////////////////////

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
