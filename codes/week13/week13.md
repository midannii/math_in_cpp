
## Machine learning 1 (Java --> C++)

교수님께서 주신 iris_perceptron_main.cpp를 보완하여 새로운 데이터에 대해 logistic regression 진행하기 


## workflow

1. 버섯의 독성 유무를 판단할 수 있는 23가지의 특징이 담겨있는, 즉 23차원의 data 수집 from [kaggle](https://www.kaggle.com/uciml/mushroom-classification)
  
  
2. data(csv file)를 txt file로 변환 : `change_mushroom_txt.ipynb`

  - 이 때, ascii 를 이용하여 숫자로 변환하고, 공백을 통해 각 데이터가 구분되도록 함
  
  - 1열에서의 edible은 0, poisonous는 1로 labeling
  
3. 2에서 만들어진 `mushroom.txt`를 읽고 train과 test를 위한 input data(train_x, test_x)와 output data(train_t, test_t)로 구분한다. :  `mushroom_main.cpp`

4. logistic classification을 진행한다. :  `mushroom_main.cpp`

  - epoch : 3000
  
  - lr : 1
