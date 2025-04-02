import pandas as pd

# Load dataset
df = pd.read_csv("D:\\c_25\\ml_in_c\\nn_in_c\\mnist_train_no_header.csv")

# Separate labels (first column) and pixel values
labels = df.iloc[:, 0]  # Extract labels
pixels = df.iloc[:, 1:]  # Extract pixel values

# Apply thresholding: If value ≤ 0.5, set to 1; otherwise, set to 0
pixels = (pixels >= 0.5).astype(int)

# Combine labels and processed pixels back
df_binarized = pd.concat([labels, pixels], axis=1)

# Save without headers (for easy processing in C)
df_binarized.to_csv("mnist_train_bnn.csv", index=False, header=False, float_format='%d')

print("Saved binarized dataset (labels unchanged, pixels binarized with 0.5 threshold)!")
