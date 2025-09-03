# OCR_OCD_tm4c123gxl
(ML Mini Project sem6 )

![image](https://github.com/user-attachments/assets/14004ae8-dc09-4e92-bfd8-0205f50d9c7e)

> it has to be optimized for actual MNIST dataset (28*28). To get image input in that scale.

output obtained in putty:

image dataset saved:
![image](https://github.com/user-attachments/assets/e9a44c78-1f3d-40c3-a0a4-f3a085798a3f)
![image](https://github.com/user-attachments/assets/0a389416-b35b-4ff9-a17a-b3a766603bbf)

> Data set used: https://www.kaggle.com/datasets/hojjatk/mnist-dataset?resource=download

Data distribution in CSV file:
 ![image](https://github.com/user-attachments/assets/e7ce7302-c526-4c84-bac9-047f76481313)

## Issues:
![image](https://github.com/user-attachments/assets/78617329-f100-431b-8a9c-7e19b9fbf8d2)
1. The final predicted value when passing actual data mostly takes the class -0 , Not sure why , maybe the weights became too insignificant. (Irrespective of the number of training).
2. Instead of 0.5 > -> 1 and 0.5 < -->0 ,more  moderation ,to reduce the threshold ?

3. The original created dataset with float ---> caused a lot of errors:
   * Loading error with size different
   * couldnt segment the headers correctly
     > So I created a binerized version of the dataset. (with thresholding ,see modify.py)
     > Converting the dataset to binary numbers of 0,1.
   * Lesser number of epoches and lesser performance as the computation is on the edge.

  ### CODE FLOW:
  1.  main code -> bnn_main.c (Loads input from mnist saved as csv file.)
  2.  mnist_loader.c to load the image dataset.
  3.  bnn.c -> Initial implementation of bnn, without using the MNIST dataset.
  4.  main.c implementation of bnn model in TM4C123G board ,which takes dataset for training and image input through uart and processes it.
  5.  Produces the output and prints the respective classes.
     

* To implement the loading of weights to the board --> The current one works by training ON the board . Passing of input data through uart and training on it.
* Passing of weights calculated or Reading of the weights from a memory source --> Seems like an easier/more optimized way to improve accuracy.
  
  -> https://stackoverflow.com/questions/56855107/how-do-i-get-weights-and-biases-from-my-model
  
  -> https://github.com/keras-team/tf-keras/issues/333
  
  -> https://bernsteinbear.com/blog/compiling-ml-models/

  ### Note:
  * calculated accuracy : 68 -70 percent ,as the training takes place in the microcontroller.
  * Precision 0.3 ish . 
 
    ### Future work:
  * Using of CNN or a more suitable structure can improve performance.
  * Better DSP algorithms ? 
  * Passing input image via camera and not as a matrix of numbers.
  * Passing the weights instead of setting up the training in the microcontroller board.
  
