# OCR_OCD_tm4c123gxl

![image](https://github.com/user-attachments/assets/14004ae8-dc09-4e92-bfd8-0205f50d9c7e)

> For now the training is done on a synthetic custom matrix with random values ,
> it has to be optimized for actual MNIST dataset (28*28).

output obtained in putty:

image dataset saved:
![image](https://github.com/user-attachments/assets/e9a44c78-1f3d-40c3-a0a4-f3a085798a3f)
![image](https://github.com/user-attachments/assets/0a389416-b35b-4ff9-a17a-b3a766603bbf)

> Data set used: https://www.kaggle.com/datasets/hojjatk/mnist-dataset?resource=download

Data distribution in CSV file:
 ![image](https://github.com/user-attachments/assets/e7ce7302-c526-4c84-bac9-047f76481313)

## Issues:
![image](https://github.com/user-attachments/assets/78617329-f100-431b-8a9c-7e19b9fbf8d2)
1. The final predicted value when passing actual data always takes the class -0 , Not sure why , maybe the weights became too insignificant. (Irrespective of the number of training).

2. The original created dataset with float ---> caused a lot of errors:
   * Loading error with size different
   * couldnt segment the headers correctly
     > So I created a binerized version of the dataset. (with thresholding ,see modify.py)

  ### CODE FLOW:
  1.  main code -> bnn_main.c
  2.  mnist_loader.c to load the image dataset.
  3.  bnn.c -> Initial implementation of bnn, without using the MNIST dataset.
     
### Approm makkale  
* The microcontroller code for tm4c123g needs some fixes , Ill do it but not today :)
* This is a group project but no one works on this other than me :/ , life is hard , ssn is bad and I am so sad .
*  I cant say anything , if I do Iam the "bad guy"
*  what kind of monstrosity is this :-0
*  I am not even going to think about it as it could make me get "retha kodhipu"
*  Actlin ma'am Kaythry ma'am ,over here!
