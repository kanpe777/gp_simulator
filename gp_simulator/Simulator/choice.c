#include <stdio.h>
#include "BmG.h"
/* cross.c
 * 引数は、tag_treeのみ
 * 交叉方法はあとで相談する
 * デフォルトで考えているのが、ランキング方式
 */


void choice(tag_t *tree_tag_array,int tree_max,int choice_percentage)
{
    //コピー元の配列IDを1つ指定、自然淘汰されるやつを選択、とりあえず、テスト用は完全ランダム
    int base_id;
    int destination_id;
    int i;
    int j;//確認用
    int node_count;
    int copy_node_num;


    if (tree_max == 1)
    {
        printf("戦略木を2本以上にしてください。\n");
        return;
    }

    //while (base_id == destination_id)
    //{
    //printf("コピー元とコピー先が一緒です -> ワンモアチョイス\n");
    //    destination_id = random() % tree_max;
    //}

    for(i = 0;i < choice_percentage;i++)
    {
        base_id = i;
        destination_id = tree_max - i - 1;
        /////////////////////////////////////////////////////////
        //printf("\n\nBefore\n");
        //node_count = 0;
        //node_count = look_tree(tree_tag_array[i].p_strTOP,node_count);
        //printf("計nodeの数は %d 個\n",node_count);
        //printf("\n\n");



        //コピー用にとりあえず、配列をコピー元のノードの数だけ用意
        node_t *copy_base_array;
        copy_node_num = tree_tag_array[base_id].inodeNUM;
        copy_base_array = (node_t*)calloc(copy_node_num,sizeof(node_t));

        //配列にそれぞれ記録、しかし、木ではないことに注意
        //引数の0は配列の添字となる
        //int check_node_num;
        //printf("コピーです\n");
        node_count = copy_tree(tree_tag_array[base_id].p_strTOP,copy_base_array,0);
        //printf("計nodeの数は %d 個\n",node_count); 

        /*int j;
          for(j = 0;j < node_count;j++)
          {
          if (copy_base_array[j].bEND)
          {
          printf("ACTION\n");
          }
          else
          {
          printf("途中\n");
          }
          printf("iSENSOR = %d\niACTION = %d\n",copy_base_array[j].iSENSOR,copy_base_array[j].iACTION);
          }
         */






        //printf("check_node_num = %d\n",check_node_num);
        /*
           printf("#----------------------------------------------------------------------------< copy >\n");
           for(j = 0;j < copy_node_num;j++)
           {
           if(copy_base_array[j].bEND)
           {
           printf("copyTRUE ,iACTION = %d番\n",copy_base_array[j].iACTION);
           }
           else
           {
           printf("copyFALSE ,iSENSOR = %d番\n",copy_base_array[j].iSENSOR);
           }
           }
         */

        free_strNODE(tree_tag_array[destination_id].p_strTOP);
        tree_tag_array[destination_id].p_strTOP = (node_t*)calloc(1,sizeof(node_t));
        //tree_tag_array[destination_id].inodeNUM = tree_create(tree_tag_array[destination_id].p_strTOP,0,0); 

        //printf("#--------------------------------------< paste >\n");
        //printf("ペーストです\n");
        tree_tag_array[destination_id].inodeNUM = paste_tree(tree_tag_array[destination_id].p_strTOP, copy_base_array, 0);
        //printf("計nodeの数は %d 個\n",node_count);
        //printf("\n\n");
        free(copy_base_array);
    }
    return;
}


