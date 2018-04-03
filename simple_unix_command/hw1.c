#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUMBER 5
#define PATTERN 8

enum NUM {
   FIRST,
   SECOND,
   THIRD,
   FOURTH,
   FIFTH
};

int main()
{
   FILE *fp;
   int i=0;
   int ran_num=0;
   int ran_file=0;
   int ran=0;
   int cnt=0;
   char ran_name[NUMBER][20] = {"KwangWoon", "University", "Embedded", "Programming", "Design"};
   char ran_pattern[PATTERN][10] = {"tab", "enter", "space", "num", "esc", "ctrl", "alt", "shift"};

   char filename[40];

   srand((unsigned int)time(NULL));
   ran_file = rand()%NUMBER;
   ran_num = rand()%PATTERN;
   printf("Filname : [%s]\n", ran_name[ran_file]);
   printf("String : [%s]\n", ran_pattern[ran_num]);

   system("rm -rf ~/work");
   system("mkdir ~/work");
   system("mkdir ~/work/first");
   system("mkdir ~/work/second");
   system("mkdir ~/work/third");
   system("mkdir ~/work/fourth");
   system("mkdir ~/work/fifth");

   switch(ran_file)
   {
      case FIRST :
         fp = fopen("./Kwangwoon.txt", "wt");
         break;

      case SECOND :
         fp = fopen("./University.txt", "wt");
         break;

      case THIRD :
         fp = fopen("./Embedded.txt", "wt");
         break;

      case FOURTH :
         fp = fopen("./Programming.txt", "wt");
         break;

      case FIFTH :
         fp = fopen("./Design.txt", "wt");
         break;
   }

   while(1)
   {
      ran = rand()%PATTERN;
      if(ran == ran_num) cnt++;
      fprintf(fp, "%s\n", ran_pattern[ran]);
      i++;
     
      if(i == PATTERN && cnt != 0) break;
      else if(i == PATTERN && cnt == 0)
      {
         fprintf(fp, "%s\n", ran_pattern[ran]);
         break;
      }
   }

   if(ran_file == FIRST) system("mv ./Kwangwoon.txt ~/work/first/");
   else if(ran_file == SECOND) system("mv ./University.txt ~/work/second");
   else if(ran_file == THIRD) system("mv ./Embedded.txt ~/work/third");
   else if(ran_file == FOURTH) system("mv ./Programming.txt ~/work/fourth");
   else if(ran_file == FIFTH) system("mv ./Design.txt ~/work/fifth");
   
   fclose(fp);
   return 0;
}
