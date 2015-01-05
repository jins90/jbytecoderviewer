class Opcode:
  code_name = ''
  value = ''
  h_value = 0
  params = ''
  def  __init__(self, code, v, p):
      self.code_name = code
      self.value = v
      self.params = p
      self.h_value = int(v, 16)
  def sprint(self):
      print self.code_name, self.value, self.h_value, self.params
  def printC(self):
      r = '    "' + self.code_name.strip() + '"' + ", "
      print r
  def printParam(self):
      if(self.params.isdigit()):
         r = '    ' + self.params.strip() + ", "
         print r
      else:
         print '    -1, '      
   
f = open('opcode.txt', 'r')
line = f.readline()
r = []
while(line):
  line = line.strip()
  arg = line.split('\t')
  arg[2] = arg[2].strip()
  if(arg[2] != ''):
      arg2 = arg[2].split(':')
#      print arg[0], arg[1], arg2[0]
      r.append(Opcode(arg[0], arg[1], arg2[0]))
  else:
#      print arg[0], arg[1]
      r.append(Opcode(arg[0], arg[1], '0'))
  line = f.readline()


r = sorted(r, key=lambda value : value.h_value)

for x in r:
   x.printParam()
