#include <stdio.h>
#include "myheader.h"


int main(int argc, char* argv[])
{

char *cptr;
int id;
int *outptr, *inptr, *counter;
student *students;

if((id = shmget(123, 100, PERM)) == -1){
	perror("Failed to create shared memory segment");
	return 1;
}

if((cptr = (char *)shmat(id, NULL, 0)) == (void *)-1){
	perror("Failed to attach shared memory segment");
	return 1;
}

inptr = (int *)(cptr);
outptr = (int *)(cptr+4);
counter = (int *)(cptr+8);

*inptr = 0;
*outptr = 0;
*counter = 0;

while(1){

while ((*counter) == BUFSIZE);

printf("Enter SID : ");
scanf("%d", &students[*inptr].SID);
printf("Enter Name : ");
scanf("%s", students[*inptr].name);
printf("Wrote at %d\n", *inptr);
*inptr = (*inptr + 1) % BUFSIZE;
*counter = (*counter) + 1;
}

return 0;


}

