/*
   Copyright 2017 Mitsuhito Ando

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

// スライドする時間間隔(デフォルトは15000ms)
float delay_ms = 15000;

// 入出力ピンの番号設定
const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 3;
const int RELAY_1_PIN = 4;
const int RELAY_2_PIN = 5;
const int BUTTON_1_STATUS_LED_PIN = 12;
const int BUTTON_2_STATUS_LED_PIN = 13;
const int POTENTIOMETER_PIN = A0;


//
// ピンモードの設定、割り込みピンの設定、シリアルポートの初期化
//
void setup()
{
  pinMode(BUTTON_1_STATUS_LED_PIN, OUTPUT);
  pinMode(BUTTON_2_STATUS_LED_PIN, OUTPUT);

  pinMode(RELAY_1_PIN, OUTPUT);
  pinMode(RELAY_2_PIN, OUTPUT);

  pinMode(POTENTIOMETER_PIN, INPUT);

  pinMode(BUTTON_1_PIN, INPUT);
  pinMode(BUTTON_2_PIN, INPUT);

  //Serial.begin(9600);
}

//
// ループ関数
//
void loop()
{

  // スライドプロジェクタAを先にスライドさせる信号を送る
  PORTD |= B00010000;
  //delay(20);

  // スライドプロジェクタBをスライドさせる信号を送る
  PORTD |= B00100000;

  // AとB同時にスライドさせる信号を送る
  //PORTD |= B00110000;

  // リレー信号を200ms保持する
  delay(200);

  // AとBのスライドプロジェクタのスライドを止める
  PORTD &= B11001111;

  // 可変抵抗で読み取った時間間隔分停止を保持する
  delay(delay_ms);
}
