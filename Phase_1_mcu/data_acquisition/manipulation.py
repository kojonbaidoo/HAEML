import pandas as pd

def main():
    file_names = ['up_down_validation.txt','up_down.txt','forward_back_validation.txt','forward_back.txt','still_validation.txt','still.txt']
    for file_name in file_names:
        process(file_name=file_name)

def process(file_name):
    all_data = []
    
    try:
        f = open(file_name,'r')
    except:
        print(f'Failes to open: {file_name}')
        return 
    
    all_lines = f.readlines()

    for line in all_lines:
        try:
            result = list(line.replace('\n','').split('\t'))
            result = [int(result[1]),int(result[2]),int(result[3])]
            all_data.append(result)
        except:
            print(f'Failes to process line: {line}')
    f.close()

    columns = ['x','y','z']
    df = pd.DataFrame(data=all_data, columns=columns)
    df.to_csv(file_name.replace('txt','csv'),index=False)


if __name__ == '__main__':
    main()