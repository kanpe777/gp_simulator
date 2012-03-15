/*
 *   * -< simulate.c >-*
 *
 * Ground()      -地上へ(END判定も行う)
 * Control()     -動きの制御
 *  |-moveRoL()  -左右どちらか
 *  |-moveJump() -ジャンプ
 *
 * 環境
 * Gravity     -重力
 * Intertia    -慣性(右=正、左=負)
 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "BmG.h"




void Refresh(Agent_status *agent)
{
    if(agent->ON_OFF == 0)
    {
        refresh();
        usleep(50000);
    }else{
        refresh();
        usleep(1);
    }
}

//エージェント出力
void printBoy(Agent_status *agent,int stgnum)
{
    if (agent->ON_OFF == 0)
    {
        clear();
        stage(stgnum);
        //        mvaddch(agent->Y-2,agent->X,'B');
        //        mvaddch(agent->Y-1,agent->X,'O');
        mvaddch(agent->Y,  agent->X,'B');
    }
    else 
    {
        clear();
        stage(stgnum);
    }
}


//慣性によって動く方向が変わる
//Moving Right or Left
int moveRoL(Agent_status *agent){
    int i;
    for(i=0;i<=abs(agent->INTERTIA);i++){
        if(agent->INTERTIA > 0){//右へ
            //            if(mvinch(agent->Y,agent->X+1) != 'I')
                if((mvinch(agent->Y,agent->X+1) != 'I') && ( mvinch(agent->Y,agent->X+1) != '*'))
                {
                agent->X += 1;
            }

        }else if(agent->INTERTIA < 0){//左へ
            //            if(mvinch(agent->Y,agent->X-1) != 'I')
                if((mvinch(agent->Y,agent->X-1) != 'I') && (mvinch(agent->Y,agent->X-1) != '*'))
            {
                agent->X -= 1;
            }
        }
    }
    return 0;
}


void Action(int stgnum,Agent_status *agent,node_t *trees,int auto_or_mamual,Girl *Girl_status)
{
    int action_num_ch;
    int action_ch = 0;
    if(auto_or_mamual == 1)
    {
        //            action_ch = getch();
        switch(action_ch) 
        {
            case 'h'://左
                if (agent->INTERTIA > -2)
                {
                    agent->INTERTIA -= 1;//慣性 
                }
                moveRoL(agent);
                break;
            case 'l'://右
                if (agent->INTERTIA < 2)
                {
                    agent->INTERTIA += 1;//慣性
                }
                moveRoL(agent);
                break;
            case 'k'://ジャンプ
                if (mvinch(agent->Y+1,agent->X) == 'I' )
                {
                    Jump(stgnum,agent,trees,auto_or_mamual,Girl_status);
                }
                break;
            case 0:
                agent->INTERTIA = 0;//何も押さないと慣性は消える
                break;
        }
    }
    else if (auto_or_mamual == 2)
    {

        Refresh(agent);

        action_num_ch = getAction(agent,trees);

        switch(action_num_ch)
        {
            case 0:
                action_ch = 'h';
                break;
            case 1:
                action_ch = 'k';
                break;
            case 2:
                action_ch = 'l';
                break;
            case 3:
                action_ch = 'j';
                break;
            case 4:
                action_ch = 'g';
                break;

        }

        switch(action_ch) 
        {
            case 'h'://左
                if (agent->INTERTIA > -2)
                {
                    agent->INTERTIA -= 1;//慣性 
                }
                moveRoL(agent);
                break;
            case 'l'://右
                if (agent->INTERTIA < 2)
                {
                    agent->INTERTIA += 1;//慣性
                }
                moveRoL(agent);
                break;

            case 'k'://ジャンプ
                if (mvinch(agent->Y+1,agent->X) == 'I')
                {
                    Jump(stgnum,agent,trees,auto_or_mamual,Girl_status);
                }
                break;
            case 'j':
                if (mvinch(agent->Y+1,agent->X) == 'I')
                {
                    Jump(stgnum,agent,trees,auto_or_mamual,Girl_status);
                }
                if (agent->INTERTIA < 1)
                {
                    agent->INTERTIA += 1;//慣性
                }
                moveRoL(agent);
                if (mvinch(agent->Y+1,agent->X) == 'I')
                {
                    Jump(stgnum,agent,trees,auto_or_mamual,Girl_status);
                }
                break;
            case 'g':
                if (mvinch(agent->Y+1,agent->X) == 'I')
                {
                    Jump(stgnum,agent,trees,auto_or_mamual,Girl_status);
                }
                if (agent->INTERTIA > -1)
                {
                    agent->INTERTIA -= 1;//慣性 
                }
                moveRoL(agent);
                if (mvinch(agent->Y+1,agent->X) == 'I')
                {
                    Jump(stgnum,agent,trees,auto_or_mamual,Girl_status);
                }
            default:
                agent->INTERTIA = 0;//何も押さないと慣性は消える
                break;
        }

    }
}


//GOODEND or BADEND
void END(int end,int stgnum,node_t *trees,int auto_or_mamual,Agent_status *agent)
{
    int total_points = agent->X;
    if (end == 0)
    {
        if (agent->X < 0)
        {
            total_points = 0;
            agent->X = 0;
        }
        if (agent->ENEMY_TOUCH_FLAG == 1)
        {
            total_points -= 50;
        }
        if (total_points < 0)
        {
            total_points = 0;
        }
        //BadEND
        if (agent->ON_OFF == 0){

            mvprintw(LINES/2+1,COLS/2-10,"(>_<;)  (>_< )");
            mvprintw(LINES/2,COLS/2-4,"GAME OVER");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            Refresh(agent);

            mvprintw(LINES/2+1,COLS/2-12,"(>_<;))    (>_< ) ");
            mvprintw(LINES/2,COLS/2-4,"GAME OVER");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            Refresh(agent);

            mvprintw(LINES/2+1,COLS/2-14,"(>_<;))))       (T-T ) ");
            mvprintw(LINES/2,COLS/2-4,"GAME OVER");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            Refresh(agent);

            mvprintw(LINES/2+1,COLS/2-16,"(>_<;)))))sorry          (T-T )");
            mvprintw(LINES/2,COLS/2-4,"GAME OVER");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            mvprintw(LINES/4,COLS/2-20,"%d DISTANCE = TOTAL %d POINTS!!!",agent->X,total_points);
            Refresh(agent);

        }
        //agent->END_FLAG = 1;
        agent->TOTAL_POINTS = total_points;


    }
    else
    {

        //GoodEND
        if(agent->ON_OFF == 0)
        {
            clear();
            mvprintw(LINES/2+1,COLS/2-8,"(*´<)          (>'*)");
            mvprintw(LINES/2,COLS/2-4,"GOOD END");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            Refresh(agent);

            clear();
            mvprintw(LINES/2+1,COLS/2-7,"(*´<)       (>'*)");
            mvprintw(LINES/2,COLS/2-4,"GOOD END");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            Refresh(agent);

            clear();
            mvprintw(LINES/2+1,COLS/2-6,"(*´<)    (>'*)");
            mvprintw(LINES/2,COLS/2-4,"GOOD END");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            Refresh(agent);

            clear();
            mvprintw(LINES/2+1,COLS/2-5,"(*´з)(ε'*)chu!!");
            mvprintw(LINES/2,COLS/2-4,"GOOD END");
            mvaddstr(LINES/2-3,COLS/2-10,"retry or quit [r/q] ?");
            curs_set(0);
            Refresh(agent);
        }


        total_points += agent->TIMES;
        mvprintw(LINES/4,COLS/2-30,"%d TIMES + %d DISTANCE = TOTAL %d POINTS!!!",agent->TIMES,agent->X,total_points);
        curs_set(0);
        Refresh(agent);

    }//Dead or Goal

    agent->END_FLAG = 1;
    agent->TOTAL_POINTS = total_points;

}


void END_Check(int stgnum, Agent_status *agent, node_t *trees, int auto_or_mamual,Girl *Girl_status)
{
    if(mvinch(agent->Y,agent->X+1) == '*' || 
       mvinch(agent->Y,agent->X-1) == '*' ||
       mvinch(agent->Y+1,agent->X) == '*' ||
       ((mvinch(agent->Y-1,agent->X) == '*') &&( agent->Jumpflag == 1)))
    {
        agent->ENEMY_TOUCH_FLAG = 1;//あとで直す
        END(0,stgnum,trees,auto_or_mamual,agent);
    }
    else if((agent->X >= Girl_status->X))
    {
        END(1,stgnum,trees,auto_or_mamual,agent);
    }
    else if(agent->TIMES <= 0 )
    {
        END(0,stgnum,trees,auto_or_mamual,agent);
    }

}






//空気抵抗
int resistance(Agent_status *agent){
    if(agent->INTERTIA > 0){
        agent->INTERTIA -= 1;
    }else if(agent->INTERTIA < 0){
        agent->INTERTIA += 1;
    }
    return 0;
}










int Jump(int stgnum,Agent_status *agent, node_t *trees,int auto_or_mamual,Girl *Girl_status)
{
    //慣性を監視
    //    mvprintw(0,0,"intertia = %d",agent->INTERTIA);

    int highest = 5;

    for(;highest > 0;highest--)
    {
        if(mvinch(agent->Y-3,agent->X) != 'I')
        {
            agent->Y -= 1;
            agent->Jumpflag = 1;
        }
        moveRoL(agent);
        control(stgnum,agent,trees,auto_or_mamual,Girl_status);
        //            usleep(50000);
    }
    return 0;
}













//control_actionに変更
int control(int stgnum,Agent_status *agent,node_t *trees,int auto_or_mamual,Girl *Girl_status){

    //慣性を監視
    //    mvprintw(0,0,"intertia = %d",agent->INTERTIA);
    //    if(agent->END_FLAG == 0)
    //    {

        //    }else{
        //        return 0;
        //    }
    if(agent->END_FLAG == 0)
    {
        timelimit(stgnum,trees,auto_or_mamual,agent);
        Action(stgnum,agent,trees,auto_or_mamual,Girl_status);

        if(agent->ON_OFF == 0)
        {
            printBoy(agent,stgnum);
        }
     
        END_Check(stgnum,agent,trees,auto_or_mamual,Girl_status);
    }

    return 0;
}



//センサーA_左上
int sensor_A(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y-1,strAGENT->X-1) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーB_真上
int sensor_B(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y-1,strAGENT->X) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーC_右上
int sensor_C(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y-1,strAGENT->X+1) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーD_左
int sensor_D(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y,strAGENT->X-1) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーE_右
int sensor_E(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y,strAGENT->X+1) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーF_左下
int sensor_F(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y+1,strAGENT->X-1) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーG_真下
int sensor_G(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y+1,strAGENT->X) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーH_右下
int sensor_H(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y+1,strAGENT->X+1) != ' ') 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//センサーI_ジャンプ中か
int sensor_I(Agent_status *strAGENT)
{
    return strAGENT->Jumpflag;
}

//センサーJ_時間が半分以上か
int sensor_J(Agent_status *strAGENT)
{
    int flag = 0;
    if(strAGENT->TIMES >= 50) 
    {
        flag = 1;
    }
    else
    {
        flag = 0;
    }

    return flag;
}

//右3マスに敵がいるかどうか。
int sensor_K(Agent_status *strAGENT)
{
    int flag = 0;
    if(mvinch(strAGENT->Y,strAGENT->X+1) == '*' ||
       mvinch(strAGENT->Y,strAGENT->X+2) == '*' ||
       mvinch(strAGENT->Y,strAGENT->X+3) == '*')
    {
        flag = 1;
    }
    return 0;
}

//----------------------------------------------------------------------------------------------by カンペー
int getAction (Agent_status *strAGENT,node_t *strNODE)
{
    if (!(strNODE->bEND))
    {
        switch (strNODE->iSENSOR)
        {
            case 0:
                if(sensor_A(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD); 
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 1:
                if(sensor_B(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD); 
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 2:
                if(sensor_C(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);                  
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 3:
                if(sensor_D(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 4:
                if(sensor_E(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD); 
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 5:
                if(sensor_F(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);                   
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 6:
                if(sensor_G(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);                   
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 7:
                if(sensor_H(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);                   
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 8:
                if(sensor_I(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);                   
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);                   
                }
                break;
            case 9:
                if(sensor_J(strAGENT) == 1)
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);                   
                }
                else
                {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);
                }
                break;
        case 10:
            if(sensor_K(strAGENT) == 1)
            {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strRIGHT_CHILD);                
            }
            else
            {
                    strNODE->iACTION = getAction(strAGENT,strNODE->p_strLEFT_CHILD);
            }
            default:
                //nop
                break;
        }//switchセンサー


    }
    else
    {
        return strNODE->iACTION;
    }
}
/*
//戦略木のノードをたどる。
int getAction(Agent_status *agent, node_t *strNODE){
int sensor_ch;
if(!(strNODE->bEND))
{
sensor_ch = strNODE->iSENSOR;
switch(sensor_ch)
{
case 0:
if(mvinch(agent->X+1,agent->Y) != ' ')
{
strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}
else
{
strNODE->iACTION = getAction(agent,strNODE->p_strLEFT_CHILD);
}
break;
case 1:
if(mvinch(agent->X+2,agent->Y) != ' ')
{
strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}
else
{
strNODE->iACTION = getAction(agent,strNODE->p_strLEFT_CHILD);
}
break;
case 2:
if(mvinch(agent->X+3,agent->Y) != ' ')
{
strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}
else
{
strNODE->iACTION = getAction(agent,strNODE->p_strLEFT_CHILD);
}

break;
case 3:
if(mvinch(agent->X+1,agent->Y+1) != ' ')
{
strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}
else
{
strNODE->iACTION = getAction(agent,strNODE->p_strLEFT_CHILD);
}
break;
case 4:
if(mvinch(agent->X+2,agent->Y+1) != ' ')
{
strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}
else
{
strNODE->iACTION = getAction(agent,strNODE->p_strLEFT_CHILD);
}

break;
case 5:
if(mvinch(agent->X+3,agent->Y+1) != ' ')
{
strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}
else
{
strNODE->iACTION = getAction(agent,strNODE->p_strLEFT_CHILD);
}

break;
case 6:
if(mvinch(agent->X,agent->Y+1) != ' ')
{
    strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}
else
{
    strNODE->iACTION = getAction(agent,strNODE->p_strRIGHT_CHILD);
}

break;
default:
//nop
break;
}

}
return strNODE->iACTION;
}


*/











//重力
int Gravity(int stgnum,Agent_status *agent, node_t *trees,int auto_or_mamual,Girl *Girl_status){

    //慣性を監視
    //    mvprintw(0,0,"intertia = %d",agent->INTERTIA);
    if (agent->END_FLAG != 1)
    {    
        if (agent->X >= Girl_status->X)
        {
            END(1,stgnum,trees,auto_or_mamual,agent);
            return 0;
        }
        else if (agent->Y > Girl_status->Y+8)
        {
            END(0,stgnum,trees,auto_or_mamual,agent);
            return 0;
        }


        printBoy(agent,stgnum);

        if(mvinch(agent->Y+1,agent->X) != 'I')
        {
            agent->Y += 1;
            control(stgnum,agent,trees,auto_or_mamual,Girl_status);
            //            usleep(80000);
            moveRoL(agent);
            Gravity(stgnum,agent,trees,auto_or_mamual,Girl_status);
        }
    }
    return 0;
}

















int Ground(int stgnum, Agent_status *agent, node_t *trees,int auto_or_mamual,Girl *Girl_status){
    int count = 0;
    if(agent->END_FLAG == 0)
    {
        Gravity(stgnum,agent,trees,auto_or_mamual,Girl_status);
        agent->Jumpflag = 0;
        control(stgnum,agent,trees,auto_or_mamual,Girl_status);

        if(count > 10)
            {
                resistance(agent);
                count = 0;
            }
        count++;

        /*
          if((agent->X >= Girl_status->X))
          {
          END(1,stgnum,trees,auto_or_mamual,agent);
          return 0;
          }
        */


        //    if (agent->END_FLAG != 1)
        //    {
        //            usleep(20000);
        Ground(stgnum,agent,trees,auto_or_mamual,Girl_status);
        //    }
    }
    return 0;
}







//時間測定
int timelimit(int stgnum, node_t *trees,int auto_or_mamual,Agent_status *agent){
    //時間切れ判定
    //    if(agent->TIMES >= 0){
        mvprintw(0,COLS/2,"time %d",agent->TIMES);
        agent->TIMES--;
        //    }else{
        //        END(0,stgnum,trees,auto_or_mamual,agent);
        //    }
    return 0;
}










void Girl_search(Girl *Girl_status)
{
    int i=0,j=0;
    while(1)
    {
        if(mvinch(i,0)=='I')
        {
            Girl_status->Y = i-1;
            break;
        }
        i++;
    }

    while(1)
    {
        if(mvinch(Girl_status->Y,j)=='L')
        {
            Girl_status->X = j;
            break;
        }
        j++;
    }
}



int place_start_boy()
{
    int height = 0;
    while(mvinch(height,0) != 'I')
    {
        height++;
    }

    return (height - 2);
}




int simulate(int stgnum,node_t *trees,int auto_or_mamual,int on_off){

    int points;
    curs_set(0);//おまじない?
    timeout(0);//getchをリアルタイムにする
    noecho();//echo off,音
    cbreak();//カノニカルモード

    stage(stgnum);

    Agent_status *agent;
    agent = (Agent_status *)malloc(sizeof(Agent_status));

    agent->TIMES=100;

    agent->X = 1;
    agent->Y = place_start_boy();
    agent->Y = 35;
    agent->Jumpflag = 0;
    agent->INTERTIA = 0;
    agent->TIMES = 100;
    agent->END_FLAG = 0;
    agent->ENEMY_TOUCH_FLAG = 0;
    agent->ON_OFF = on_off;

    printBoy(agent,stgnum);


    Girl *Girl_status;
    Girl_status = (Girl *)malloc(sizeof(Girl));

    Girl_search(Girl_status);

    Ground(stgnum,agent,trees,auto_or_mamual,Girl_status);
    points = agent->TOTAL_POINTS;

    free(agent);
    free(Girl_status);

    return points;
}


