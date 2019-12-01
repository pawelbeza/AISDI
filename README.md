# AISDI - Algorithms and Data Structures
## About The Project
This repository consists of analysis of algorithms and data structures such as sorting, dictionaries, pattern searching and pathfinding.

For every problem I implement one or more algorithms and compare its efficency with their equivalence in [STL library](https://pl.wikipedia.org/wiki/Standard_Template_Library).

## Algorithms:
1. [Sorting]()
2. [Dictionaries]()

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
