#include "BmG.h"
#include <stdio.h>
//#include <stdlib.h>


void rank_quicksort(tag_t *tree_tag_array,int left,int right)
{
    int i,j;
    int pivot;
    int tag_point_change;
    int tag_nodenum_change;
    node_t *tag_strTOP_change;
    //tag_strTOP_change = (node_t *)malloc(sizeof(node_t));

    pivot = tree_tag_array[(left + right) / 2].iPOINT;
    i = left;
    j = right;

    while(1)
    {
        while(tree_tag_array[i].iPOINT > pivot)
        { 
            i++;
        }
        while(tree_tag_array[j].iPOINT < pivot)
        {
            j--;
        }
        if(i >= j)
        {
            break;
        }

        tag_strTOP_change = tree_tag_array[i].p_strTOP;
        tag_point_change = tree_tag_array[i].iPOINT;
        tag_nodenum_change = tree_tag_array[i].inodeNUM;

        tree_tag_array[i].p_strTOP = tree_tag_array[j].p_strTOP;
        tree_tag_array[i].iPOINT = tree_tag_array[j].iPOINT;
        tree_tag_array[i].inodeNUM = tree_tag_array[j].inodeNUM;

        tree_tag_array[j].p_strTOP = tag_strTOP_change;
        tree_tag_array[j].iPOINT = tag_point_change;
        tree_tag_array[j].inodeNUM = tag_nodenum_change;
        
        //printf("tree_tag_array[%d].p_strTOP = %p ,tree_tag_array[%d].iPOINT = %d\n",i,&tree_tag_array[i].p_strTOP,i,tree_tag_array[i].iPOINT);
        //printf("tree_tag_array[%d].p_strTOP = %p ,tree_tag_array[%d].iPOINT = %d\n",j,&tree_tag_array[j].p_strTOP,j,tree_tag_array[j].iPOINT);


        i++;
        j--;
    }
    //free(tag_strTOP_change);

    if(left < (i-1))
    {
        rank_quicksort(tree_tag_array,left,(i - 1));
    }
    if((j+1) < right)
    {
        rank_quicksort(tree_tag_array,(j + 1),right);
    }

    return;

}

