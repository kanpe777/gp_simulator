#include <stdio.h>
#include <stdlib.h>
#include "BmG.h"



void cross(tag_t *tree_tag_array,int tree_max,int cross_num)
{   
    //int cross_num = 3;
    //int tree_max = 6;
    int i,j;
    int cross_target[cross_num * 2];
    //printf("交差する奴らは合計%d個\n",cross_num*2);


        //srandom((unsigned)time(NULL));
        for(i = 0;i < (cross_num * 2);i++)
        {
            cross_target[i] = random() % tree_max;
            j = 0;
            while(j < i)
            {
                if(cross_target[j] == cross_target[i])
                {
                    j = 0;
                    cross_target[i] = random() % tree_max;
                }
                else
                {
                    j++;
                }
            }
            //printf("交叉対象は戦略木No.%d\n",cross_target[i]);//確認用
        }



    int id_A;
    int id_B;
    int targetA_node_num;
    int targetB_node_num;
    target_t *target_A;
    target_t *target_B;
    target_A = (target_t*)calloc(1,sizeof(target_t));
    target_B = (target_t*)calloc(1,sizeof(target_t));
    //target_A->p_target = (node_t*)calloc(sizeof(node_t));
    //target_B->p_target = (node_t*)calloc(sizeof(node_t));

    for (i = 0;i < cross_num;i++)
    {
        id_A = cross_target[i];
        id_B = cross_target[i + cross_num];
        targetA_node_num = (random() % tree_tag_array[id_A].inodeNUM) + 1;
        targetB_node_num = (random() % tree_tag_array[id_B].inodeNUM) + 1;
        //printf("Aの交換するNODEは%d番目\n",targetA_node_num);//確認用
        //printf("Bの交換するNODEは%d番目\n",targetB_node_num);//確認用

        target_A->p_target = NULL;
        target_B->p_target = NULL;

        //交叉NODEを探索
        get_p_target(tree_tag_array[id_A].p_strTOP,target_A,targetA_node_num,0);
        get_p_target(tree_tag_array[id_B].p_strTOP,target_B,targetB_node_num,0);

        //printf("ターゲットA_NODEのポインタは %p\n",target_A->p_target);//確認用
        //printf("ターゲットB_NODEのポインタは %p\n",target_B->p_target);//確認用

        //Let's交叉
        if(targetA_node_num == 1)
        {
            tree_tag_array[id_A].p_strTOP = target_B->p_target;
        }
        else
        {
            get_p_target(tree_tag_array[id_A].p_strTOP,target_B,targetA_node_num,1);
        }

        if(targetB_node_num == 1)
        {
            tree_tag_array[id_B].p_strTOP = target_A->p_target;
        }
        else
        {
            get_p_target(tree_tag_array[id_B].p_strTOP,target_A,targetB_node_num,1);
        }
    }

    //free(target_A->p_target);
    //free(target_B->p_target);
    free(target_A);
    free(target_B);

    /*
       for(i = 0;i < (cross_num * 2);i++)
       {
       printf("cross_target[%d] = %d\n",i,cross_target[i]);
       }*/




    //return 0;
    return;
}

