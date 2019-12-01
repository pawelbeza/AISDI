# AISDI - Algorithms and Data Structures
## About The Project
This repository consists of analysis of algorithms and data structures such as sorting, dictionaries, pattern searching and pathfinding.

For every problem I implement one or more algorithms and compare its efficency with their equivalence in [STL library](https://pl.wikipedia.org/wiki/Standard_Template_Library).

## Algorithms:
1. [Sorting](#sorting)
2. [Dictionaries](#dictionaries)

<!-- Sorting -->
## [Sorting](https://en.wikipedia.org/wiki/Sorting_algorithm)
I implemented following sorting algorithms on [iterators](https://en.wikipedia.org/wiki/Iterator):
* [bubble sort](https://en.wikipedia.org/wiki/Bubble_sort)
* [merge sort](https://en.wikipedia.org/wiki/Merge_sort)
* [qucik sort](https://en.wikipedia.org/wiki/Quicksort)

Then I compared their efficency by measuring their time of execution using *small_input* and *big_input* (you can find them in *Sort* catalog).

Results:

## 1. small_input - merge sort vs bubble sort vs quick sort vs STL sort

![chart (1)](https://user-images.githubusercontent.com/43823276/69915290-aadf0000-144d-11ea-9167-bcad30b861f9.png)
The graph shows that time of execution of **bubble sort** grows as function     <a href="https://www.codecogs.com/eqnedit.php?latex=n^2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n^2" title="n^2" /></a>
 which araises from its complexity which is O(<a href="https://www.codecogs.com/eqnedit.php?latex=n^2" target="_blank"><img src="https://latex.codecogs.com/gif.latex?n^2" title="n^2" /></a>). Hovewer it is not clearly visible what are dependencies between times of execution for rest of algorithms. Therefore I tested them seperately using *big_input*.
 
 ## 2. big_input - merge sort vs quick sort vs STL sort
![chart (2)](https://user-images.githubusercontent.com/43823276/69915855-07ddb480-1454-11ea-96a1-f6e083a9d6d0.png)
As it could be predicted **STL sort** outperforms implemented **quick sort** and **merge sort** since it's not ordinary sort but hybrid sorting algorithm which means that it uses more than one sorting algorithms as a routine. However still for *big_input*(which had around *850000 words*) there was no such a big difference between times of execution of **quick sort** and **STL sort** but it would be more visible for bigger inputs. **Merge sort** was around *4* times worse than other nlogn algorithms.

## Algorithms in ascending order of their execution time:

1. STL Sort
2. Quicksort
3. Mergesort
4. Bubble Sort

---
<!-- Dictionaries -->
## [Dictionaries](https://en.wikipedia.org/wiki/Associative_array)

I implemented dictionary using following trees:

* [splay tree](https://en.wikipedia.org/wiki/Splay_tree)
* [AVL tree](https://en.wikipedia.org/wiki/AVL_tree)

Results:
All algorithms were tested by inserting and querying words from *big_input*(can be found in Dictionaries catalog) and calculating average execution time.

## Insertion - Splay Tree vs AVL Tree vs STL map
![chart (4)](https://user-images.githubusercontent.com/43823276/69920233-9159aa80-1485-11ea-942a-d11a25139929.png)
According to the diagram dictionary implemented on **splay tree** is around 10 times slower than **AVL** implementation or **STL map**. It is important to realize tat **the splay** tree is not always balanced so we may not have *logn* insertion time in particular cases. Nevertheless it seems that for bigger number of insertions it has logarithmic characteristic since access cost of the worst case is logarithmic. 

But still it's not so clear what are dependencies between **AVL tree** implementation and **STL map** so let's take a closer look at it.

## Insertion - AVL Tree vs STL map
![chart (5)](https://user-images.githubusercontent.com/43823276/69920447-5dcc4f80-1488-11ea-8e3c-d849d7c40cb3.png)
It seems that the average time of insertion is very similar but for over *70000* insertions difference between time execution becomes bigger and bigger. 

## Querying - Splay Tree vs AVL Tree vs STL map
![chart (6)](https://user-images.githubusercontent.com/43823276/69920563-e992ab80-1489-11ea-9155-891f1e258cb2.png)
Similarly to the previous charts it appears that splay tree got the worst time execution but it is probably because of tests which queried all possible words from input file. Whereas splay trees are great for querying words which are frequently accessed so didn't have chance to shine. Unfortunetely I didn't have idea how to make tests which would be more relatable to the real case scenario (surely something with frequencies of words should be done).

As it was in insertion case let's take closer look at **AVL** and **STL map** dictionaries.

## Querying - AVL Tree vs STL map
![chart (7)](https://user-images.githubusercontent.com/43823276/69920698-4c387700-148b-11ea-9073-371577b71d1a.png)
At first glance the most intriguing fact is level of noise which is visible on charts. For sure it indicates that there were a lot of queries regarding words which were inserted deepely in tree but it's strange that it appears mostly before *200000* insertions. I also tried to think about characteristics of input file which was text of *Bible*, maybe older part of *Bible* had some characteristics which would explain it in more detail.
However when it comes to differences between execution time of **AVL tree** and **STL tree** it seems that for this praticular input it seems that the average query is faster for **AVL tree**.
