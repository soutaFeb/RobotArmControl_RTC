# シリアルリンクロボットアームを直感的に制御可能なRTC群
## 概要
## 特徴
- GUIでアームの状態を確認しつつ直感的に操作できる
- 横からの視点を追加できる
- 手先座標をキーボードから直接打ち込んで指定できる
- ファイルを読み込んで自動で動作させられる    

![GUIイメージ](https://user-images.githubusercontent.com/72483942/96357404-5f514580-1136-11eb-9993-f34a8be4a03e.PNG)
## 仕様
- 言語：C++
- OS：Windows10
## コンポーネント群
- RobotArmGUI：手先位置から関節角度計算,アームの状態を表示。DXライブラリを利用
- AccelerationControl：手先の移動速度を制御
- SerialOutAngle：マイコンに各関節角度を送信
- RobotArmCUI：キーボードで手先位置を指定
- RobotArmAutomaticController：ファイルを読み込んで自動で手先位置を指定

