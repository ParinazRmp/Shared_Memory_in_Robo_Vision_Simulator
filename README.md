# Shared_Memory_in_Robo_Vision_Simulator
The code to design, develop, test, and deploy is an interactive simulator of a (simplified) typical vision system, able to track an object in a 2-D plane. This is a true example of an industrial vision system in a robotic manufacturing workshop.

## ARP-Assignment2

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#Introduction">Introduction</a></li>
    <li><a href="#Installation_and_Running">Installation_and_Running</a></li>
    <li><a href="#Fauctionality">Fauctionality</a></li>
    <li><a href="#How_it_works">How_it_works</a></li>
    <li><a href="#PseudoCode">PseudoCode</a></li>
    <li><a href="#Simulation_and_Results">Simulation_and_Results</a></li>
    <li><a href="#Improving_Robot_Movement">Improving_Robot_Movement</a></li>
  </ol>
</details>

## Introduction
In this project, we will provide a shared memory infrastructure to implement a simulated vision system.

For this task, it is necessary to utilize a shared memory in which two processes will work concurrently, mirroring similar real-life applications. However, due to the lack of a camera, we will simulate the creation of a moving image by implementing a ncurses window. By means of arrow keys, a spot in the window will be moved to generate the illusion of a camera's perspective. 
This spot will serve as the focal point for the simulation.
The structure of the code is as follows:
![image](https://github.com/ParinazRmp/Shared_Memory_in_Robo_Vision_Simulator/assets/94115975/30f07d50-2b70-4d47-8164-e8442bc5309c)

