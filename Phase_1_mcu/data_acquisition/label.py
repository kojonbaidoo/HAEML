import pandas as pd

def main():
    file_names = ['up_down.csv', 'still.csv','forward_back.csv']
    labels = [1,0,2]
    for i in range(len(file_names)):
        label(file_name=file_names[i], label=labels[i])

def label(file_name, label):
    df = pd.read_csv(file_name)
    df['label'] = len(df['x']) * [label]
    df.to_csv('labeled_'+file_name,index=False)


if __name__ == '__main__':
    main()