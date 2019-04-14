import paramiko
import time


class EtInterface:
    def __init__(self):
        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect('upboard', username='erich', password='upboard')
        self.sh = client.invoke_shell()
        endCnt = 0
        self.initText = ''
        while endCnt < 20:
            if not self.sh.recv_ready():
                endCnt += 1
                time.sleep(0.1)
            else:
                endCnt = 0
                #self.initText += self.sh.recv(1).decode('UTF-8')
                self.sh.recv(1) #dummy read

        self.exec_cmd('cd myrepos/ET/source/upBoard/', True)

    def connect(self):
        print('unused')

    def start_exec(self):
        self.exec_cmd('')

    def exec_cmd(self, cmd, suppress_output=False):
        self.sh.send(cmd + '\n')

        #ommit first line as it only contains the cmd
        while(self.sh.recv(1).decode('UTF-8') != '\n'):
            pass

        endCnt = 0
        while endCnt < 20:
            if not self.sh.recv_ready():
                endCnt += 1
                time.sleep(0.1)
            else:
                endCnt = 0
                ch = self.sh.recv(1).decode('UTF-8')
                if not suppress_output:
                    print(ch, end='')


