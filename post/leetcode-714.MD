+++
title = "leetcode: Question 714"
summary = ["Best Time to Buy and Sell Stock with Transaction Fee"]
tags = [
    "leetcode",
    "DP",
    "algorithm"
]
categories=[]
date = "2017-10-22"
+++

# 714. Best Time to Buy and Sell Stock with Transaction Fee

## 题目

Your are given an array of integers prices, for which the i-th element is the price of a given stock on day i; and a non-negative integer fee representing a transaction fee.

You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction. You may not buy more than 1 share of a stock at a time (ie. you must sell the stock share before you buy again.)

Return the maximum profit you can make.

*Example 1:*

```
Input: prices = [1, 3, 2, 8, 4, 9], fee = 2
Output: 8
Explanation: The maximum profit can be achieved by:
Buying at prices[0] = 1
Selling at prices[3] = 8
Buying at prices[4] = 4
Selling at prices[5] = 9
The total profit is ((8 - 1) - 2) + ((9 - 4) - 2) = 8.
```

## 传统动态规划

这是我第一个版本的答案，方法是对的，可惜需要n^2的时间复杂度，在leetcode上提交直接超时了。

具体思路就是：profit[i]这个状态的值由 (profit[0],... profit[i-1]) 到profit[i]的状态转变的最大值决定,即：
```
profit[i]= max{profit[0]+max{0, prices[i]-prices[0]}, ..., profit[i-1]+max{0, prices[i]-prices[i-1]}}
```
代码如下所示：
```java
public static int maxProfit(int[] prices, int fee) {
    int profit[] = new int[prices.length];
    for(int i=1; i<profit.length; i++){
        for(int j=0; j<i; j++){
            int tmp = prices[i]-prices[j]-fee>0?prices[i]-prices[j]-fee:0;
            if(profit[j]+tmp>profit[i]){
                profit[i]=profit[j]+tmp;
            }
        }
    }
    return profit[profit.length-1];
}
```

## 状态机

这个方法是看了[leetcode-309](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/description/)的状态机解法之后受到的启发。

通过分析，我们可以发现总共有三个状态：已买入（S0），已卖出（S1）和空闲（S2）。已买入状态的入度为：由已买入状态自我维持，或由已卖出状态转入，或有空闲状态转入。已卖出状态只有由已买入状态转入，因为有买才有卖。空闲状态可以由已卖出状态转入，或由空闲状态自我维持。开始状态，即对应第一个price，可以是空闲状态或已买入状态。所以状态转移图为：

买入时profit会降低相应的price，而卖出则会赚到相应的差价，所以状态转移函数为：
```
s0[i] = max(s0[i-1], s2[i-1]-prices[i]);
s0[i] = max(s0[i], s1[i-1]-prices[i]);
s1[i] = s0[i-1] + prices[i] - fee;
s2[i] = max(s1[i-1], s2[i-1]);
```

所以代码就如下所示了：
```java
public static int maxProfit(int[] prices, int fee) {
    int s0[] = new int[prices.length];
    int s1[] = new int[prices.length];
    int s2[] = new int[prices.length];
    s0[0] = -prices[0];
    s1[0] = -fee;
    s2[0] = 0;
    for(int i=1; i<prices.length; i++){
        s0[i] = Math.max(s0[i-1], s2[i-1]-prices[i]);
        s0[i] = Math.max(s0[i], s1[i-1]-prices[i]);
        s1[i] = s0[i-1] + prices[i] - fee;
        s2[i] = Math.max(s1[i-1], s2[i-1]);
    }
    return Math.max(s2[prices.length-1], s1[prices.length-1]);
    }
```