# get commands from reading a file
def unpack(file_name):
    f = open(file_name, 'r')
    return [x.strip() for x in f]

# get commands from direct input
def retrieve():
    commands = []
    command = ''

    while command != '000':
        command = input('command: ')
        if (len(command) == 3 and command.isalnum()):
            commands.append(command)
        else:
            print('Invalid command!')

    return commands

def disassemble(a_list):
    commands_map = {
        '0': ['DAT', 'HLT'],
        '1': 'ADD',
        '2': 'SUB',
        '3': 'STA',
        '5': 'LDA',
        '6': 'BRA',
        '7': 'BRZ',
        '8': 'BRP',
        '9': ['INP', 'OUT']
    }

    for command in a_list:
        if (command[0] == '0' or command[0] == '9'):
            if (command[0] == '9' and command[-1] == '1'):
                print(commands_map[command[0]][0])
            elif (command[0] == '9' and command[-1] == '2'):
                print(commands_map[command[0]][1])
            elif (command[0] == '0' and command[1:] == '00'):
                print(commands_map[command[0]][1])
            else:
                print( '%s %s' % (commands_map[command[0]][0], command[1:]))
        else:
            print('%s %s' % (commands_map[command[0]], command[1:]))


unpacked = unpack('commands.txt')
# unpacked = retrieve()
disassemble(unpacked)
