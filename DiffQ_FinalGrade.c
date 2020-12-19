/*
 * Processing The Final Grades for MATH 3304 Elementary Differential Equations at Missouri S&T
 *
 *  Created on: 2020 Spring
 *      Author: Wenqing Hu (Missouri S&T)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const float final_full=200;
const float mid1_full=100;
const float mid2_full=100;
const float mid3_full=100;


int main(){
	FILE *fp = NULL;
	char *line;
	char buffer[1024];
	char *student_name_1[200];
	char *student_name_2[200];
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
	//imput data file column structure: student name, student id, final, mid1, mid2, mid3, hw
	//all empty blocks must be filled by 0
	if ((fp = fopen("DiffQ_Gradebook.csv", "at+")) != NULL)
	{
		char *record = NULL;
		int column_number=1;
		fseek(fp, 0, SEEK_SET);  //locate to the beginning of file
		while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)	//get the whole line from the gradebook
		{
			if (line_number!=0){
				record = strtok(line, ",");
				while (record != NULL)//read data from each line
				{
					//save the id and scores data
					switch (column_number)
					{  case 1:
						   student_name_1[line_number]=(char *)malloc(100*sizeof(char));
						   strcpy(student_name_1[line_number], record);
						   break;
					   case 2:
						   student_name_2[line_number]=(char *)malloc(100*sizeof(char));
						   strcpy(student_name_2[line_number], record);
						   break;
					   case 3:
						   student_id[line_number] = atoi(record);
						   break;
					   case 4:
						   final[line_number] = atof(record);
						   break;
					   case 5:
						   mid1[line_number] = atof(record);
						   break;
					   case 6:
						   mid2[line_number] = atof(record);
						   break;
					   case 7:
						   mid3[line_number] = atof(record);
						   break;
					   case 8:
						   hw[line_number] = atof(record);
						   break;
					}
					ifadjustmid[line_number]='N';
					adjusted_smallest_mid[line_number]=0;
					printf("%s ", record);	//print the current data
					if (column_number == 8)  
					//only the first 8 columns are recorded [name_1, name_2, id, final, mid1, mid2, mid3, hw]
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
	//set the output file
	FILE *output=NULL;
	output=fopen("DiffQ_Gradebook_Final.csv","w");
	fprintf(output, "%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s \n", "name", "id", "grade", "total", "final", "mid1", "mid2", "mid3", "hw", "adjust?", "adjusted min mid");
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
		if (semester_score[i]>=540)
			semester_grade[i]='A';
		else
			if (semester_score[i]>=480)
				semester_grade[i]='B';
			else
				if (semester_score[i]>=420)
					semester_grade[i]='C';
				else
					if (semester_score[i]>=360)
						semester_grade[i]='D';
					else
						semester_grade[i]='F';
		//print everything to file
		fprintf(output, "%s, %s, %d, %c, %f, ", student_name_1[i], student_name_2[i], student_id[i], semester_grade[i], semester_score[i]);
		fprintf(output, "%f, %f, %f, %f, %f, %c, %f \n", final[i], mid1[i], mid2[i], mid3[i], hw[i], ifadjustmid[i], adjusted_smallest_mid[i]);
	}
	fclose(output);
return 0;
}
