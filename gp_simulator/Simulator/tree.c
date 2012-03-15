#include <stdio.h>//printfとか
//#include <stdbool.h>//bool型を使うため
#include <stdlib.h>//まぁ色々(randomやfprintf)
//#include <time.h>//time関数を使うため
#include "BmG.h"

/*#-----< 戦略木を生成 >-----#
 * 実際にノードをつなげながら構造木を生成する
 * 木の深さ0,1,2,3,...で50%,40%,30%,...,0%の確率で子NODEを作る
 * 再起を利用して、左NODEから作っていく
 * 子を作るときのみ、CHILD分の構造体をcallocする
 * 子を作らない時のみ、iACTIONを設定
 */
/*----追加_1/16
 * 本番用は、treeを作るだけで返す値はなくてよい
 * 引数は、ノードの構造体のポインタ
 *         ノードの深さ
 */
/*----追加_2/9
 * やはり、nodeの数を返すようにした。
 * nodeの数は交叉の際に使用する。
 *引数に nodeの数を追加
 */
int tree_create(node_t *strNODE,int node_count,int node_depth)
    //void tree_create(node_t *strNODE,int node_depth)
{
    int child_percentage = 50 - (node_depth * 10);
    node_depth++;
    node_count++;
    //printf("node %d 個目\n",node_count);
    if ((random()%100+1) <= child_percentage)
    {   
        //printf("作るよ!!\n");//確認用
        strNODE->p_strLEFT_CHILD = (void*)calloc(1,sizeof(node_t));
        //strNODE->p_strLEFT_CHILD->p_strLEFT_CHILD = NULL;
        //strNODE->p_strLEFT_CHILD->p_strRIGHT_CHILD = NULL;

        strNODE->p_strRIGHT_CHILD = (void*)calloc(1,sizeof(node_t));
        //printf("右 %p\n左 %p\n",strNODE->p_strRIGHT_CHILD,strNODE->p_strLEFT_CHILD);//tes確認用

        strNODE->bEND = false; 
        strNODE->iSENSOR = random() % 10;
        //printf("左! %d番目\n",node_count);//確認用
        node_count = tree_create((node_t*)strNODE->p_strLEFT_CHILD,node_count,node_depth);       
        //tree_create((node_t*)strNODE->p_strLEFT_CHILD,node_depth);
        //printf("右! %d番目\n",node_count);//確認用
        node_count = tree_create((node_t*)strNODE->p_strRIGHT_CHILD,node_count,node_depth);
        //tree_create((node_t*)strNODE->p_strRIGHT_CHILD,node_depth);
    }
    else
    {
        strNODE->bEND = true;
        //strNODE->iACTION = random() % 5;
        strNODE->iACTION = random() % 5;
        //printf("ACTION!! %d\n",strNODE->iACTION);//確認用
    }

    return node_count;
    //return;
}






/*#-------------< 戦略木をFREE(メモリ解放) >--------------------#
 * 木構造をどんどん再帰で潜っていき、終端にきたらfreeする
 * 非終端NODEは左,右NODE_CHILDをそれぞれfreeしてから、自分自身をfreeする
 * 
 */
/*----追加_1/16
 * 本番用は、freeするだけでよいので、返す値はなくてよい
 * 引数は、ノードの構造体のポインタ
 */
//int free_strNODE(node_t *strNODE,int node_count){
void free_strNODE(node_t *strNODE)
{
    if (!(strNODE->bEND))
    {   //printf("潜る\n");//確認用
        //printf("左に潜るよ! %d番目\n",node_count);//確認用
        //node_count = free_strNODE(strNODE->p_strLEFT_CHILD,node_count+1);
        free_strNODE((node_t*)strNODE->p_strLEFT_CHILD);
        //printf("右に潜るよ! %d番目\n",node_count);//確認用
        //node_count = free_strNODE(strNODE->p_strRIGHT_CHILD,node_count+1);
        free_strNODE((node_t*)strNODE->p_strRIGHT_CHILD);
        //printf("子NODEのFREEは終了、自分自身をFREE\n");

        free(strNODE);
    }
    else
    {   //printf("free\n");//確認用
        //printf("終端NODE、発見!!Let's FREE!! %d番目\n",node_count);//確認用
        free(strNODE);
    }
    //return node_count;
    return;
} 


/*#-----------------------< 戦略木をコピー >--------------------#
 * 
 */
int copy_tree(node_t *strNODE,node_t *copy_base_array,int base_array_id)
{
    copy_base_array[base_array_id].bEND = strNODE->bEND;
    copy_base_array[base_array_id].iACTION = strNODE->iACTION;
    copy_base_array[base_array_id].iSENSOR = strNODE->iSENSOR;

    base_array_id++;

    if (!(strNODE->bEND))
    {   
        //printf("copy左%d番目\n",base_array_id);
        base_array_id = copy_tree((node_t*)strNODE->p_strLEFT_CHILD,copy_base_array,base_array_id);

        //printf("copy右%d番目\n",base_array_id);
        base_array_id = copy_tree((node_t*)strNODE->p_strRIGHT_CHILD,copy_base_array,base_array_id);
    }
    else
    { 
        //printf("ACTION %d\n",strNODE->iACTION);
    }
    /*else
      {
      copy_base_array->iACTION = strNODE->iACTION;
      copy_base_array->iSENSOR = strNODE->iSENSOR;
      }*/

    return base_array_id;
}








int paste_tree(node_t *strNODE,node_t *copy_base_array,int base_array_id)
{
    strNODE->bEND = copy_base_array[base_array_id].bEND;
    strNODE->iACTION = copy_base_array[base_array_id].iACTION;
    strNODE->iSENSOR = copy_base_array[base_array_id].iSENSOR;

    base_array_id++;
    //if (copy_base_array[base_array_id].bEND)
    if (strNODE->bEND)
    {//確認用
        //printf("pasteTRUE , iACTION %d\n",strNODE->iACTION);
    }
    else
    {
        //printf("pasteFALSE ,iSENSOR %d\n",strNODE->iSENSOR);
        /*    
              if(strNODE->bEND)
              {
              printf("ありえない\n");
              }
              else if (!(strNODE->bEND))
              {
              printf("正しい\n");
              }*/


        strNODE->p_strLEFT_CHILD = (void*)calloc(1,sizeof(node_t));
        strNODE->p_strRIGHT_CHILD = (void*)calloc(1,sizeof(node_t));

        
        //printf("左%d番目\n",base_array_id);
        base_array_id = paste_tree((node_t*)strNODE->p_strLEFT_CHILD,copy_base_array,base_array_id);       

        //printf("右%d番目\n",base_array_id); 
        base_array_id = paste_tree((node_t*)strNODE->p_strRIGHT_CHILD,copy_base_array,base_array_id);
    }
    /*else
      {
      printf("切れていい\n");
      }*/

    /*
       if (!(strNODE->bEND))
    //if (!(copy_base_array[base_array_id].bEND))
    {

    }
     */
    return base_array_id;
}



/*#----------------<  交叉するnodeを見つける >-----------------#
 * target_node_numをデクリメントしていき、
 * == 0 となったstrNODEが交叉するべきstrNODEとなる
 */
int get_p_target(node_t *strNODE,target_t *targetNODE,int target_node_num,int flag)
{
    target_node_num--;
    if ((target_node_num == 0) && (flag == 0))
    {
        targetNODE->p_target = strNODE;
        //printf("ターゲット確定 p_targetNODEは %p\n",targetNODE->p_target);   
    }


    if(!(strNODE->bEND))
    {
        if ((target_node_num == 1)&&(flag == 1))
        {
            strNODE->p_strLEFT_CHILD = (void *)targetNODE->p_target;//交叉
        }
        target_node_num = get_p_target((node_t*)strNODE->p_strLEFT_CHILD,targetNODE,target_node_num,flag);


        if ((target_node_num == 1)&&(flag == 1))
        {
            strNODE->p_strRIGHT_CHILD = (void *)targetNODE->p_target;//交叉
        }
        target_node_num = get_p_target((node_t*)strNODE->p_strRIGHT_CHILD,targetNODE,target_node_num,flag);

    }
    else
    {
        //NOP
    }
    return target_node_num;
}



/*#------------< 確認用 >-------------------#
 *
 */
int look_tree(node_t *strNODE,int node_count)
{

    node_count++;
    if (!(strNODE->bEND))
    {
        //printf("look左%d番目\n",node_count); 
        node_count = look_tree((node_t*)strNODE->p_strLEFT_CHILD,node_count);
        //printf("look右%d番目\n",node_count);
        node_count = look_tree((node_t*)strNODE->p_strRIGHT_CHILD,node_count);
    }
    else
    {
        //printf("ACTION %d\n",strNODE->iACTION);
    }

    return node_count;
}

