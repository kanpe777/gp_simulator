#include <stdlib.h>
#include <stdbool.h>
#include <curses.h>
/*#-----< BmG(Boy_meets_Girl).h >#
 * すべては main.c で使えるようにするためのヘッダファイル
 *
 */


/*#--------< ノード >--------#
 * 末端か?(YES=true,NO=false)
 * 行動番号(0~4の5つの行動)左,左上,上,右上,右
 * センサー番号(眼の前3種類、足元3種類、計6種類)
 * 右子ノードのポインタ
 * 左子ノードのポインタ
 */
typedef struct _node {
        bool bEND;
        int iACTION;
        int iSENSOR;
        //struct node_t *strPARENT;
        struct node_t *p_strRIGHT_CHILD;
        struct node_t *p_strLEFT_CHILD;
} node_t;

/*#-------< タグ >-------#
 * 得点
 * 戦略木の頂点ノードのポインタ
 */
typedef struct _tag {
        int inodeNUM;
        int iPOINT;
        node_t *p_strTOP;
} tag_t;


/*#---------< ターゲットNODEポインタ  >-----------#
 * ダブルが意味不明なのでこれ使う
 */
typedef struct _target {
        node_t *p_target;
} target_t;


//tree.c
//extern void tree_create(node_t *strNODE,int node_depth);
extern int tree_create(node_t *strNODE,int node_count,int node_depth);
extern void free_strNODE(node_t *strNODE);
//extern int copy_tree(node_t *strNODE,node_t *copy_base_array,int id);
extern int copy_tree(node_t *strNODE,node_t *copy_base_array,int base_array_id);
extern int paste_tree(node_t *strNODE,node_t *copy_base_array,int base_array_id);
extern int get_p_target(node_t *strNODE,target_t *p_targetNODE,int target_node_num,int flag);
extern int look_tree(node_t *strNODE,int node_count);


//choice.c
extern void choice(tag_t *tree_tag_array,int tree_max,int choice_percentage);

//rank.c
extern void rank_quicksort(tag_t *tree_tag_array,int left,int right);

//mutate.c
extern void mutate(tag_t *tree_tag_array,int tree_max,int mutate_target_id); 


//simulator
typedef struct Agent_status {
    int X;
    int Y;
    int INTERTIA;
    int TIMES;
    int END_FLAG;
    int TOTAL_POINTS;
    int ON_OFF;
    int Jumpflag;
    int ENEMY_TOUCH_FLAG;
} Agent_status;

typedef struct Girl {
    int X;
    int Y;
} Girl;

extern int stage();
extern int simulate();
