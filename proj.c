#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>


void citire_director(char *director,char *file2)
  {
    //deschidere fisier output
    int file_fd2;
   
file_fd2=open(file2,O_RDWR | O_APPEND | O_CREAT , S_IRUSR | S_IWUSR);

if(file_fd2==-1)
{
perror("error open output file");
exit(1);
}
//deschidere director
    DIR *dir;
    
dir=opendir(director);
 
if(dir==NULL)
{
perror("error open director");
exit(1);
}

struct dirent *entry;

while((entry=readdir(dir))!=NULL)
{
  if(strcmp(entry->d_name,"..")!=0 && strcmp(entry->d_name,".")!=0)
    {
      char path[500]={};
      strcat(path,director);
      strcat(path,"/");
      strcat(path,entry->d_name);
      struct stat st_file;
      if(stat(path,&st_file)==-1)
	{
	  perror("stat error");
	  exit(1);
	}
      //director
  if(S_ISDIR(st_file.st_mode))
    {
       int uid;
 uid=(st_file.st_uid);
 
 char str[500];
 
 sprintf(str,"\nnume director: %s\nidentificatorul utilizatorului: %d\n",entry->d_name,uid);

 char str2[300];
 
    if(write(file_fd2,str,strlen(str))==-1)
{
perror("error close file");
exit(1);
}
      const char *access_types[] = {"user", "group", "other"};
   const mode_t permission_masks[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

    for (int i = 0; i < 3; i++)
    {
     snprintf(str2, sizeof(str2), "%s drepturi de acces :", access_types[i]);
            
            snprintf(str2 + strlen(str2), sizeof(str2) - strlen(str2), "%s", (st_file.st_mode & permission_masks[i * 3]) ? "R" : "-");
            
            snprintf(str2 + strlen(str2), sizeof(str2) - strlen(str2), "%s", (st_file.st_mode & permission_masks[i * 3 + 1]) ? "W" : "-");
           
            snprintf(str2 + strlen(str2), sizeof(str2) - strlen(str2), "%s\n", (st_file.st_mode & permission_masks[i * 3 + 2]) ? "X" : "-");
            
         if(write(file_fd2,str2,strlen(str2))==-1)
{
perror("error close file");
exit(1);
}
    }
    }
   //legatura simbolica
  
   else if(entry->d_type == DT_LNK)
    {
       struct stat lst_file;
      if(lstat(path,&lst_file) == -1)
	{
	  perror("stat error");
	  exit(1);
	}
      char str7[500];
      sprintf(str7,"\nnume legatura: %s\ndimensiunea legatura: %ld\ndimensiune fisier: %ld\n",entry->d_name,lst_file.st_size,st_file.st_size);

          if(write(file_fd2,str7,strlen(str7))==-1)
{
perror("error close file");
exit(1);
}
      char str8[300];
        const char *access_types[] = {"user", "group", "other"};
   const mode_t permission_masks[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

    for (int i = 0; i < 3; i++)
    {
      snprintf(str8,sizeof(str8),"%s drepturi de acces legatura :", access_types[i]);
      snprintf(str8 + strlen(str8),sizeof(str8) - strlen(str8),"%s", (lst_file.st_mode & permission_masks[i * 3]) ? "R" : "-");
      snprintf(str8 + strlen(str8),sizeof(str8) - strlen(str8),"%s", (lst_file.st_mode & permission_masks[i * 3 + 1]) ? "W" : "-");
      snprintf(str8 + strlen(str8),sizeof(str8) - strlen(str8),"%s\n", (lst_file.st_mode & permission_masks[i * 3 + 2]) ? "X" : "-");

          if(write(file_fd2,str8,strlen(str8))==-1)
{
perror("error close file");
exit(1);
}
	}
    }
  
  //fisere BMP
  
  else if (strstr(entry->d_name, ".bmp") != NULL) 
    {

      if(!S_ISREG(st_file.st_mode))
  {
    perror("not regular");
    exit(1);
  }
       int uid,links;
 uid=(st_file.st_uid);
 links =(st_file.st_nlink);
 int fd;
  fd=open(entry->d_name,O_RDONLY);
  if(fd==-1)
    {
  perror("error open bmp file");
  exit(1);
    }
     int dimens,inaltimea,lungimea;
    lseek(fd,18,SEEK_SET);
  if(read(fd,&inaltimea,sizeof(int))!=sizeof(int))
    {
      perror("error read");
      exit(1);
    }
  if(read(fd,&lungimea,sizeof(int))!=sizeof(int))
    {
      perror("error read");
      exit(1);
    }
 
    lseek(fd,2,SEEK_SET);
  if(read(fd,&dimens,sizeof(int))!=sizeof(int))
    {
      perror("error read");
      exit(1);
    }
  char str3[500];
 
  sprintf(str3,"\nnume fisier: %s\ninaltime: %d\nlungime: %d\ndimensiune: %d\nidentificatorul utilizatorului: %d\ntimpul ultimei modificari: %scontorul de legaturi: %d\n",entry->d_name,inaltimea,lungimea,dimens,uid,ctime(&st_file.st_mtime),links);

 
    if(write(file_fd2,str3,strlen(str3))==-1)
{
perror("error close file");
exit(1);
}
     char str4[300];
        const char *access_types[] = {"user", "group", "other"};
   const mode_t permission_masks[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

    for (int i = 0; i < 3; i++)
    {
     snprintf(str4, sizeof(str4), "%s drepturi de acces :", access_types[i]);
           
            snprintf(str4 + strlen(str4), sizeof(str4) - strlen(str4), "%s", (st_file.st_mode & permission_masks[i * 3]) ? "R" : "-");
           
            snprintf(str4 + strlen(str4), sizeof(str4) - strlen(str4), "%s", (st_file.st_mode & permission_masks[i * 3 + 1]) ? "W" : "-");
           
            snprintf(str4 + strlen(str4), sizeof(str4) - strlen(str4), "%s\n", (st_file.st_mode & permission_masks[i * 3 + 2]) ? "X" : "-");
            
         if(write(file_fd2,str4,strlen(str4))==-1)
{
perror("error close file");
exit(1);
}
    }
    }
  //fisiere normale
  
  else if (strstr(entry->d_name, ".bmp") == NULL && S_ISREG(st_file.st_mode) && !(S_ISLNK(st_file.st_mode)))
    {
      
      if(!S_ISREG(st_file.st_mode)){
    perror("not regular");
    exit(1);
  }
      int uid,links,dimens;
      dimens=(st_file.st_size);
 uid=(st_file.st_uid);
 links =(st_file.st_nlink);
 int fd;
  fd=open(path,O_RDONLY);
  if(fd==-1)
    {
  perror("error open normal file");
  exit(1);
    }
     char str5[500];
   sprintf(str5,"\nnume fisier: %s\ndimensiune: %d\nidentificatorul utilizatorului: %d\ntimpul ultimei modificari: %scontorul de legaturi: %d\n",entry->d_name,dimens,uid,ctime(&st_file.st_mtime),links);

 
    if(write(file_fd2,str5,strlen(str5))==-1)
{
perror("error close file");
exit(1);
}
     char str6[300];
        const char *access_types[] = {"user", "group", "other"};
   const mode_t permission_masks[] = {S_IRUSR, S_IWUSR, S_IXUSR, S_IRGRP, S_IWGRP, S_IXGRP, S_IROTH, S_IWOTH, S_IXOTH};

    for (int i = 0; i < 3; i++)
    {
     snprintf(str6, sizeof(str6), "%s drepturi de acces :", access_types[i]);
            
            snprintf(str6 + strlen(str6), sizeof(str6) - strlen(str6), "%s", (st_file.st_mode & permission_masks[i * 3]) ? "R" : "-");
           
            snprintf(str6 + strlen(str6), sizeof(str6) - strlen(str6), "%s", (st_file.st_mode & permission_masks[i * 3 + 1]) ? "W" : "-");
            
            snprintf(str6 + strlen(str6), sizeof(str6) - strlen(str6), "%s\n", (st_file.st_mode & permission_masks[i * 3 + 2]) ? "X" : "-");
            
         if(write(file_fd2,str6,strlen(str6))==-1)
{
perror("error close file");
exit(1);
}
   
    }
    }
 
 
    }
 }
 
 if(closedir(dir)==-1)
{
perror("close director");
exit(1);
}
if(close(file_fd2)==-1)
    {
      perror("error close output file");
      exit(1);
    }
  }
    
  int main(int argc,char *argv[])
  {
  if(argc!=2)
    {
      printf("numar incorect de argumente");
      exit(1);
      
    }
  char *file2="statistica.txt";
  
 char *director=argv[1];
 citire_director(director,file2);
 
 
 return 0;
  }
//probleme: alte directoare ca argument/ nu merge decat cu ./SO2 .
