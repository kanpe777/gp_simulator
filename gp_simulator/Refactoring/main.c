#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <time.h>
#include "BmG.h"

/*#---------< Main >---------#
 *---< 引数 >
 * 第一：maxステージ数
 * 第二：初期母集団の数
 * 第三：世代数
 * 第四：途中スタート(YES:1,NO:0)
 *
 *---< 全体像 >
 * (1),初期母集団の生成(戦略木の生成)
 * (2),各戦略木をSimulatorに渡し、適応度(得点)をつける
 * (3),適応度順にソート(クイック)
 * (4),選択(エリート選択)
 * (5),交叉
 * (6),突然変異
 * (7),(2)へ
 */

int main(int argc,char *argv[])
{
    if (argc != 5)
    {
        fprintf(stderr,"Arg_ERROR\n第一引数：maxステージ数\n第二引数：初期母集団の数\n第三引数：世代数\n第四引数:途中スタート(YES:1,NO:0)\n");
        exit(1);
    }

    srandom((unsigned)time(NULL));

    //int i,j;//できるだけiやjなど意味のない変数を減らしたい
    int stage_id_max = atoi(argv[1]);
    int stage_id;

    int tree_max = atoi(argv[2]);
    int tree_id;

    int generation_max = atoi(argv[3]);
    int generation_id;

    //途中スタート(セーブ機能)は未実装

    int generate_rank_top[generation_max];

    /*--------< パラメータ >--------*/
    /* 選択率     (全体ｎの下位〇〇%が自然淘汰、上位〇〇%をコピー)
     * 交叉率     (全体の〇〇%を交叉)
     * 突然変異率 (1個体は〇〇%の確率で突然変異を起こす)
     */
    int choice_percentage  = 20;
    int cross_percentage   = 10;
    int mutate_probability = 1;


    /*--------< 初期母集団生成 >-----*/
    /* タグ-戦略木
     * タグには得点と、戦略木のノード数が記録されている。
     */
    int node_num;
    int tree_depth;
    tag_t *tree_tag_array;
    tree_tag_array = (tag_t*)calloc(tree_max,sizeof(tag_t));
    for (tree_id = 0;tree_id < tree_max;tree_id++)
    {
        node_num = 0;
        tree_depth = 0;
        tree_tag_array[tree_id].p_node_top = (node_t*)calloc(1,sizeof(node_t));
        //tree_tag_array[tree_id].i_node_num = createTree(tree_tag_array[tree_id].p_node_top,node_num,tree_depth);
    }

    

    for (generation_id = 0;generation_id < jeneration_max;generation_id++)
    {
        if (initscr() == NULL)
        {
            for (tree_id = 0;tree_id < tree_max;tree_id++)
            {
                //freeTreeNode(tree_tag_array[tree_id].p_node_top);
            }
            free(tree_tag_array);
            fprintf(stderr,"init screen ERROR\n");
            exit(-1);
        }


        for (stage_id = 1;stage_id <= stage_id_max;stage_id++)
        {
            for (tree_id = 0;tree_id < tree_max;tree_id++)
            {
                tree_tag_array[tree_id].i_point += getPoint(stage_id,tree_tag_array[tree_id].p_node_top);
                clear();
                refresh();
            }
        }

        endwin();
    
        /*-----------< ソート >----------*/
        //高い順 = 降順
        //rankQuicksort(tree_tag_array,tree_max);

        generate_rank_top[generation_id] = tree_tag_array[0].i_point;


        /*-----------< 選択 >-----------------*/
        double choice_num = (double)tree_max * (0.01 * (double)choice_percentage);
        //choice(tree_tag_array,tree_max,(int)choice_num);




        /*-----------< 交叉 >-----------------*/
        double cross_num = (double)tree_max * (0.01 * (double)cross_percentage)
        //cross(tree_tag_array,tree_max,(int)cross_num);





        /*-----------< 突然変異 >-------------*/
        for (tree_id = 0;tree_id < tree_max;tree_id++)
        {
            if (mutate_probability > (random() % 100))
            {
                mutate(tree_tag_array,tree_id);
            }
        }

        //一度、ノードの数を数え直す
        for (tree_id = 0;tree_id < tree_max;tree_id++)
        {
            node_num = 0;
            //tree_tag_array[tree_id].i_node_num = countNode(tree_tag_array[tree_id],node_num);
        }
    }

    /*-------< 戦略木をすべて削除 >----------*/
    for (tree_id = 0;tree_id < tree_max;tree_id++)
    {
        //freeTreeNode(tree_tag_array[tree_id].p_node_top);
    }
    free(tree_tag_array);





    FILE *fp;
    if ((fp = fopen("change_graph.txt","w")) == NULL)
    {
        fprintf(stderr,"failed file open\n");
        exit(EXIT_FAILURE);
    }
    
    for (generation_id = 0;generation_id < generation_max;generation_id++)
    {
        fprintf(fp,"%d %d\n",generation_id,generate_rank_top[generation_id]);
    }


    fclose(fp);


    printf("最後まで\n");
    return 0;
}
