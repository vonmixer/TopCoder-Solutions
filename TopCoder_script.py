"""This utility will read a source file containing a Topcoder problem description and then
populate a .cpp file appropriately. It will add some common header files, a skeleton class
with the necessary function, and the main function along with the test data from the first
example in the problem description
"""

import re

headers = "#include <string>\n#include <iostream>\n"
headers+="#include <vector>\n#include <sstream>\n"
headers+="#include <set>\n#include <map>\n#include <queue>\n\n"
headers+="using namespace std;\n\n"


data = open("C:\source.txt")
strala = data.read()

cls_start = strala.index('Class:')
cls_end = strala.index('Method:')

func_start = strala.index('re:')
func_end = strala.index('(be sure')

param_start = strala.index('ers:')
param_end = strala.index('Returns:')
ret_end = strala.index('Method ')

"""Get class name"""
clsname = strala[cls_start+7:cls_end-1]
Cls = "class "+clsname+"\n{\npublic:\n"

func = strala[func_start+4:func_end-1]      
params = strala[param_start+5:param_end-1]  
ret = strala[param_end+9:ret_end-1]         
split_params = re.split(',',params);        
sign = "	"+func+";\n};\n\n"          
func_name = func[len(ret)+1:func.index('(')]

func2 = func[0:func.index(func_name)]+clsname
func2+="::"+func[func.index(func_name):]+"\n{\n\n}\n\n"

"""Generate list of names for parameters"""
split_names = list(split_params)
split_vals = list(split_params)
for i in range(len(split_params)):
    if(i>0):
        split_params[i] = split_params[i][1:]
    split_names[i] = 'a'+str(i)

test_val = strala[strala.index('0)')+9:strala.index('Returns: ')]

"""Extract values from first example"""
i=-1
while(len(test_val)>0):
    i+=1
    if(test_val[0] != '{'):
        split_vals[i] = test_val[0:test_val.index('\n')]
        test_val = test_val[test_val.index('\n')+1:]
    else:
        split_vals[i] = test_val[1:test_val.index('}')]
        test_val = test_val[test_val.index('}')+5:]

data.close()

dest = open("C:\\Algorithms\\"+clsname+".cpp",'w') 
mane = "int main()\n{\n"
mane += "	"+clsname+" lala;\n"

"""Declare parameters"""
for i in range(len(split_names)):
    mane += "	"+split_params[i]+" "+split_names[i]+";\n"

"""Assign values to parameters"""
for i in range(len(split_names)):
    if(split_vals[i].find(',')!=-1):
        while(len(split_vals[i])>0):
            if(split_vals[i].find(',')!=-1):
                mane += "	"+split_names[i]+'.push_back('+split_vals[i][0:split_vals[i].index(',')]+");\n"
                split_vals[i] = split_vals[i][split_vals[i].index(',')+1:]
            else:
                mane += "	"+split_names[i]+'.push_back('+split_vals[i]+");\n"
                split_vals[i] = ""
    else:
        while(len(split_vals[i])>0):
            mane += "	"+split_names[i]+'.push_back('+split_vals[i]+");\n"
            split_vals[i] = ""
            

mane += "	lala."+func_name+"("

i = 1
for i in range(len(split_names)):
    mane += split_names[i]
    if i!=len(split_names)-1:
        mane+=","
mane += ");\n"

mane += "	return 0;\n}\n"
dest.write(headers+Cls+sign+func2+mane);

dest.close()


