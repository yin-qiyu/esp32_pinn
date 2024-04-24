#include <EloquentTinyML.h>
#include "nn_model.h"
#include "math.h"

#define NUMBER_OF_INPUTS 2
#define NUMBER_OF_OUTPUTS 1
#define TENSOR_ARENA_SIZE 2*1024


static const uint8_t LED_BUILTIN1 = 48;
static const uint8_t temp_num = 30;
static const uint8_t soc_num = 30;
static const uint8_t strain_num = 30;

// 生成Eloquent对象
Eloquent::TinyML::TfLite<NUMBER_OF_INPUTS, NUMBER_OF_OUTPUTS, TENSOR_ARENA_SIZE> ml;

float x_test[30][2] = {
  {26.06,0.22},{26.09,0.22},{26.11,0.22},{26.11,0.23},{26.13,0.23},
  {26.16,0.23},{26.17,0.23},{26.17,0.23},{26.22,0.23}, {26.20,0.23},
  {26.24,0.23},{26.25,0.23},{26.26,0.23},{26.27,0.23},{26.28,0.23},
  {26.32,0.23},{26.31,0.23},{26.33,0.24}, {26.37,0.24}, {26.38,0.24},
  {26.40,0.24}, {26.42,0.24}, {26.45,0.24}, {26.43,0.24}, {26.46,0.24}, 
  {26.46,0.24}, {26.48,0.24}, {26.49,0.24}, {26.50,0.24}, {26.51,0.24}
};

// float temp[temp_num] = 
//     {26.06, 26.09, 26.11, 26.11, 26.13, 26.16, 26.17, 26.17, 26.22, 26.20, 
//     26.24, 26.25, 26.26, 26.27, 26.28, 26.32, 26.31, 26.33, 26.37, 26.38, 
//     26.40, 26.42, 26.45, 26.43, 26.46, 26.46, 26.48, 26.49, 26.50, 26.51};

// float soc[soc_num]= 
//     {0.22, 0.22, 0.22, 0.23, 0.23, 0.23, 0.23, 0.23, 0.23, 0.23,
//      0.23, 0.23, 0.23, 0.23, 0.23, 0.23, 0.23, 0.24, 0.24, 0.24,
//      0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24, 0.24};
     
float strain[strain_num]= 
    {123.20, 123.36, 123.30, 123.29, 123.31, 123.43, 123.33, 123.35, 123.22, 123.30,
    123.37, 123.26, 123.30, 123.36, 123.28, 123.43, 123.37, 123.42, 123.25, 123.36,
    123.36, 123.29, 123.50, 123.47, 123.42, 123.31, 123.30, 123.51, 123.24, 123.43};



// 设置led的引脚为2



// 初始化串口，led引脚，加载神经网络模型以及0-pi上等间隔采样500个x的值
void setup() {
    Serial.begin(115200);
    // pinMode(LED_BUILTIN1, OUTPUT);
    ml.begin(pinn_model_tflite);
}

// 主循环，for循环中循环读取数组中x的值并使用神经网络推理预测值，使用串口输出x以及对应的真实值和预测值，同时将预测值输出PWM波到led引脚
void loop() {
    for(int i = 0; i < 30; i++)
    {
      // Serial.print("actual/predicted:%2f,%.2f\n"strain[i],(ml.predictClass(x_test[i]));
      float predicted = ml.predict(x_test[i]);
      Serial.print(strain[i]);
      Serial.print(", ");
      Serial.print(predicted);
      Serial.print("\n ");

      // float y = sin(x[i]);
      // float y = sin(x);
            
      // Serial.print("sin(");
      // Serial.print(x[i]);
      // Serial.print(") = ");
      // Serial.printf("sin:%.2f\n", x[i], sin(x[i]));
      // // Serial.print(y);
      // // Serial.print("\t predicted: ");
      // // Serial.println(predicted);
      // Serial.printf("predicted:%.2f\n", predicted);
      // Serial.printf("demo:%.2f,%.2f\n",y,predicted);
      // Serial.printf("demo:%.2f,%.2f\n",strain[i],predicted);
      // analogWrite(LED_BUILTIN1, predicted * 255);
      delay(100);
    }
}