import paramiko
client = paramiko.SSHClient()
client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
client.connect('upBoard', username='erich', password='upboard')
ssh_stdin, ssh_stdout, ssh_stderr = client.exec_command('ls')
#print(ssh_stdin)
#print(ssh_stdout)
for line in ssh_stdout:
    print(line)
#print(ssh_stderr)