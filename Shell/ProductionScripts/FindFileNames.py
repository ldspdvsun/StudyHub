# -*- coding:utf-8 -*-
"""
@file: FindFileNames.py
@time: 2022/10/21 13:41
@author: Sun
@desc: 遍历某个文件夹下所有文件名
"""
import os, re


def findAllFile(base):
    for root, ds, fs in os.walk(base):
        for f in fs:
            # 正则表达式匹配要查找的文件名，没有的话，默认匹配所有# if re.match(r'.*\d.*', f):
            if re.match(r'.', f):
                fullname = os.path.join(root, f)
                yield fullname


def findAllNames():
    base = 'D:\Projects\lx_file\云平台测试能力建设群_规程备份资料\\20221017_20221021\睢单单20221021新增操作规程\新增操作规程'
    count = 0
    for i in findAllFile(base):
        # 获取文件名称中最后一个反斜线的位置
        last_loc_back_slash = i.rfind('\\')
        # 获取文件名称中最后一个点的位置，一般是文件名后缀前的点
        last_loc_point = i.rfind('.')

        print(i[last_loc_back_slash + 1:last_loc_point])
        count+=1

    print('总文件数',count)


if __name__ == '__main__':
    findAllNames()

