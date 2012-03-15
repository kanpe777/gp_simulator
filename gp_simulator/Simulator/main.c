#include <stdio.h>
#include <stdlib.h>//randam()やstderr
#include <curses.h>//cursesにより、シミュレーターが成立
#include <time.h>//time関数を使うため
#include "BmG.h"//自作ヘッダファイル

/*#-----< Main >-------#
 * (1),引数の数をチェックをする(引数はステージID)
 * (2),戦略木の頂点だけはMainでやる
 *     戦略木にもIDと得点用の構造体(タグ)を付与する  タグ-(戦略木頂点)
 * (3),戦略木をSimulatorに渡す(戻り値は点数)
 * (4),タグを見て、ランキングを作成
 * (5),交叉をする(全体の10%)
 * (6),突然変異をするか?(1%)
 * (7),(3)へ
 **/
int main(int argc,char *argv[])
{   
    int i,j;
    if(argc != 6)
    {
        fprintf(stderr,"Arg_ERROR \n第一引数：maxステージID\n第二引数：Manualモード:\"1\"  Autoモード:\"2\" \n第三引数：戦略木の数 第四引数：世代数\n");
        exit(1);
    }

    int stageID_max = atoi(argv[1]);
    int stageID;
    int auto_or_manual = atoi(argv[2]);
    int tree_max = atoi(argv[3]);
    int generation_max = atoi(argv[4]);
    int on_off = atoi(argv[5]);
    
    int generate_rank_top[generation_max];
    

    /*------------< パラメータ >-----------------*/
    /* 選択率
     * 交叉率
     * 突然変異率
     */
    int choice_percentage = 20;   //全体の下位〇〇%を自然淘汰し、上位〇〇%をコピー
    int cross_num_percentage = 10;//全体の〇〇%を交叉
    int mutate_probability = 2;   //1個体は〇〇%の確率で突然変異



    /*---------< 初期母集団生成 >---------*/
    /* タグ-戦略木
     * タグには得点と、戦略木のノードの数が記録されている。
     */
    tag_t *tree_tag_array;
    tree_tag_array = (tag_t*)calloc(tree_max,sizeof(tag_t));
    for(i = 0;i < tree_max;i++)
    {
        //tree_tag_array[i] = (tag_t *)calloc(1,sizeof(tag_t));
        tree_tag_array[i].p_strTOP = NULL;
    }
















    srandom((unsigned)time(NULL));
    int node_count = 0;
    int node_depth = 0;
    for(i = 0;i < tree_max;i++)
    {
        //printf("===============================戦略木No.%d\n",i);
        tree_tag_array[i].p_strTOP = (node_t *)calloc(1,sizeof(node_t));
        tree_tag_array[i].inodeNUM = tree_create(tree_tag_array[i].p_strTOP,node_count,node_depth);
        //printf("tree_tag_array[%d].inodeNUM = %d\n",i,tree_tag_array[i].inodeNUM);
    }



















    /*-------------------------------------------------------------------------------------------------------------------------------*/
    for(i = 0;i < generation_max;i++)
    {
        //printf("Simulate します\n");//確認用
        /*--------------------------------------< 適応度計算 >--------------------*/
        /* 点数を返す。
         */
        if(initscr() == NULL)
        {   
            for(j = 0;j < tree_max;j++)
            {
                free_strNODE(tree_tag_array[j].p_strTOP);
                free(tree_tag_array);
            }
            fprintf(stderr,"init screen ERROR\n");
            exit(-1);
        }


        for(j = 0;j < tree_max;j++)
        {
            tree_tag_array[j].iPOINT = 0;
            //for(stageID = 1;stageID <= 1;stageID ++)
            for(stageID = 1; stageID <= stageID_max; stageID++)
            {
                tree_tag_array[j].iPOINT += simulate(stageID,tree_tag_array[j].p_strTOP,auto_or_manual,on_off);
                clear();
                refresh();
                //上3行は本番で必要
                //tree_tag_array[j].iPOINT = random() % 100 + 1;//simulateが完成したら不要
            }
        }
        if(endwin() == ERR)
        {
            fprintf(stderr,"end window ERROR\n");
            exit(-1);
        }




        /*--------< ソート >-------*/
        //得点順に並べる(高い方から)
        rank_quicksort(tree_tag_array,0,tree_max-1);
        generate_rank_top[i] = tree_tag_array[0].iPOINT;
        //for(j = 0; j < tree_max; j++)
        //{
        //      generate_rank[j][i] = tree_tag_array[j].iPOINT;
        //    printf("%d位 : %d点\n", j+1, tree_tag_array[j].iPOINT);
        //}
        //printf("\n");













        /*----------------------------------------------< 選択 >-------------*/
        int choice_num = tree_max / 10;
        choice_num *= (choice_percentage / 10);
        choice(tree_tag_array,tree_max,choice_num);


           /* 
           printf("\n\nBefore\n");
           for(j = 0;j < tree_max;j++)
           {
           node_count = 0;
           node_count = look_tree(tree_tag_array[j].p_strTOP,node_count);
           printf("計nodeの数は %d 個\n",node_count);
           }
           printf("\n\n");*/
         












        /*-------------< 交叉 >-----------------*/
        double cross_num = tree_max / 100;
        //printf("bcross_num = %f\n",cross_num);
        cross_num *= (cross_num_percentage / 2);
        //printf("across_num = %f\n",cross_num);
        //int cross_num = tree_max / 2;//確認用
        cross(tree_tag_array,tree_max,(int)cross_num);















        /*------------< 突然変異 >-------------*/
        /* 非終端 -> 終端
         * 非終端 -> 非終端
         * 終端   -> 終端
         * 終端   -> 非終端
         * 非終端の場合になった際に、その深さは指定できない。
         */
        for(j = 0;j < tree_max;j++)
        {
            if (mutate_probability > (random() % 100))
            {
                mutate(tree_tag_array,tree_max,j);
            }
        }
        /*
           printf("\n\nAfter\n");
           for(j = 0;j < tree_max;j++)
           {
           node_count = 0;
           node_count = look_tree(tree_tag_array[j].p_strTOP,node_count);
           printf("計nodeの数は %d 個\n",node_count);
           }
        */














        //一度node数を数え直す必要あり
        for(j = 0;j < tree_max;j++)
        {    
            //printf("\n今から見るぜtree_tag_array[%d] 番目\n",j);
            node_count = 0;
            tree_tag_array[j].inodeNUM = look_tree(tree_tag_array[j].p_strTOP,node_count);
            //usleep(100000);
        }



    }//適応度計算->交叉->突然変異
    /*----------------------------------------------------------------------------------------------------------------------*/
















    /*--------< 戦略木をすべて削除 >---------*/    
    //全てのノードをFREE
    for(j = 0;j < tree_max;j++)
    {
        free_strNODE(tree_tag_array[j].p_strTOP);
    }
    free(tree_tag_array);
















    FILE *fp;
    if((fp = fopen("change_graph.txt","w")) == NULL)
    {
        printf("ファイル開けるの失敗\n");
        exit(EXIT_FAILURE);
    }
        for(j = 0;j < generation_max;j++)
        {
            //printf("%d位%d点  ",j+1,generate_rank[j][i]);
            printf("%d %d\n",j,generate_rank_top[j]);
            fprintf(fp,"%d %d\n",j,generate_rank_top[j]);
        }

    fclose(fp);














    //printf("最後まで来ました\n");//確認用

    return 0;
}
