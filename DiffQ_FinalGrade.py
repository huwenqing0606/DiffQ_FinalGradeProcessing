#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat May 16 18:15:16 2020

Title: processing the final score and grades for MATH3304 Elementary Differential Equations

Algorithm: Score=Final+Midterm+HW, Lowest midterm percentage score is replaced by final percentage score if the former is smaller than the latter 

@author: Wenqing Hu (Missouri S&T)
"""

import pandas as pd
import numpy as np

#import the gradebook file and the scores
file_Grade = "DiffQ_Gradebook.csv"
score = pd.read_csv(file_Grade)
#read the the student name and id
student_name = list(score.iloc[:,0])
student_id = np.array(score.iloc[:,1])
#read the the final score
score_final = np.array(score.iloc[:,2])
#read the the midterm scores
score_mid1 = np.array(score.iloc[:,3])
score_mid2 = np.array(score.iloc[:,4])
score_mid3 = np.array(score.iloc[:,5])
#read the the homework scores
score_hw = np.array(score.iloc[:,6])

#number of students
num_stu=len(student_id)

#data preprocessing, all nan are turned into 0
for i in range(num_stu):
    if np.isnan(score_final[i]):
        score_final[i] = 0
    if np.isnan(score_mid1[i]):
        score_mid1[i] = 0
    if np.isnan(score_mid2[i]):
        score_mid2[i] = 0
    if np.isnan(score_mid3[i]):
        score_mid3[i] = 0
    if np.isnan(score_hw[i]):
        score_hw[i] = 0
    
#full scores of final, midterms, hw
score_final_full = 150
score_mid_full = [50, 50, 100]
score_hw_full = 100

#concatenate all information into one list consisting of [name, id, grade, total, final, mid1, mid2, mid3, hw, ifadjustedmid, orignalmid1, orignalmid2, orignalmid3]
complete_info_list=[]
for i in range(num_stu):
    complete_info_list.append([student_name[i], student_id[i], '', 0, score_final[i], score_mid1[i], score_mid2[i], score_mid3[i], score_hw[i], 'N', score_mid1[i], score_mid2[i], score_mid3[i]])

#write everything into the final gradebook
finalgradebook = open('DiffQ_Gradebook_Final.txt', 'w') 


for i in range(num_stu):
    #find the percentage scores of midterm scores
    midterm_percentage = np.array([complete_info_list[i][5]/score_mid_full[0], complete_info_list[i][6]/score_mid_full[1], complete_info_list[i][7]/score_mid_full[2]])
    #find the minimum of percentage of midterm scores, and identify its index
    midterm_percentage_min = np.min(midterm_percentage)
    midterm_percentage_min_index = np.where(midterm_percentage == np.min(midterm_percentage))
    midterm_percentage_min_index = midterm_percentage_min_index[0][0]
    #find the final percentage score
    final_percentage = complete_info_list[i][4]/score_final_full
    #replace the lowest midterm by the final discounted to midterm full score if the former percentage is lower than the final percentage
    if final_percentage > midterm_percentage_min:
        complete_info_list[i][5+midterm_percentage_min_index] = final_percentage*score_mid_full[midterm_percentage_min_index]
        complete_info_list[i][9]='Y'
    #calculate the total score
    complete_info_list[i][3]=int(complete_info_list[i][4]+complete_info_list[i][5]+complete_info_list[i][6]+complete_info_list[i][7]+complete_info_list[i][8])
    #determine the grade
    if complete_info_list[i][3] >= 400:
        complete_info_list[i][2]='A'
    elif complete_info_list[i][3] >= 355:
        complete_info_list[i][2]='B'
    elif complete_info_list[i][3] >= 310:
        complete_info_list[i][2]='C'
    elif complete_info_list[i][3] >= 265:
        complete_info_list[i][2]='D'
    else:
        complete_info_list[i][2]='F'
    #print everything to the final gradebook
    print(complete_info_list[i], file=finalgradebook)

finalgradebook.close()