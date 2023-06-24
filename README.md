# Shared_Memory_in_Robo_Vision_Simulator
The code to design, develop, test, and deploy is an interactive simulator of a (simplified) typical vision system, able to track an object in a 2-D plane. This is a true example of an industrial vision system in a robotic manufacturing workshop.

## ARP-Assignment2

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#Introduction">Introduction</a></li>
    <li><a href="#Installation_and_Running">Installation_and_Running</a></li>
    <li><a href="#Documentation">Documentation</a></li>
    <li><a href="#Fauctionality">Fauctionality</a></li>
    <li><a href="#Simulation_and_Results">Simulation_and_Results</a></li>
    <li><a href="#Members">Members</a></li>
  </ol>
</details>

## Introduction
In this project, we will provide a shared memory infrastructure to implement a simulated vision system.

For this task, it is necessary to utilize a shared memory in which two processes will work concurrently, mirroring similar real-life applications. However, due to the lack of a camera, we will simulate the creation of a moving image by implementing a ncurses window. By means of arrow keys, a spot in the window will be moved to generate the illusion of a camera's perspective. 
This spot will serve as the focal point for the simulation.
The structure of the code is as follows:

![image](https://github.com/ParinazRmp/Shared_Memory_in_Robo_Vision_Simulator/assets/94115975/160aba64-20ef-4fb9-a6e2-7fd21eb8ba74)
<img src="https://user-images.githubusercontent.com/80394968/225428258-e8b9859d-d05b-42ed-b783-29340073b10f.png" width="60" />
## Installation_and_Running
### 1. ncurses installation
To install the ncurses library, simply open a terminal and type the following command:
```console
sudo apt-get install libncurses-dev
```
### 2. *libbitmap* installation and usage
To work with the bitmap library, you need to follow these steps:
1. Download the source code from [this GitHub repo](https://github.com/draekko/libbitmap.git) in your file system.
2. Navigate to the root directory of the downloaded repo and run the configuration through command ```./configure```. Configuration might take a while.  While running, it prints some messages telling which features it is checking for.
3. Type ```make``` to compile the package.
4. Run ```make install``` to install the programs and any data files and documentation.
5. Upon completing the installation, check that the files have been properly installed by navigating to ```/usr/local/lib```, where you should find the ```libbmp.so``` shared library ready for use.
6. In order to properly compile programs which use the *libbitmap* library, you first need to notify the **linker** about the location of the shared library. To do that, you can simply add the following line at the end of your ```.bashrc``` file:      
```export LD_LIBRARY_PATH="/usr/local/lib:$LD_LIBRARY_PATH"```

### 3. Compiling and running Process A and Process B
Once the installation is done, clone this repository to your desired location:
<pre><code>git clone https://github.com/ParinazRmp/Shared_Memory_in_Robo_Vision_Simulator.git </code></pre>
After you clone the repository, run this command:
<pre><code> sh run.sh </code></pre>

## Documentation
You can view the documentation [here](http://example.com/your_doxygen_docs).

## Fauctionality

## Simulation_and_Results
![ARP2](https://github.com/ParinazRmp/Shared_Memory_in_Robo_Vision_Simulator/assets/94115975/3f27c4c6-5aad-417e-96cf-c03877155c6c)

<img src="https://user-images.githubusercontent.com/80394968/225428503-ce0991e7-10c8-45f5-bb52-ab4de821c27d.png" width="60" /> 

## Members
| Github-page | Email |
|------------------|------------------|
| [Danial Sabzevari](https://github.com/dssdanial)  | s5217544@studenti.unige.it |
| [Parinaz Ramezanpour](https://github.com/ParinazRmp)  | s5214640@studenti.unige.it |
