# 程設專題
## Project 1 Maximal Points Problem
### 題目內容

在一個空間中有 p 和 q 兩個點，當 p.x >= q.x、p.y >= q.y 以及 p.z >= q.z 成立時稱為 p dominates q。
當一個在點集合 S 中的 p 點不被任何其他屬於 S 的點 dominates 時，該 p 點就被稱作為一個 maximal point。

目標：將所有屬於 S 的 maximal points 找出來。
 

### 實作方法

（一） 暴力求解

從第 1 個點到第 n 個點，每個點都跟自己以外的所有點比較，若沒有任何一個點 dominate 它，即為 maximal point。
優化：一旦遇到 dominate 它的點，即可保證它非 maximal point，因此可直接跳出迴圈並記錄此點，不再比較。

（二） 分治

首先將所有的點依照 x 優先、y 次之、z 最後的優先順序做降序排列。之後將排序後的集合從中間切半，分成大小相等的兩個部分，令 a 為 x 值較大的一半，b 則為較小的一半。這時候可以保證 a 集合中點的 x 值必定大於等於 b 中的點，此時將 a 與 b 中的點做比較，便可忽略 x 值，將其降為僅考慮 y 和 z 的二維 maximal point 問題。

## Project 2 Making Binary Search Dynamic
### 題目內容

![](https://i.imgur.com/Ya32hq6.png)
 
### 實作方法

（一）	架構
根據題目，建立k個陣列（A0, A1, …, Ak-1）並將n個數字放入其中，第i個陣列Ai的長度為2i，且所有陣列只會有全滿與全空兩個狀態。
因陣列長度不一，故選擇vector作為容器；另外，由於後續還會插入未知數量的數字，因此最初宣告的陣列數會大於k。

（二）	Search

基本上使用基礎的binary search方法實作，設定左右邊界並逐次砍半，直至找到目標數字。惟因此架構不只一陣列，須依序搜尋所有不為空的陣列。

（三）	Insert

首先須用Search確定所有陣列中皆無要插入的數字。
建立一個暫存陣列，將要插入的數字放入。判斷A0狀態，若A0為空，則將暫存陣列的內容移至A0；否則將暫存陣列與A0合併，判斷A1狀態。若A1仍不為空，則將合併後的暫存陣列與A1合併，判斷A2狀態，以此類推。

（四）	Delete

首先須用Search找出要刪除的數字位置。
最初並不將數字直接刪除，而是執行軟刪除——將欲刪除的數字標記為不可用，但仍保留數字。直到單個陣列Ai中欲刪除的數字達到陣列長度的一半，再一次處理陣列中所有數字。處理方式為：若前一陣列Ai-1為空，將Ai中剩餘數字移入前一陣列；若非，則將前一陣列與剩餘數字合併，放入原陣列Ai。

（五）	紅黑樹
使用C++函式庫中的set來實作，其特性為：
* Set中的元素皆已排序
* Set中沒有重複的原素
* 底層結構為紅黑樹

可使用count()、insert()、erase()來完成搜尋、插入與刪除的動作。


## Project 3 The Candyman Can Do More!
### 題目內容

It’s the first of October, the day Willy Wonka opens the doors to his famous Chocolate Factory for the five lucky kids that hold one of the golden tickets: Charlie, Augustus, Mike, Veruca and Violet. The tour guided by Willy Wonka begins, and after Augustus falls into the river of chocolate and Violet turns into a blueberry (but don’t worry, they are going to be safe and healthy at the end), there are three of the children left.

What a shock! To calm down the remaining three children, Willy Wonka wants to give some candies to them. He has a couple of candies that are of different weight and wants to divide them evenly between the children, so that they don’t get jealous at each other.

He wants to know how bad the fairest distribution is, i.e. what is the minimum difference in the candies weight, of the kid getting the candies of the most total weight and the kid getting the least. For example, assume that he gives the three children candies of weight a, b and c, respectively. The badness of this distribution is the difference between the maximum of a, b, c and the minimum of a, b, c. Unfortunately, Willy Wonka is not very good in mathematics, so he needs your help. 

**Input**

The first line of input contains a single integer (less than 130) indicating the number of testcases that follow.
Each testcase consists of two lines. The first line contains a number n (0< n ≤ 200), the number of candies to be distributed.
The second line contains n numbers A1, A2, . . ., An(0< Ai ≤ 100 for all i = 1. . . n), the weight of the different candies.

**Output**

For each testcase, output a single line which contains the case number (as shown in the sample output)
and then the smallest badness that can be achieved when distributing all candies to the children.
There is only a single space between the colon and the smallest badness. 

### 實作方法
（一）	標準 DP

建立布林陣列dp[i][j]，代表第一個人拿總重為i、第二個人拿總重為j、第三個人拿總重為所有糖果重（sum）-i-j的情況是否可行。
遍歷每顆糖果，dp[i][j]依照i、j從sum到0的順序遍歷。若dp[i][j]可行，則dp[i+糖果重][j]及dp[i][j+糖果重]也會可行。
填完表格後，只要找出其中拿最多與拿最少的最小重量差即為答案。


（二）	位元運算

與標準DP的邏輯相同，惟dp[i][j]改為使用bitset做位元運算，可加快運算速度。

（三）	Top-Down

1.	想法1：使用遞迴方法，以三維陣列記錄最小重量差並回推，然數字過大以致三維陣列無法建立。
2.	想法2：反向從可能的結果來填表格，從估計最小重量差為0的可能性考慮至總和（即最大可能重量差），並考慮所有可能的組合，若組合可行且最小重量差正確，則為答案。

## Project 4 Sabotage with Chaos
### 題目內容
The regime of a small but wealthy dictatorship has been abruptly overthrown by an unexpected rebellion. Because of the enormous disturbances this is causing in world economy, an imperialist military super power has decided to invade the country and reinstall the old regime.

For this operation to be successful, communication between the capital and the largest city must be completely cut. This is a difficult task, since all cities in the country are connected by a computer network using the Internet Protocol, which allows messages to take any path through the network. Because of this, the network must be completely split in two parts, with the capital in one part and the largest city in the other, and with no connections between the parts.

There are large differences in the costs of sabotaging different connections, since some are much more easy to get to than others.
Write a program that, given a network specification and the costs of sabotaging each connection, determines which connections to cut in order to separate the capital and the largest city to the lowest possible cost.

### 實作方法
（一）	Flow
    
Max-Flow Min-Cut

（二）	Randomized

根據Karger’s algorithm，每次隨機將兩個點合併，只要不將1和2併為同一點即可。合併至最後只剩下兩個點，剩餘的邊即為其中一種割法。重複以上步驟並記錄切割方法中代價最小的一種，只要重複次數夠多便能找到真正的最小割。

在實作上，我使用並查集來記錄合併點的集合，並且一次處理一條邊而非一個點，這樣的作法在處理邊時會遇到三種情況：

1. 兩端點為可合併且未合併的兩點 > 合併
2. 兩端點為可合併且已合併的兩點 > 忽略
3. 兩端點為不可合併的兩點 > 為需切割的邊 > 記錄

在記錄割邊的同時處理邊權重的和，若此割法的權重和小於目前的最小割，則將其換為新的割法。

