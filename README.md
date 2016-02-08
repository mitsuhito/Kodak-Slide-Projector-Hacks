Kodak-Slide-Projector-Hacks
===========================
## システム構成

   ![Diagram](https://raw.github.com/mitsuhito/Kodak-Slide-Projector-Hacks/master/synced_kodak_slide_projector_diagram.jpg)

---

## 回路図

   ![Schimatic](https://raw.github.com/mitsuhito/Kodak-Slide-Projector-Hacks/master/schimatic.jpg)
   [https://github.com/mitsuhito/Kodak-Slide-Projector-Hacks/blob/master/schimatic.pdf](https://github.com/mitsuhito/Kodak-Slide-Projector-Hacks/blob/master/schimatic.pdf)

---

## プログラムの書き換え方 (ハードウェア上に実装されているつまみを利用する場合)
1. Arduino IDE(開発環境)を入れる。
   [Arduino 1.6.7](http://arduino.cc/en/Main/Software#toc2)をダウンロード。

2. ダウンロードしたarduino-1.6.7-(macosx, windows).zipを任意の場所で展開する。

3. Kodak Slide Projector HacksのArduino用ソースコードをダウンロードし、展開する。
   https://github.com/mitsuhito/Kodak-Slide-Projector-Hacks/archive/master.zip

4. Arduino IDEを起動する。

   ![Arduino IDE Icon](https://raw.github.com/mitsuhito/Kodak-Slide-Projector-Hacks/master/arduino_ide.jpg)

   このアイコンを見つけてダブルクリックする。

5. Arduino IDEのメニューバーから ```ファイル``` > ```開く``` を選択し、3番目でダウンロードした``` synced_kodak_slide_projector.ino``` を指定して開く。

6. (オプション)ソースコードの必要な部分の改変を行う。

   特に変更が必要になる可能性がある部分は、可変抵抗（つまみ）で変化させる事のできるスライド時間間隔を下記の部分を変更することで行える。

  ```
// 最小スライド時間間隔(900ms)
const int MIN_DELAY = 900;
// 最大スライド時間間隔(5000ms)
const int MAX_DELAY = 5000;
  ```

   ```900``` の部分を変える事で、可変抵抗を一番端まで回した時の最小スライド時間が変化する。

   ```5000``` の部分を変える事で、可変抵抗を一番端まで回した時の最大スライド時間が変化する。

   ここで使用する単位はミリ秒（1/1000秒）です。

7. Arduino UNOをUSBケーブルでコンピュータと接続する。

8. Arduino IDEのメニューバーから ```ツール``` > ```マイコンボード``` > ```Arduino/Genuino UNO``` を選択する。

9. Arduino IDEのメニューバーから ```ツール``` > ```シリアルポート``` > ```/dev/tty.usbmodem*``` あるいは ```/dev/cu.usbmodem*``` を選択する。

   ```/dev/tty.usbmodem``` もしくは ```/dev/cu.usbmodem``` からはじまる行を選択してください。末尾の文字は環境ごとに変化します。

10. Arduino IDEのメニューバーから ```ファイル``` > ```マイコンボードに書き込む``` を選択する。

   書き込みが完了した旨を伝えるメッセージが表示されれば書き込み完了。

---

## ハードウェア上に実装されているつまみを利用しないで、ソフトウェアだけでスライド時間間隔を指定する場合
1. Arduino IDE(開発環境)を入れる。
   [Arduino 1.6.7](http://arduino.cc/en/Main/Software#toc2)をダウンロード。

2. ダウンロードしたarduino-1.6.7-(macosx, windows).zipを任意の場所で展開する。

3. Kodak Slide Projector HacksのArduino用ソースコードをダウンロードし、展開する。
   https://github.com/mitsuhito/Kodak-Slide-Projector-Hacks/archive/master.zip

4. Arduino IDEを起動する。

   ![Arduino IDE Icon](https://raw.github.com/mitsuhito/Kodak-Slide-Projector-Hacks/master/arduino_ide.jpg)

   このアイコンを見つけてダブルクリックする。

5. Arduino IDEのメニューバーから ```ファイル``` > ```開く``` を選択し、3番目でダウンロードした``` synced_kodak_slide_projector_interval_fixed.ino``` を指定して開く。

6. スライドする時間間隔の変更があれば下記の部分の改変を行う。デフォルトは15秒。

  ```
  // 設定するスライド時間間隔(15000ミリ秒)
  const int DELAY_MS = 15000;
  ```

   ```15000``` の部分を変える事でスライドするまでに待機する時間が変わります。

   ここで使用する単位はミリ秒（1/1000秒）です。

7. Arduino UNOをUSBケーブルでコンピュータと接続する。

8. Arduino IDEのメニューバーから ```ツール``` > ```マイコンボード``` > ```Arduino/Genuino UNO``` を選択する。

9. Arduino IDEのメニューバーから ```ツール``` > ```シリアルポート``` > ```/dev/tty.usbmodem*``` あるいは ```/dev/cu.usbmodem*``` を選択する。

   ```/dev/tty.usbmodem``` もしくは ```/dev/cu.usbmodem``` からはじまる行を選択してください。末尾の文字は環境ごとに変化します。

10. Arduino IDEのメニューバーから ```ファイル``` > ```マイコンボードに書き込む``` を選択する。

   書き込みが完了した旨を伝えるメッセージが表示されれば書き込み完了。
