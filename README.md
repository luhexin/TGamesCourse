# TGamesCourse
官网https://gameinstitute.qq.com/open-courses-2023/program

---
## 《UE入门》作业
1. 源码编译UE4/5，新建一个C++工程，进行简单场景编辑和工程设置
2. 编译并构建安装包，确保能够用来将游戏工程安装到手机正常运行

## 《UMG界面》作业
为目前的Demo添加类似下面的游戏界面:包含角色的个人信息，基础操作按钮，计分显示。可选:添加一个得分排行榜，排行数据可使用
SaveGame保存于本地，得分进入榜单时可编辑自己在榜单上显示的昵称

--- 

> UE版本: 4.27  
> 
> 角色模型与动画资源: 
> 1. 虚幻商城: "Paragon: Gideon"
> 2. Mixamo: Derrick  
## UI方面
- 运行时UI
    - 包括角色信息，红条(血量)、蓝条(技能)、白条(技能剩余时间)
    - 正上方是当前生存时间，右上方是额外分数(当炮台攻击到敌人时，增加数值)
![UI](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/runtimeUI.png)
- 排行榜UI
    - 按住Rank按钮显示排行榜，松开Rank按钮排行榜隐藏
    - 红色字体为当前分数(实时更新名次与分数)
    - 白色字体为历史分数(游戏结束时，会将当前游戏信息写入到本地SaveGame中，更新历史名次)
![UI](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/RankUI.png)
- 结算UI
    - 比较当前分数与历史最佳分数
    - 打破(或平)历史最佳分数，会显示新纪录(或平记录)
    - 其他情况会显示当前分数以及历史最佳分数
![UI](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/OverUI.png)

## 玩家角色方面
- 实现了基本的移动、跳跃、镜头转动、基础攻击、普通技能，瞬移技能、物品交互等功能
- `基础攻击`演示  
![动态图](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/PrimaryAttack.gif)
- 攻击到敌人会令敌人停止动作5s  
![动态图](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/AttackZom.gif)
- `普通技能`: 消耗20点蓝条，使炮台子弹以及敌人动作停止5s，左上方白条同步倒计时  
![动态图](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/Canon.gif)  
- `瞬移技能`: 前方投掷一个粒子，当粒子接触到地面或墙体时会爆炸，人物传送到爆炸点
![动态图](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/Dash.gif)


## 敌人方面
- 使用行为树和EQS实现了追击玩家以及随机巡逻。
    - 没有发现玩家时，会在附近的点随机巡逻
    - 发现玩家时，会追击玩家   

![动态图](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/FollowRoam.gif)  
- 进入敌人的攻击范围, 敌人攻击单次造成10点伤害   
![攻击玩家](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/zomAttack.gif)  


## 其他
- 爆炸桶
    - 受到攻击时，会向周围施加一定的力，在一定范围内玩家和敌人均会因受力而后退
![爆炸桶](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/Explode.gif)
- 宝箱
    - 在范围内按下交互键(Interact), 开启宝箱
    - 宝箱开启恢复20点蓝量
![爆炸桶](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/Treasure.gif)
- 炮台
    - 当玩家进入炮台一定范围时，炮台将发射子弹，对玩家造成10点伤害
    - 碰到敌人，玩家获得额外分数(Extra Score)
![动态图](https://github.com/luhexin/TGamesCourse/blob/main/ReadmeAsset/gif/Canon.gif)
