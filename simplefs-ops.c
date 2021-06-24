#include "simplefs-ops.h"
#include "simplefs-disk.c"
#include <string.h> 
extern struct filehandle_t file_handle_array[MAX_OPEN_FILES]; // Array for storing opened files

int simplefs_create(char *filename){
	
	int i=0;
	int c;
	struct inode_t *inode = (struct inode_t *)malloc(sizeof(struct inode_t));
	//Check in 8 Nodes if some file exist
	//return -1 if some file already exists
	
	while(i!=8)
	{
		simplefs_readInode(i, inode);
		c=compare(inode->name, filename);
		if(c==0){
			return -1;
		}
		i++;
	}
	
	//Returns -1 on failure
	int inode_num = simplefs_allocInode();
	printf("%d\n",inode_num);
	if(inode_num == -1)
		return -1;

	//Creating a node
	
    strcpy(inode->name, filename);
    inode->status = INODE_IN_USE;
    inode->file_size = 0;
    for(i=0; i<4; i++)	
    	inode->direct_blocks[i] = -1;

    simplefs_writeInode(inode_num, inode);
    free(inode);
	
    return inode_num;
}


void simplefs_delete(char *filename){
    /*
	    delete file with name `filename` from disk
	*/
}

int simplefs_open(char *filename){
    /*
	    open file with name `filename`
	*/
    return -1;
}

void simplefs_close(int file_handle){
    /*
	    close file pointed by `file_handle`
	*/

}

int simplefs_read(int file_handle, char *buf, int nbytes){
    /*
	    read `nbytes` of data into `buf` from file pointed by `file_handle` starting at current offset
	*/
    return -1;
}


int simplefs_write(int file_handle, char *buf, int nbytes){
    /*
	    write `nbytes` of data from `buf` to file pointed by `file_handle` starting at current offset
	*/
    return -1;
}


int simplefs_seek(int file_handle, int nseek){
    /*
	   increase `file_handle` offset by `nseek`
	*/
    return -1;
}
// Comparing both the strings.  
int compare(char a[],char b[])  
{  
    int flag=0,i=0;  // integer variables declaration  
    while(a[i]!='\0' &&b[i]!='\0')  // while loop  
    {  
       if(a[i]!=b[i])  
       {  
           flag=1;  
           break;  
       }  
       i++;  
    }  
    if(flag==0)  
    return 0;  
    else  
    return 1;  
} 
int main(){
	int r;
	char input[20];
	printf("--Create a file--\n");
	printf("Enter file name\n");
	gets(input);
	printf("%s",input);
	r=simplefs_create(input);
	if(r!=-1){
		printf("Inode=%d\n",r);
	}
	
}


