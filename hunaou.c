#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* =========================
   胡闹大学 v1.1
   ========================= */

/* 玩家信息 */
char player_name[20];

/* 玩家属性 */
int mood;
int health;
int money;
int knowledge;

/* 行动次数 */
int study_count = 0;
int workout_count = 0;
int game_count = 0;
int fly_count = 0;
int work_count = 0;
int eat_count = 0;
int sleep_count = 0;
int outing_count = 0;


/* ---------- 函数声明 ---------- */

void choose_origin(void);
void show_status(void);
void show_menu(void);

void do_action(int choice);
void random_event(void);

void limit_status(void);

void show_changes(
    int old_mood,
    int old_health,
    int old_money,
    int old_knowledge
);

void check_game_over(void);

void show_ending(void);
void show_achievements(void);


/* =========================
   主程序
   ========================= */

int main(void)
{
    int day;
    int time_block;
    int choice;

    srand((unsigned int)time(NULL));

    printf("\n");
    printf("====================================\n");
    printf("             胡 闹 大 学\n");
    printf("              v1.1\n");
    printf("====================================\n");

    printf("\n请输入你的名字：");
    scanf("%19s", player_name);

    printf("\n欢迎来到胡闹大学，%s。\n", player_name);
    printf("你将在这里度过非常充实（大概）的七天。\n");

    choose_origin();

    /* 7天 */
    for (day = 1; day <= 7; day++)
    {
        printf("\n\n");
        printf("####################################\n");
        printf("              DAY %d / 7\n", day);
        printf("####################################\n");

        /* 每天5个时间块 */
        for (time_block = 1; time_block <= 5; time_block++)
        {
            printf("\n------------------------------------\n");
            printf("今天的第 %d / 5 个时间块\n", time_block);
            printf("------------------------------------\n");

            show_status();
            show_menu();

            printf("你决定：");
            scanf("%d", &choice);

            while (choice < 1 || choice > 8)
            {
                printf("没有这个选项。大学可以胡闹，菜单不能胡闹。\n");
                printf("请重新输入 1～8：");
                scanf("%d", &choice);
            }

            do_action(choice);

            limit_status();
            check_game_over();

            /*
               普通行动结束后
               25%概率发生额外随机事件。

               出门本身已经会触发随机事件，
               所以出门时不再额外触发一次。
            */
            if (choice != 8 && rand() % 100 < 25)
            {
                random_event();

                limit_status();
                check_game_over();
            }
        }

        printf("\nDAY %d 结束。\n", day);
        printf("你成功地又活过了一天。\n");
    }


    /* ---------- 七天结束 ---------- */

    printf("\n\n");
    printf("====================================\n");
    printf("            七 天 后 ……\n");
    printf("====================================\n");

    show_status();

    show_ending();

    show_achievements();

    printf("\n感谢游玩《胡闹大学》v1.1。\n");
    printf("你的大学生活暂时结束了。\n");
    printf("现实里的还没有。\n\n");

    return 0;
}


/* =========================
   选择出生
   ========================= */

void choose_origin(void)
{
    int choice;

    printf("\n");
    printf("========== 请选择你的出生 ==========\n");

    printf("\n");
    printf("1. 天龙人\n");
    printf("   一出生就站在别人毕业后的终点。\n");

    printf("\n");
    printf("2. 老鼠人\n");
    printf("   活着已经消耗了大部分力气。\n");

    printf("\n");
    printf("3. 平凡的一块石头\n");
    printf("   没什么特别，但至少还能滚。\n");

    printf("\n");
    printf("4. 管他呢随便吧\n");
    printf("   把命运交给随机数。\n");

    printf("\n请选择 1～4：");

    scanf("%d", &choice);

    while (choice < 1 || choice > 4)
    {
        printf("投胎失败，请重新投胎：");
        scanf("%d", &choice);
    }


    if (choice == 1)
    {
        mood = 100;
        health = 100;
        knowledge = 100;
        money = 30000;

        printf("\n【天龙人】\n");
        printf("很好。出生已经替你解决了大部分问题。\n");
    }

    else if (choice == 2)
    {
        mood = 20;
        health = 20;
        knowledge = 20;
        money = 2000;

        printf("\n【老鼠人】\n");
        printf("你的大学生活还没开始，看起来已经快结束了。\n");
    }

    else if (choice == 3)
    {
        mood = 50;
        health = 50;
        knowledge = 50;
        money = 8000;

        printf("\n【平凡的一块石头】\n");
        printf("普通得令人安心。\n");
    }

    else
    {
        mood = rand() % 81 + 20;
        health = rand() % 81 + 20;
        knowledge = rand() % 81 + 20;

        money = rand() % 19001 + 1000;

        printf("\n【管他呢随便吧】\n");
        printf("你盯着自己的属性看了一会儿。\n");
        printf("算了，投胎这种东西本来就不是你能控制的。\n");
    }

    show_status();
}


/* =========================
   显示状态
   ========================= */

void show_status(void)
{
    printf("\n========== 当前状态 ==========\n");

    printf("玩家：%s\n", player_name);

    printf("心情：%3d / 100\n", mood);
    printf("健康：%3d / 100\n", health);
    printf("学识：%3d / 100\n", knowledge);

    printf("金钱：%d 円\n", money);

    printf("==============================\n");
}


/* =========================
   菜单
   ========================= */

void show_menu(void)
{
    printf("\n今天干点什么？\n");

    printf("1. 上课\n");
    printf("2. 健身\n");
    printf("3. 宅家打游戏\n");
    printf("4. 起飞\n");
    printf("5. 打工\n");
    printf("6. 吃饭\n");
    printf("7. 睡觉\n");
    printf("8. 出门逛逛\n");

    printf("\n");
}


/* =========================
   执行动作
   ========================= */

void do_action(int choice)
{
    int event;

    /*
       先记住行动之前的状态。
       行动结束后就可以计算：
       新数值 - 旧数值
    */

    int old_mood = mood;
    int old_health = health;
    int old_money = money;
    int old_knowledge = knowledge;


    /* ---------- 上课 ---------- */

    if (choice == 1)
    {
        study_count++;

        printf("\n【上课】\n");

        event = rand() % 100;

        /* 20%概率迟到 */
        if (event < 20)
        {
            printf("你冲进车站。\n");
            printf("电车门在你面前缓缓关上。\n");
            printf("你和车里的乘客隔着玻璃深情对视。\n");

            printf("\n没挤上电车，迟到了！\n");
            printf("本次学习收益减半。\n");

            knowledge += 6;
            mood -= 4;
            health -= 2;
        }

        else
        {
            printf("你真的去上课了。\n");
            printf("教授甚至有点意外。\n");

            knowledge += 12;
            mood -= 3;
            health -= 2;
        }
    }


    /* ---------- 健身 ---------- */

    else if (choice == 2)
    {
        workout_count++;

        printf("\n【健身】\n");

        if (money >= 500)
        {
            printf("你去了健身房。\n");
            printf("镜子里的自己看起来突然很有希望。\n");

            money -= 500;
            health += 12;
            mood += 5;
        }

        else
        {
            printf("你摸了摸钱包。\n");
            printf("健身房今天与你无缘。\n");
            printf("于是你在宿舍做了20个深蹲。\n");

            health += 5;
            mood -= 2;
        }
    }


    /* ---------- 打游戏 ---------- */

    else if (choice == 3)
    {
        game_count++;

        printf("\n【宅家打游戏】\n");

        printf("“只玩一会儿。”\n");
        printf("几个小时过去了。\n");

        mood += 12;
        health -= 5;
        knowledge -= 2;
    }


    /* ---------- 起飞 ---------- */

    else if (choice == 4)
    {
        fly_count++;

        printf("\n【起飞】\n");

        printf("你决定暂时离开地球表面。\n");
        printf("具体怎么飞的不重要。\n");
        printf("重要的是你飞了。\n");

        mood += 8;
        health -= 4;
    }


    /* ---------- 打工 ---------- */

    else if (choice == 5)
    {
        work_count++;

        printf("\n【打工】\n");

        printf("你用宝贵的青春换来了工资。\n");
        printf("资本主义对你的表现表示满意。\n");

        money += 2500;
        mood -= 5;
        health -= 6;
    }


    /* ---------- 吃饭 ---------- */

    else if (choice == 6)
    {
        eat_count++;

        printf("\n【吃饭】\n");

        if (money >= 1000)
        {
            event = rand() % 100;

            /* 25%半价便当 */
            if (event < 25)
            {
                printf("你走进超市。\n");
                printf("远处的店员拿出了半价贴纸。\n");

                printf("\n贴！贴！贴！\n");

                printf("\n你抢到了半价便当！\n");
                printf("1000円 -> 500円\n");

                money -= 500;
                health += 10;
                mood += 8;
            }

            else
            {
                printf("你认真吃了一顿饭。\n");
                printf("原来人类吃饭之后真的会舒服一点。\n");

                money -= 1000;
                health += 10;
                mood += 3;
            }
        }

        else if (money >= 300)
        {
            printf("你看了一眼余额。\n");
            printf("今天只能吃便利店饭团了。\n");

            money -= 300;
            health += 4;
            mood -= 2;
        }

        else
        {
            printf("你打开钱包。\n");
            printf("钱包也看着你。\n");

            printf("\n你没钱吃饭。\n");

            health -= 8;
            mood -= 8;
        }
    }


    /* ---------- 睡觉 ---------- */

    else if (choice == 7)
    {
        sleep_count++;

        printf("\n【睡觉】\n");

        printf("你决定今天最大的成就就是闭上眼睛。\n");
        printf("这是一个非常成熟的决定。\n");

        health += 15;
        mood += 5;
    }


    /* ---------- 出门 ---------- */

    else if (choice == 8)
    {
        outing_count++;

        printf("\n【出门逛逛】\n");

        if (money >= 500)
        {
            money -= 500;
            mood += 6;

            printf("你离开了宿舍。\n");
            printf("光是看到外面的世界，心情就好了一点。\n");
        }

        else
        {
            printf("你没有500円。\n");
            printf("于是选择了免费的散步路线。\n");

            mood += 3;
            health += 2;
        }
    }


    /*
       显示这次行动造成的变化
    */

    show_changes(
        old_mood,
        old_health,
        old_money,
        old_knowledge
    );


    /*
       出门必定遇到一个随机事件
    */

    if (choice == 8)
    {
        random_event();
    }
}


/* =========================
   自动显示属性变化
   ========================= */

void show_changes(
    int old_mood,
    int old_health,
    int old_money,
    int old_knowledge
)
{
    int mood_change = mood - old_mood;
    int health_change = health - old_health;
    int money_change = money - old_money;
    int knowledge_change = knowledge - old_knowledge;

    printf("\n");
    printf("──── 本次变化 ────\n");


    /* 心情 */

    if (mood_change > 0)
        printf("心情   +%d\n", mood_change);

    else if (mood_change < 0)
        printf("心情   %d\n", mood_change);


    /* 健康 */

    if (health_change > 0)
        printf("健康   +%d\n", health_change);

    else if (health_change < 0)
        printf("健康   %d\n", health_change);


    /* 学识 */

    if (knowledge_change > 0)
        printf("学识   +%d\n", knowledge_change);

    else if (knowledge_change < 0)
        printf("学识   %d\n", knowledge_change);


    /* 金钱 */

    if (money_change > 0)
        printf("金钱   +%d円\n", money_change);

    else if (money_change < 0)
        printf("金钱   %d円\n", money_change);


    if (mood_change == 0 &&
        health_change == 0 &&
        money_change == 0 &&
        knowledge_change == 0)
    {
        printf("什么都没有发生。\n");
    }


    printf("─────────────────\n");
}


/* =========================
   随机事件
   ========================= */

void random_event(void)
{
    int event;

    int old_mood = mood;
    int old_health = health;
    int old_money = money;
    int old_knowledge = knowledge;

    event = rand() % 10;

    printf("\n");
    printf("********** 随机事件 **********\n");


    if (event == 0)
    {
        printf("【教授の慈悲】\n");

        printf("教授突然宣布提前下课。\n");
        printf("你一度怀疑自己听错了。\n");

        mood += 8;
        health += 3;
    }


    else if (event == 1)
    {
        printf("【Steam促销】\n");

        printf("你本来只想看一眼。\n");

        if (money >= 1800)
        {
            printf("三个小时后，你拥有了七款大概永远不会打开的游戏。\n");

            money -= 1800;
            mood += 15;
        }

        else
        {
            printf("余额救了你。\n");
            printf("你什么也买不起。\n");

            mood -= 2;
        }
    }


    else if (event == 2)
    {
        printf("【路边捡钱】\n");

        printf("你低头发现了1000円。\n");
        printf("你环顾四周。\n");
        printf("……\n");

        money += 1000;
        mood += 5;
    }


    else if (event == 3)
    {
        printf("【东京的雨】\n");

        printf("你没带伞。\n");
        printf("天气预报昨天确实说了会下雨。\n");
        printf("你没看。\n");

        health -= 5;
        mood -= 7;
    }


    else if (event == 4)
    {
        printf("【自动售货机的祝福】\n");

        printf("自动售货机掉下来两瓶饮料。\n");
        printf("你沉默了。\n");
        printf("自动售货机也沉默了。\n");

        mood += 15;
        health += 3;
    }


    else if (event == 5)
    {
        printf("【突然的小测验】\n");

        if (knowledge >= 60)
        {
            printf("你居然会做。\n");
            printf("这一刻，知识真的改变了命运。\n");

            mood += 8;
            knowledge += 3;
        }

        else
        {
            printf("试卷认识你。\n");
            printf("你不认识试卷。\n");

            mood -= 8;
        }
    }


    else if (event == 6)
    {
        printf("【朋友请客】\n");

        printf("朋友突然说：“今天我请。”\n");
        printf("你第一次如此深刻地理解了友情。\n");

        health += 8;
        mood += 10;
    }


    else if (event == 7)
    {
        printf("【睡过头】\n");

        printf("你睁开眼睛。\n");
        printf("手机上的时间让你重新闭上了眼睛。\n");

        mood -= 4;
        health += 3;
    }


    else if (event == 8)
    {
        printf("【迷之好运】\n");

        printf("今天什么都很顺。\n");
        printf("电车有座，天气舒服，便利店也不用排队。\n");

        mood += 12;
    }


    else
    {
        printf("【什么都没发生】\n");

        printf("今天居然非常普通。\n");
        printf("在胡闹大学，这本身就是一种异常。\n");

        mood += 2;
    }


    printf("******************************\n");


    /*
       显示随机事件造成的变化
    */

    show_changes(
        old_mood,
        old_health,
        old_money,
        old_knowledge
    );
}


/* =========================
   限制属性
   ========================= */

void limit_status(void)
{
    if (mood > 100)
        mood = 100;

    if (health > 100)
        health = 100;

    if (knowledge > 100)
        knowledge = 100;


    /*
       注意：
       这里不把0以下直接改成0。

       因为我们还需要让
       check_game_over()
       判断角色是否已经出事。

       但显示上负数没有意义，
       所以最低设置为0。
    */

    if (mood < 0)
        mood = 0;

    if (health < 0)
        health = 0;

    if (knowledge < 0)
        knowledge = 0;


    if (money < 0)
        money = 0;
}


/* =========================
   GAME OVER判断
   ========================= */

void check_game_over(void)
{
    /*
       健康优先判断。
       如果同一次事件让健康和心情
       同时归零，则进入健康结局。
    */

    if (health <= 0)
    {
        printf("\n\n");
        printf("====================================\n");
        printf("             GAME OVER\n");
        printf("====================================\n");

        printf("\n你的健康归零了。\n");
        printf("这次是真的撑不住了。\n");

        printf("\n最终结局：\n");
        printf("《我靠你不活了啊？》\n");

        printf("\n最终状态：\n");
        show_status();

        printf("\n你在胡闹大学留下了短暂而胡闹的一生。\n");
        printf("====================================\n");

        exit(0);
    }


    if (mood <= 0)
    {
        printf("\n\n");
        printf("====================================\n");
        printf("             GAME OVER\n");
        printf("====================================\n");

        printf("\n你的心情归零了。\n");
        printf("你彻底绷不住了，大学生活到此为止。\n");

        printf("\n最终结局：\n");
        printf("《电车延迟》\n");

        printf("\n最终状态：\n");
        show_status();

        printf("\n胡闹大学今日也在正常运行。\n");
        printf("====================================\n");

        exit(0);
    }
}


/* =========================
   七天后的结局
   ========================= */

void show_ending(void)
{
    printf("\n");
    printf("====================================\n");
    printf("              最终结局\n");
    printf("====================================\n");


    if (mood >= 85 &&
        health >= 85 &&
        knowledge >= 85 &&
        money >= 20000)
    {
        printf("\n《你是不是偷偷读档了？》\n\n");

        printf("学习、健康、快乐、金钱。\n");
        printf("别人说人生不能什么都要。\n");
        printf("你说：为什么不能？\n");
    }


    else if (mood <= 25 &&
             health <= 25 &&
             knowledge <= 25 &&
             money <= 3000)
    {
        printf("\n《胡闹大学》\n\n");

        printf("你回顾了自己的七天。\n");
        printf("……\n");
        printf("至少游戏标题出现了。\n");
    }


    else if (knowledge >= 90)
    {
        printf("\n《图书馆最终Boss》\n\n");

        printf("七天过去了。\n");
        printf("别人问你大学生活怎么样。\n");

        printf("你想了想：\n");
        printf("“大学……有生活吗？”\n");
    }


    else if (health >= 90)
    {
        printf("\n《这里是大学，不是健身房》\n\n");

        printf("教授已经不认识你了。\n");
        printf("健身房前台认识。\n");
    }


    else if (mood >= 90)
    {
        printf("\n《这辈子有了》\n\n");

        printf("绩点是什么？不知道。\n");
        printf("但是你真的很开心。\n");
    }


    else if (money >= 30000)
    {
        printf("\n《资本主义的走狗》\n\n");

        printf("同学还在赶作业。\n");
        printf("你正在研究下个月的排班表。\n");
    }


    else if (health <= 20)
    {
        printf("\n《活着就是胜利》\n\n");

        printf("七天结束了。\n");
        printf("你最大的成就是成功活到了结算画面。\n");
    }


    else if (money <= 500)
    {
        printf("\n《钱包比脸还干净》\n\n");

        printf("你打开钱包。\n");
        printf("里面的空气非常新鲜。\n");
    }


    else if (knowledge <= 20)
    {
        printf("\n《我真的是大学生吗？》\n\n");

        printf("学校认识你。\n");
        printf("教授不一定认识你。\n");
    }


    else
    {
        printf("\n《平凡的一块石头》\n\n");

        printf("你没有成为传奇。\n");
        printf("也没有彻底完蛋。\n");
        printf("七天以后，你还在继续滚。\n");
    }


    printf("\n====================================\n");
}


/* =========================
   成就
   ========================= */

void show_achievements(void)
{
    int achievement_count = 0;

    printf("\n");
    printf("====================================\n");
    printf("              成就结算\n");
    printf("====================================\n");


    /*
       这里按照你原来的要求：
       “超过10次”
       所以是 > 10，不是 >= 10。
    */

    if (fly_count > 10)
    {
        printf("★ 中国人能飞\n");
        printf("  起飞超过10次。\n\n");

        achievement_count++;
    }


    if (sleep_count > 10)
    {
        printf("★ 睡美人\n");
        printf("  睡觉超过10次。\n\n");

        achievement_count++;
    }


    /*
       “超过15次”
    */

    if (work_count > 15)
    {
        printf("★ 打工皇帝\n");
        printf("  打工超过15次。\n\n");

        achievement_count++;
    }


    if (knowledge >= 100)
    {
        printf("★ 学术妲己\n");
        printf("  学识达到100。\n\n");

        achievement_count++;
    }


    if (health >= 100)
    {
        printf("★ 人形自走蛋白粉\n");
        printf("  健康达到100。\n\n");

        achievement_count++;
    }


    if (mood >= 100)
    {
        printf("★ 活着就是为了开心\n");
        printf("  心情达到100。\n\n");

        achievement_count++;
    }


    if (money >= 30000)
    {
        printf("★ 钱不是万能的，但……\n");
        printf("  持有30000円以上。\n\n");

        achievement_count++;
    }


    if (outing_count >= 8)
    {
        printf("★ 出门是会有好事的\n");
        printf("  出门达到8次。\n\n");

        achievement_count++;
    }


    if (game_count >= 10)
    {
        printf("★ Steam大学荣誉毕业生\n");
        printf("  打游戏达到10次。\n\n");

        achievement_count++;
    }


    if (study_count == 0)
    {
        printf("★ 今天也没见到教授\n");
        printf("  七天一次课都没有上。\n\n");

        achievement_count++;
    }


    if (study_count > 0 &&
        workout_count > 0 &&
        game_count > 0 &&
        fly_count > 0 &&
        work_count > 0 &&
        eat_count > 0 &&
        sleep_count > 0 &&
        outing_count > 0)
    {
        printf("★ 真・大学生\n");
        printf("  八种行动全部体验过。\n\n");

        achievement_count++;
    }


    if (achievement_count == 0)
    {
        printf("没有解锁任何成就。\n");
        printf("这本身似乎也是一种成就。\n");
    }


    printf("------------------------------------\n");

    printf("本周行动统计：\n");

    printf("上课：%d 次\n", study_count);
    printf("健身：%d 次\n", workout_count);
    printf("游戏：%d 次\n", game_count);
    printf("起飞：%d 次\n", fly_count);
    printf("打工：%d 次\n", work_count);
    printf("吃饭：%d 次\n", eat_count);
    printf("睡觉：%d 次\n", sleep_count);
    printf("出门：%d 次\n", outing_count);

    printf("\n共解锁 %d 个成就。\n", achievement_count);

    printf("====================================\n");
}
