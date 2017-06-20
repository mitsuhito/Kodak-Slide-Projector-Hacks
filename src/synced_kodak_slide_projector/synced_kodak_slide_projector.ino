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

#include <MsTimer2.h>

// スライドする時間間隔(デフォルトは1000ms)
float delay_ms = 1000;

// 再生中かどうかのフラグ
volatile boolean is_playing = false;

// ボタン1の状態を表す変数
volatile boolean button_1_input_status = HIGH;

// ボタン2の状態を表す変数
volatile boolean button_2_input_status = HIGH;

// 最後にボタン1が押された時の時間を保持する変数
volatile unsigned long button_1_pressed_time = 0;

// 最後にボタン2が押された時の時間を保持する変数
volatile unsigned long button_2_pressed_time = 0;

// チャタリングを無視する時間定数(ms)
const int BOUNCE = 100;

// 入出力ピンの番号設定
const int BUTTON_1_PIN = 2;
const int BUTTON_2_PIN = 3;
const int RELAY_1_PIN = 4;
const int RELAY_2_PIN = 5;
const int BUTTON_1_STATUS_LED_PIN = 12;
const int BUTTON_2_STATUS_LED_PIN = 13;
const int POTENTIOMETER_PIN = A0;

// 最小スライド時間間隔(900ms)
const int MIN_DELAY = 900;
// 最大スライド時間間隔(20000ms)
const int MAX_DELAY = 20000;

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

  MsTimer2::set(100, watch_button_status);
  MsTimer2::start();

  Serial.begin(9600);
}

//
// ループ関数
//
void loop()
{
  // 可変抵抗の値を読み取る
  int a0_raw = analogRead(POTENTIOMETER_PIN);

  // 読み取った可変抵抗の値を、MIN_DELAYからMAX_DELAYの数値の間にスケーリングし直す
  delay_ms = map(a0_raw, 0, 1023, MIN_DELAY, MAX_DELAY);

  // デバッグ用
  Serial.print(millis());
  Serial.print(" ");
  Serial.print("delay(ms)=");
  Serial.print(delay_ms);
  Serial.print(" is_playing=");
  Serial.println(is_playing);

  // 再生ボタンが押されていた場合
  if (is_playing)
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
    int cnt = delay_ms;
    while (cnt--)
    {
      // 停止ボタンが押されたら待ち状態をキャンセルする
      if(is_playing == false)
        break;
      delay(1);
    }
  }
}

void watch_button_status()
{
  //
  // ボタン1の状態監視
  //
  bool b1 = digitalRead(BUTTON_1_PIN);
  if ((millis() - button_1_pressed_time) > BOUNCE)
  {
    if (button_1_input_status != b1)
    {
      button_1_input_status = !button_1_input_status;
      button_1_pressed_time = millis();
    }
    if (button_1_input_status == LOW)
      is_playing = true;
  }
  // 再生中かどうかをLEDで表示
  digitalWrite(BUTTON_1_STATUS_LED_PIN, is_playing);

  //
  // ボタン2の状態監視
  //
  bool b2 = digitalRead(BUTTON_2_PIN);
  if ((millis() - button_2_pressed_time) > BOUNCE)
  {
    if (button_2_input_status != b2)
    {
      button_2_input_status = !button_2_input_status;
      button_2_pressed_time = millis();
    }
    if (button_2_input_status == LOW)
      is_playing = false;
  }
  digitalWrite(BUTTON_2_STATUS_LED_PIN, !button_2_input_status);
}
