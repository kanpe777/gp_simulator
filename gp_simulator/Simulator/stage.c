/*
// stage.c
// ステージ設定
 */

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "BmG.h"

int stage(int stgnum){
    FILE *fp;
    char s[COLS];


    //もっといい方法があるかも
    if(stgnum == 1){
        if((fp = fopen("./stage/stage1.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 2){
        if((fp = fopen("./stage/stage2.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 3){
        if((fp = fopen("./stage/stage3.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 4){
        if((fp = fopen("./stage/stage4.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 5){
        if((fp = fopen("./stage/stage5.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 6){
        if((fp = fopen("./stage/stage6.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 7){
        if((fp = fopen("./stage/stage7.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 8){
        if((fp = fopen("./stage/stage8.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 9){
        if((fp = fopen("./stage/stage9.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }else if(stgnum == 10){
        if((fp = fopen("./stage/stage10.txt","r")) == NULL){
            fprintf(stderr,"file open error!!\n");
            exit(1);
        }
    }
    while(fgets(s,256,fp) != NULL){
        printw("%s",s);
    }
    fclose(fp);  
    return 0;
}
