# coding:utf-8
"""
@File    : test.py
@Time    : 2022/10/7 9:19
@Author  : Sun
@Description : 
"""
import matplotlib.pyplot as plt
import xlrd
from matplotlib import ticker
plt.rcParams['font.family']='SimHei'

worksheet = xlrd.open_workbook(r'E:\Anaconda\file\油松刺槐6789月液流速率图.xlsx')

Pinus_tabuliformis=worksheet.sheet_by_index(0)
Robinia_pseudoacacia=worksheet.sheet_by_index(1)
Pinus_tabuliformis_Robinia_pseudoacacia_x=Pinus_tabuliformis.col_values(4)[1:Pinus_tabuliformis.nrows]
# 创建x轴标签使用
Pinus_tabuliformis_Robinia_pseudoacacia_x2=Pinus_tabuliformis.col_values(2)[1:Pinus_tabuliformis.nrows]
Pinus_tabuliformis_y=Pinus_tabuliformis.col_values(3)[1:Pinus_tabuliformis.nrows]
Robinia_pseudoacacia_y=Robinia_pseudoacacia.col_values(3)[1:Robinia_pseudoacacia.nrows]

plt.xticks(rotation=90)
plt.plot(Pinus_tabuliformis_Robinia_pseudoacacia_x, Pinus_tabuliformis_y, 'p-', color='r', label="Pinus_tabuliformis")
plt.plot(Pinus_tabuliformis_Robinia_pseudoacacia_x, Robinia_pseudoacacia_y, '*:', color='b', label="Robinia_pseudoacacia")
plt.xticks(list(range(0,96)),Pinus_tabuliformis_Robinia_pseudoacacia_x2)
plt.gca().xaxis.set_major_locator(ticker.MultipleLocator(12))
plt.xlabel("TIME")#横坐标名字
plt.ylabel("sap velocity(cm/h)")#纵坐标名字
plt.legend(loc="upper right")# 标签位置
plt.grid(True, linestyle='--', alpha=0.5)
plt.savefig("f1.jpg",dpi=900)

plt.show()