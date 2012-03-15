/*#----------< 構造体_ノード >-----------#
 * 末端か?
 *
 *
 */

typedef struct _node
{
    bool b_end;
    int i_action;
    int i_sensor;
    struct node_t *p_right_child;
    struct node_t *p_left_child;
} node_t;


/*#----------< 構造体_戦略木タグ >-----------#
 * 戦略ノード数
 * 得点
 * 戦略木の頂点ノード
 */
typedef struct _tag
{
    int i_node_num;
    int i_point;
    node_t *p_node_top;
} tag_t;


/*#----------< 構造体_ターゲットnodeポインタ >-----------#
 * ダブルポインタが意味不明なのでこれを使う
 * 後々治す
 */
typedef struct _target
{
    node_t *p_target;
} target_t;

