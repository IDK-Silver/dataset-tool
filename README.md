# Dataset Tool

> Dataset Tool 是用來處理用於 Deep Learning 的資料集
>
> 可以把原始資料集或標記按照比例分成 Train, Valid, Test 這三個子資料集
>
> 或是把資料集的標記檔案中的 class 做偏移 ( 當前支持Darknet格式 )



# 目前功能

* 把原始資料集或標記按照比例分成 Train, Valid, Test 
* 把 Darknet 的標記中的 class 加上特定的偏移數值



# 使用範例



## 通用

* 查看說明

  ```shell
  ./dataset_tool -h
  ```
  ```shell
  ./dataset_tool split -h
  ```
    ```shell
  ./dataset_tool offset -h

* 查看版本
  ```shell
  ./dataset_tool -v
  ```
  



## 資料分割 - split

* 把 dataset資料分割成 Train, Valid, Test 這三個子資料集

  ```shell
  ./dataset_tool split ./dataset
  ```


* 把 dataset 資料按照特定比例分割成 Train, Valid, Test 這三個子資料集

  ```shell
  ./dataset_tool split ./dataset --p 0.5 0.4 0.1
  ```

* 把 dataset 資料夾及標記分割成 Train, Valid, Test 這三個子資料集

  預設 annotation 的副檔名為 xml, 可以用 --label_ext 指定別的副檔名

  ```shell
  ./dataset_tool split ./dataset --label ./dataset_annotation --label_ext txt
  ```



## 標記偏移 - offset

**<u>當前支持Darknet格式</u>**

* 標記資聊夾裡面檔案的 class 加上一個偏移數值, 並保存到輸出資料夾

  可以用 --out 指定輸出資料夾

  ```shell
  ./dataset_tool offset dataset_annotation 10 --out offset_annotation
  ```