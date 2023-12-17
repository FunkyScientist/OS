#include <stdio.h>
#include "myheader.h"
int main(){
char *cptr;
int id;
int *outptr,*inptr,*counter;
student *students;

if((id=shmget(123,160,PERM))==-1){
 perror("Failed to create shared memory segment");
 return 1;
}
if((cptr=(char *)shmat(id,NULL,0))==(void *)-1){
perror("failed to atttach shared memory segment");
return 1;

}
inptr=(int *)(cptr);
outptr=(int *)(cptr+4);
counter=(int *)(cptr+8);
students=(student *)(cptr+12);
*inptr=0;
*outptr=0;
*counter=0;


while(1){
while ((*counter)==BUFSIZE); //DO NOTHING
printf("Enter SID : ");
scanf("%d", &students[*inptr].SID);
printf("Enter Name : ");
scanf("%s",students[*inptr].name);
printf("wrote at %d\n",*inptr);
*inptr =(*inptr + 1) %BUFSIZE;
*counter=(*counter)+1;
}

return 0;




}
