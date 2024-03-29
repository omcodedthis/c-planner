# c-planner
This program takes in input such as total duties & the number of people from the user through the terminal to plan a schedule. The program then takes these parameters from the user to generate a table where the columns are the current duty for each hour for a 24-hour day starting from 8pm the previous day and the rows are the person's name. 

## Demo

![cdemo](https://user-images.githubusercontent.com/119602009/223148167-770a8453-136f-4fe5-8ae3-d525dbbcf5ef.gif)


The table created is organised by name, showing that respective person's schedule for the 24-hour period starting from 2000. The table cells with no values indicate the 
time period from 2200 to 0600 as shown in the GIF above.

## Changelog & Future Updates
* Fixed Segmentation Faults.
* Fixed an issue where certain personnel received no breaks.
* Added the ability for duty types & total hours of this respective duty to be determined by the user.
* Added colored text to improve the distinction between duty slots.
* Reduced the number of dependencies.

## Getting Started
* Download the program using the green "<> Code" button.

* While in the folder "c-planner", use this command-line in the terminal to run it.

  ```
  ./c-planner
  ```
  
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------
<sub>*Disclaimer: This is currently a work in progress. This repository will be updated when new features have been added or when bugs have been rectified. Only stable versions of the program will be pushed as an update to this repository.*<sub/>
