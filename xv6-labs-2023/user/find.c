#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

#define MAX_PATH_LENGTH 500
char* fmtname(char *path);

void find( char *path, char *fname);

int main(int argc, char *argv[]){
  
  // get the file name from argument
  if (argc == 3){
    find(".", argv[2]);
    exit(0);
  }



  printf("couldn' find the file\n");
  exit(-1);
}

void find( char* path, char *fname){
  // try to find all the file name inside current directory
  // if couldn't then go to the next directory if exist
  // if there is no directory then simply return false and declare files cannot find
  struct stat st;
  struct dirent de;
  char buf[MAX_PATH_LENGTH];
  int fd;
  char *p;

  if ((fd = open(path, O_RDONLY)) < 0){
    fprintf(2, "Connot open %s\n", path);
    return;
  }
 
  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }
   switch(st.type){
   case T_DIR:
     if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
       printf("ls: path too long\n");
       break;
     }
     strcpy(buf, path);
     p = buf+strlen(buf);
     *p++ = '/';
     while(read(fd, &de, sizeof(de)) == sizeof(de)){
       if(de.inum == 0)
         continue;
       memmove(p, de.name, DIRSIZ);
       p[DIRSIZ] = 0;
       if(stat(buf, &st) < 0){
         printf("find: cannot stat %s\n", buf);
         continue;
       }
       if (st.type == T_DIR && strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0){
          find(buf, fname);
        } else if (st.type == T_FILE && strcmp(de.name, fname) == 0){
	  buf[strlen(buf)] = '\n';
          printf("%s", buf);
        }
     }
     break;
  }
  close(fd);
 }
