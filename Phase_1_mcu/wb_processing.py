file_names = ['fixed_i_l1_weights.txt','fixed_i_l1_bias.txt',
                'fixed_l1_l2_weights.txt','fixed_l1_l2_bias.txt',
                'fixed_l2_o_weights.txt','fixed_l2_lo_bias.txt'
                ]

# file_names = [file_names[0]]

for file_name in file_names:
    out_file = open('formatted_'+file_name,'w')
    with open(file_name,'r') as file:
        line = file.readline() 
        while line:
            line = file.readline()
            tmp = line.split('   ')
            result = "("
            for item in tmp:
                result = result + '"' + item + '"' + ","
            result = result[:len(result)-3]
            result = result + "),\n"
            print(result)
            out_file.write(result)
    file.close()
    out_file.close()