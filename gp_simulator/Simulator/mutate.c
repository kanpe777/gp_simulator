#include <stdio.h>
#include "BmG.h"


void mutate(tag_t *tree_tag_array,int tree_max,int mutate_target_id)
{
    
    int target_node_num = random() % tree_tag_array[mutate_target_id].inodeNUM + 1;
    int search_flag = 0;
    int dammy = 0;



    target_t *mutate_target;
    mutate_target = (target_t*)malloc(sizeof(target_t));
    get_p_target(tree_tag_array[mutate_target_id].p_strTOP,mutate_target,target_node_num,search_flag);
    
    if (mutate_target->p_target->bEND)
    {
        tree_create(mutate_target->p_target,dammy,dammy);
    }
    else
    {
        free_strNODE((node_t*)mutate_target->p_target->p_strLEFT_CHILD); 
        free_strNODE((node_t*)mutate_target->p_target->p_strRIGHT_CHILD);
        tree_create(mutate_target->p_target,dammy,dammy);
    }



    free(mutate_target);
    return;
}

