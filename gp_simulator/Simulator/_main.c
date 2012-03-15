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
    if(argc != 5)
    {
        fprintf(stderr,"Arg_ERROR\n第一引数：maxステージ数\n第二引数：初期母集団の数\n第三引数：世代数\n第四引数:途中スタート(YES:1,NO:0)\n");
        exit(1);
    }

    //int i,j;//できるだけiやjなど意味のない変数を減らしたい
    int stage_id_max = atoi(argv[1]);
    int stage_id;

    int tree_max = atoi(argv[2]);
    int tree_id;

    int generation_max = atoi(argv[3]);
    int generation_id;

    //未実装->途中スタート

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
    tag_t *tree_tag_array;
    tree_tag_array = (tag_t*)calloc(tree_max,sizeof(tag_t));
    for(tree_id = 0;tree_id < tree_max;tree_id++)
    {
        tree_tag_array[tree_id].strTOP = NULL; 
    }

    



    return 0;
}
