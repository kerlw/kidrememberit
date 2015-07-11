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