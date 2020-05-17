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
		//read the data from DiffQ_Gradebook.csv
		if ((fp = fopen("DiffQ_Gradebook.csv", "at+")) != NULL)
		{
			fseek(fp, 170L, SEEK_SET);  //定位到第二行，每个英文字符大小为1
			char *record = NULL;
			int column_number=1;
			int line_number=0;
			while ((line = fgets(buffer, sizeof(buffer), fp))!=NULL)	//当没有读取到文件末尾时循环继续
			{
				if (line_number!=0){
					record = strtok(line, ",");
					while (record != NULL)//读取每一行的数据
					{
						printf("%s ", record);//将读取到的每一个数据打印出来
						if (column_number == 7)  //只需读取前7列
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
	return 0;
}
