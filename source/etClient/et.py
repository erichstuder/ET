
import EtInterface

etInterface = EtInterface.EtInterface()
execMode = False
while True:
    t = input()
#   print(text)
    if t.strip() == 'connect':
        etInterface.connect()
    elif t.strip() == 'exec':
        etInterface.start_exec()
        execMode = True
    elif t.strip() == 'q':
        if execMode:
            execMode = False
            print('exec mode finished')
        else:
            print('nothing to quit')
    elif execMode:
        #print(t.strip)
        etInterface.exec_cmd(t)
    elif t.strip() == 'q':
        break
    else:
        print('unknown command')



