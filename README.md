# Kid Remember It 
Trying to practise kid's memory.

## RoadMap
Step 1:

* show some cards to kids for a short time, then hide these cards, let the kids try to select out the correct card from a card list in the correct order.
* number of cards, length of card showing time, time length for permutation is the 3 factors of difficulty.
* each puzzle should be generated randomly, and there should be an algorithm to calculate the difficulty factor according to kids answer, make it step by step.

Step 2:

* the classic memory game: show cards to kids with the back side, trying to clear these card by flipping tow same cards.
* number of cards, time length for flipping is 2 factors of difficulty  


## Ideas

1. Initialize with a 'step 1' game, X cards, Y seconds to remember (player could choose start to skip waiting period) and Z seconds to select and place cards in order.
+ According to player's score in the first game, calculate the difficulty factor that the next game should be created with.
+ If player get very high score, that means the difficulty of current game is too low for him(her), so we could increase the difficulty factor more levels.
+ The final goal is to create games that kids need to try his/her best to solve it, nor he/she would be failed.

## Time factor
1. Player has 5 seconds for each card in remember period
2. Player has 5 seconds for each card in represent period
3. Guessing player should use 2.5 seconds for each card in remember period on average.
4. Guessing player should use 2 second for each card in represent period on average.

===============

OK

Let's redesign the difficulty & score system for the step 1.

At first, we need to point out all difficulty factors as below:

1. type of cards to be used [2,9] -> 8 levels
+ number of cards to be used [5, 14] -> 10 levels
+ sequence of cards (ignore this factor, it's too complex for me to model it :P)
+ duration period for remember [2,5]s/card -> 4 levels
+ duration period for represent [2,5]s/card -> 4 levels

And second, we need to make some rules to set / change these factors:

1.  type of cards must NOT be less than 1/3 of number of cards. 
+ if the count of type of cards become the same with the number of cards or reached the max number of types, increase the number of cards
+ after increase number of cards, set the type of cards to the min number that could be used

At last, we use the easiest way to calculate the score used to judge whether player should go forward to the next level or back to the previous level:

1. Finished correctly in time, go forward, otherwise go back.
+ TODO make it more complex ~pula pula pula~~


#孩子，记住它
锻炼孩子的记忆力

## 规划
一阶段：

* 显示一些卡片一段时间，然后隐藏，让孩子尝试从一个序列中按顺序选出正确的卡片。
* 卡片的数量、显示卡片的时间长短、选择排列卡片的时间长短作为难度因子
* 每个关卡都随机生成，作出算法来根据孩子作答的情况计算难度因子，让难度逐步升级

阶段二

* 经典的记忆游戏：显示一组背面朝上的卡片，翻转出相同的两张方可消除一对卡片
* 卡片的数量、翻卡片的时间长短是2个难度因子

## 随想
1. 初始化一局游戏，有X张卡片，Y秒用于记忆(孩子可以选择掠过记忆的等待时间）以及Z秒用于恢复正确的排列
2. 根据孩子的表现来计算游戏的困难系数
3. 如果孩子表现非常出色，说明当前的难度远低于他（她）的能力，可以适当跨级调高难度
4. 最终目的是要创建出让孩子不尽最大努力无法通过的游戏

## 时间因子
1. 玩家在记忆阶段拥有 5秒/每张卡片
+ 玩家在重现阶段拥有 5秒/每张卡片
+ 猜测玩家在记忆阶段的平均水平应该在2.5秒/每张卡片
+ 猜测玩家在重现阶段的平均水平应该在2秒/每张卡片

===============

好吧，让我们来重新设计阶段一的 难度&积分 系统吧

首先，我们需要列举出所有的难度因子：

1. 使用的卡片的种类 [2, 9] -> 8阶
+ 使用的卡片的数量 [5, 14] -> 10阶
+ 卡片出现的顺序（暂时忽略这个因子，用这个因子建模对我来说太复杂了 :P）
+ 用于记忆的时间 [2, 5]s/卡片 -> 4阶
+ 用于重现的时间 [2, 5]s/卡片 -> 4阶

然后我们制定一些规则来设置/改变这些因子：

1. 卡片的种类不少于卡片数量的1/3
2. 卡片种类和卡片数量持平或卡片种类达到种类最大数值后，增加难度则增加卡片数量
3. 增加卡片数量后，卡片种类恢复到增加数量后可使用的最低种类数

最后，我们使用最简单的规则来确定分数决定玩家晋级或降级

1. 规定时间内成功完成，晋级，否则降级。
+ TODO 制定更复杂的分数计算和升降规则 ～普啦普啦普啦～～

