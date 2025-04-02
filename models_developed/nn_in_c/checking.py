import pandas as pd

df = pd.read_csv(r"D:\c_25\ml_in_c\nn_in_c\mnist_test.csv")#("mnist_train.csv")
print(df.head())  # Check the first few rows
print(df.iloc[0])  # Check the first row specifically
print(df.size)
import pandas as pd

# Load the dataset
df = pd.read_csv("mnist_train.csv")

# Save without headers
df.to_csv("mnist_train_no_header.csv", index=False, header=False)

print("Saved dataset without headers!")
