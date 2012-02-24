headers = "#include <string>\n#include <iostream>\n"
headers+="#include <vector>\n#include <sstream>\n"
headers+="#include <set>\n#include <map>\n#include <queue>\n\n"
headers+="using namespace std;\n\n"


data = open("C:\source.txt")
strala = data.read()

index1 = strala.index('Class:')
index2 = strala.index('Method:')

clsname = strala[index1+7:index2-1]

Cls = "class "+clsname+"\n{\npublic:\n"

index3 = strala.index('re:')
index4 = strala.index('(be sure')

func = strala[index3+4:index4-1]

sign = "	"+func+";\n};\n\n"

func2 = func[0:func.index(" ")+1]+clsname
func2+="::"+func[func.index(" ")+1:]+"\n{\n\n}\n\n"

print headers,Cls,sign,func2

dest = open("C:\\Algorithms\\"+clsname+".cpp",'w') 
mane = "int main()\n{\n"
mane += "	"+clsname+" lala;\n\n"
mane += "	return 0;\n}\n"
dest.write(headers+Cls+sign+func2+mane);

data.close()
dest.close()

