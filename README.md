# OfflineJudge

## 前言

當初我同學有在架設我們學校的線上評測系統，而一開始我們的系統非常不穩定，因此，他想到可以寫離線的程式答題系統緩解我們上課的需求。而我看到這個系統，我覺得這是一個不錯的想法，並依此加以改良，新增 TLE 判定和超時時會強制停止。

## 使用(解題者)

一題會是一個資料夾，裡面會有隱藏檔案和非隱藏檔案。

| 檔案名稱 | 大致內容 | 是否隱藏 |
| --- | --- | --- |
| AC | ascii art 的 AC 字樣 | True |
| WA | ascii art 的 WA 字樣 | True |
| TLE | ascii art 的 TLE 字樣 | True |
| main.h | 主要程式 | 不用附給使用者 |
| Run.cpp | 執行程式 | 不用附給使用者 |
| Run.exe | 執行程式 | False |
| Solve.cpp | 使用者的程式 | False |
| Description | 題目敘述 | False |
| README.md | 說明使用方法(如下) | False |

### README.txt 內文

#### 以下說明檔案功能及用法

1. 編譯並執行 Run.cpp 可以獲得評測結果
2. 程式碼請寫在 Solve.cpp 裡面
3. 題目敘述在 Description 裡面，一般應該是 .txt，.md 或 .pdf
4. 標準輸入輸出用 cin 和 cout 就可以了

#### 以下說明答題結果

1. AC 作答正確
2. WA 輸出結果錯誤，或不符合題目要求
3. TLE 執行時間過長
4. 程式跳掉 一般來說都是 RE(runtime error)

#### 以下規定請勿違反

1. 擅自更改除 Solve 以外的檔案

#### 貼心小提醒

由於 Solve 函式會被重複使用，因此變數就算開在全域也要記得初始化(現版本已經不需要)

### 截圖

![AC](https://live.staticflickr.com/65535/52131824719_f3ef187894_o.png)

## 使用(出題者)

資料夾中還含有一個隱藏資料夾 TestCase，裡面存放有測試資料。裡面的檔案如下

| 檔案名稱 | 大致內容 |
| --- | --- |
| Gen.cpp | 預設的測試資料生成程式 |
| GraphGen.h | 圖論測資生成程式 ( [使用介紹](https://mtmatt.page/misc/the-test-case-builder-of-graph-theory/) ) |
| Sol.cpp | 官解檔 |
| log.txt | 測試資料們的基本資料 |

### Gen.cpp

介紹各個函式的功能

| 函式 | 功能 |
| --- | --- |
| RandomNumber(long long a,long long b) | 生成一個隨機數 ( 範圍\[a,b\] ) |
| RandomNumber(long long n) | 生成一個隨機數 ( 範圍\[1,n\] ) |
| solve() | 共用解答函式(會調用Sol.cpp) |
| SubTesk1(int a) | 生成第 a 筆測資 |

如果覺得 RandomNumber 太長，GraphGen.h 裡面有相同功能的函式 Rand

### log.txt

只有三行，第一行是測試資料數目，第二行是執行時間限制，以毫秒為單位，第三行是題目ID。

```
TestCases:     5
TimeLimit(ms): 50
ProblemID: Default
```

## 主程式

| 函式 | 功能 |
| --- | --- |
| RunCode(int timeLimit) | 執行使用者程式(會計算時間，盡量減少多餘程式碼) |
| RunTestCase(int testCase,int timeLimit) | 完成執行第 testCase 筆測試資料所需的前置條件 |
| Judge(int testCase) | 評判解答正確性 |
| RunSolution() | 執行所有測試並輸出結果 |
| Encode() | AC時回傳密碼(預設的加密演算法安全性很低，需要修改) |

## 競賽中不會出現的 C++ 功能

多執行續 thread 函式庫

```cpp
// 開新的執行續處理函式 RunCode
thread run{RunCode,timeLimit};
// 讓此執行續等待一段時間 chrono 格式
this_thread::sleep_for(chrono::milliseconds(timeLimit+20))
// 放空該執行續(與物件 run 取消綁定，但會繼續執行)
run.detach();
// 合併執行續，意味著它會等待到 run 那個執行序完成(return)後再合併
run.join();
```

## 其它題目

可以去雲端硬碟下載。這裡有一些題目。[Mega](https://mega.nz/folder/HgdU3J4A#NjDnWXqIS6Ov_hDGnrbtkA)
