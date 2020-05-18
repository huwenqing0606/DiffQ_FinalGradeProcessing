/*
 * Processing The Final Grades for MATH 3304 Elementary Differential Equations at Missouri S&T
 *
 *  Created on: 2020年5月17日
 *      Author: Wenqing Hu (Missouri S&T)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const float final_full=150;
const float mid1_full=50;
const float mid2_full=50;
const float mid3_full=100;


int main(){
	FILE *fp = NULL;
	char *line;
	char buffer[1024];
	int student_id[200];
	float final[200];
	float mid1[200];
	float mid2[200];
	float mid3[200];
	float hw[200];
	float semester_score[200];
	char semester_grade[200];
	char ifadjustmid[200];
	float adjusted_smallest_mid[200];
	int line_number=0;
	//read the data from DiffQ_Gradebook.csv
	if ((fp = fopen("DiffQ_Gradebook.csv", "at+")) != NULL)
	{
		char *record = NULL;
		int column_number=1;
		fseek(fp, 170L, SEEK_SET);  //locate to 2nd line, each letter size 1
		while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)	//get the whole line from the gradebook
		{
			if (line_number!=0){
				record = strtok(line, ",");
				while (record != NULL)//read data from each line
				{
					//save the id and scores data
					switch (column_number)
					{
					   case 2:
						   student_id[line_number] = atoi(record);
						   break;
					   case 3:
						   final[line_number] = atof(record);
						   break;
					   case 4:
						   mid1[line_number] = atof(record);
						   break;
					   case 5:
						   mid2[line_number] = atof(record);
						   break;
					   case 6:
						   mid3[line_number] = atof(record);
						   break;
					   case 7:
						   hw[line_number] = atof(record);
						   break;
					}
					ifadjustmid[line_number]='N';
					adjusted_smallest_mid[line_number]=0;
					printf("%s ", record);	//print the current data
					if (column_number == 7)  //only the first 7 columns are recorded [name, id, final, mid1, mid2, mid3, hw]
						break;
					record = strtok(NULL, ",");
					column_number++;
				}
				printf("\n");
				column_number = 1;
			}
			line_number++;
		}
		fclose(fp);
		fp = NULL;
	}
	//process the scores and obtain the class grades
	int num_students;
	num_students = line_number-1;
	printf("Num Students = %d \n", num_students);
	int i;
	for (i=1;i<=num_students;i++){
		//calculate the midterm and final percentages
		float percentage_mid[3], percentage_final;
		percentage_mid[1]=mid1[i]/mid1_full;
		percentage_mid[2]=mid2[i]/mid2_full;
		percentage_mid[3]=mid3[i]/mid3_full;
		percentage_final=final[i]/final_full;
		//find the smallest midterm percentage and locate it
		float smallest_percentage_mid;
		int k, location_smalleset_percentage_mid;
		for (k=1; k<=3; k++){
			if (k==1)
			{
				smallest_percentage_mid=percentage_mid[1];
				location_smalleset_percentage_mid=1;
			}
			else
				if (percentage_mid[k]<smallest_percentage_mid){
					smallest_percentage_mid=percentage_mid[k];
					location_smalleset_percentage_mid=k;
				}
		}
		//compare the smallest midterm percentage with the final percentage
		//if the former one is smaller, then set the index for ifadjustmid=1 and record the adjusted mid score
		if (percentage_final>smallest_percentage_mid){
			ifadjustmid[i]='Y';
			switch (location_smalleset_percentage_mid){
				case 1:
					adjusted_smallest_mid[i]=percentage_final*mid1_full;
					break;
				case 2:
					adjusted_smallest_mid[i]=percentage_final*mid2_full;
					break;
				case 3:
					adjusted_smallest_mid[i]=percentage_final*mid3_full;
					break;
				}
		}
		else
			switch (location_smalleset_percentage_mid){
				case 1:
					adjusted_smallest_mid[i]=mid1[i];
					break;
				case 2:
					adjusted_smallest_mid[i]=mid2[i];
					break;
				case 3:
					adjusted_smallest_mid[i]=mid3[i];
					break;
				}
		//calculate final scores
		if (ifadjustmid[i]=='N')
			semester_score[i]=final[i]+mid1[i]+mid2[i]+mid3[i]+hw[i];
		else
		{
			switch (location_smalleset_percentage_mid){
				case 1:
					semester_score[i]=final[i]+adjusted_smallest_mid[i]+mid2[i]+mid3[i]+hw[i];
					break;
				case 2:
					semester_score[i]=final[i]+mid1[i]+adjusted_smallest_mid[i]+mid3[i]+hw[i];
					break;
				case 3:
					semester_score[i]=final[i]+mid1[i]+mid2[i]+adjusted_smallest_mid[i]+hw[i];
					break;
				}
		}
		//give the grades
		if (semester_score[i]>=400)
			semester_grade[i]='A';
		else
			if (semester_score[i]>=355)
				semester_grade[i]='B';
			else
				if (semester_score[i]>=300)
					semester_grade[i]='C';
				else
					if (semester_score[i]>=265)
						semester_grade[i]='C';
					else
						semester_grade[i]='C';
		//print everything
		printf("%d ", student_id[i]);
		printf(", %f ", final[i]);
		printf(", %f ", mid1[i]);
		printf(", %f ", mid2[i]);
		printf(", %f ", mid3[i]);
		printf(", %f ", hw[i]);
		printf(", %c , %f ", ifadjustmid[i], adjusted_smallest_mid[i]);
		printf(", %f ", semester_score[i]);
		printf(", %c \n", semester_grade[i]);
	}
return 0;
}
