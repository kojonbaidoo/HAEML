/*
Input Layer
Hidden Layer
Output Layer
Non-linearity
    Softmax
    Relu
*/

/*
ARCHITECTURE
L0 3: INPUT LAYER
L1 16: HIDDEN LAYER
L2 16: HIDDEN LAYER
L3 3: Output LAYER
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define INPUT_LAYER 3
#define L1_LAYER 16
#define L2_LAYER 16
#define L3_LAYER 3

#define L1_WEIGHT_ROW 16
#define L1_WEIGHT_COL 3
#define L1_BIAS_COUNT 16

#define L2_WEIGHT_ROW 16
#define L2_WEIGHT_COL 16
#define L2_BIAS_COUNT 16

#define L3_WEIGHT_ROW 3
#define L3_WEIGHT_COL 16
#define L3_BIAS_COUNT 3

double L1_WEIGHTS[L1_WEIGHT_ROW][L1_WEIGHT_COL] = {
    {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0},
    {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}, 
    {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}, 
    {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}, {1.0,1.0,1.0}
};

double L1_BIAS[L1_BIAS_COUNT] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

double L2_WEIGHTS[L2_WEIGHT_ROW][L2_WEIGHT_COL] = {
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},{1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
};

double L3_WEIGHTS[L3_WEIGHT_ROW][L3_WEIGHT_COL] = {
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0},
    {1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0}
};

void Layer1(double *input_value, double *L1_OUTPUT);
void Layer2(double *L1_OUTPUT, double *L2_OUTPUT);
void Layer3(double *L2_OUTPUT,double *L3_OUTPUT);

double relu(double value);
double softmax(double value, double exponent_sum_of_all);

int main(){
    double input_values[3] = {1,1,1};
    double L1_OUTPUT[L1_LAYER];
    double L2_OUTPUT[L2_LAYER];
    double L3_OUTPUT[L3_LAYER];

    Layer1(input_values, L1_OUTPUT);
    Layer2(L1_OUTPUT, L2_OUTPUT);
    // Layer3(L2_OUTPUT,L3_OUTPUT);

    for(int i = 0;i < L2_WEIGHT_ROW;i++){
        printf("%f\n",L2_OUTPUT[i]);
    }
}

void Layer1(double *input_value, double *L1_OUTPUT){
    double temp;
    for(int i = 0;i < L1_WEIGHT_ROW;i++){
        temp = (input_value[0] * L1_WEIGHTS[i][0]) + (input_value[1] * L1_WEIGHTS[i][1]) + (input_value[2] * L1_WEIGHTS[i][2]) + L1_BIAS[i];
        L1_OUTPUT[i] = relu(temp);
    }
}

void Layer2(double *L1_OUTPUT, double *L2_OUTPUT){

}
void Layer3(double *L2_OUTPUT,double *L3_OUTPUT){

}

double relu(double value){
    return (value > 0) * value;
}

double softmax(double value, double exponent_sum_of_all){
    double e = 2.71828;
    double result = pow(e,value) / exponent_sum_of_all;
    return result;
}