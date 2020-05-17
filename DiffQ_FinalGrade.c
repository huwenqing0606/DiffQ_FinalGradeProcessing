/*
 * Processing The Final Grades for MATH 3304 Elementary Differential Equations at Missouri S&T
 *
 *  Created on: 2020年5月17日
 *      Author: Wenqing Hu (Missouri S&T)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
			printf("Student %d: ", i);
			printf("%d ", student_id[i]);
			printf("%f ", final[i]);
			printf("%f ", mid1[i]);
			printf("%f ", mid2[i]);
			printf("%f ", mid3[i]);
			printf("%f \n", hw[i]);
		}
	return 0;
}
