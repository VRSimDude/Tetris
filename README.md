<a name="readme-top"></a>
# Tetris (Console)

<!-- Screenshots -->
<p align="center">
	<img src="/Screenshot/screenshot_1.jpg?raw=true" />
	<img src="/Screenshot/screenshot_2.jpg?raw=true" />
</p>

<!-- TABLE OF CONTENTS -->
<summary>Table of Contents</summary>
<ol>
  <li>
    <a href="#about-the-project">About The Project</a>
    <ul>
      <li><a href="#description">Description</a></li>
      <li><a href="#built-with">Built With</a></li>
    </ul>
  </li>
  <li>
    <a href="#getting-started">Getting Started</a>
    <ul>
      <li><a href="#prerequisites">Prerequisites</a></li>
      <li><a href="#installation">Installation</a></li>
      <li><a href="#play-the-game">Play the game</a></li>
    </ul>
  </li>
  <li><a href="#how-to-use-the-project">How to Use the Project</a>
    <ul>
      <li><a href="#keybindings">Keybindings</a></li>
    </ul>
  </li>
  <li><a href="#contributing">Contributing</a></li>
  <li><a href="#license">License</a></li>
  <li><a href="#contact">Contact</a></li>
</ol>
  
<!-- ABOUT THE PROJECT -->
## About The Project
Here are all the main informations about the project.

### Description
This project is more a private project for me to learn and practice C++ in a project. It will not be released or published at all.<br>
It is the Tetris game hopefully everyone knows but with a little twist in the mechanics.
Once a line is completed all single characters that have no other character below are falling down.
This way the player can create a chain of effects which could make a nearly lost game almost empty again.
The speed increase with the score.

### Built With
The project uses only libraries that are available on the system itself. No third party libraries will be used.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
## Getting Started
In this section is described how to start using this project to develop it and what is required to do so.

### Prerequisites
To edit and build the project Visual Studio on Windows is required currently because of the solution file.<br>
To clean the project from Visual Studio temporary files execute Clean.bat.

### Installation
1. Clone the repo
```sh
git clone https://github.com/VRSimDude/Tetris.git
```
2. open the project<br>
open Tetris.sln

### Play the game
To play the game built it in Visual Studio or start it directly from Visual Studio.<br><br>
You can also start the game without Visual Studio by download the executables for windows here:<br>
[v1.0.0 Win64](https://github.com/VRSimDude/Tetris/releases/download/v1.0.0/Executable.win64.zip)<br>
[v1.0.0 Win32](https://github.com/VRSimDude/Tetris/releases/download/v1.0.0/Executable.win32.zip)<br><br>

The size of the play area can be changed by adding one or two values to the command or the shortcut as seen here:<br>
<p align="center">
	<img src="/Screenshot/screenshot_3.jpg?raw=true" />
</p><br>
The first value is the width of the play area and the second is the height.
You can also enter no value or just the width.
The default values are 16 width and 32 height.<br>
The width has a min value of 9 and max of 32.
The height has a min value of 11 and max of 64.
All values out of this are cutted.<br><br>

<b>Important</b> is o change the size of the console in order to see the game correctly.<br><br>
To change that right click at the console window menu and click `Properties`:<br>
<p align="center">
	<img src="/Screenshot/screenshot_4.jpg?raw=true" />
</p><br><br>

And then change the `Width` and `Height` of the `Screen Buffer Size` and `Window Size`:<br>
<p align="center">
	<img src="/Screenshot/screenshot_5.jpg?raw=true" />
</p><br><br>

The width must be the given width (or default 16) plus additional 12 for the UI.<br>
The height must be the given height (or default 32) plus additional 2 for better display.<br><br>

For a better experience choose a `Font` that displays the characters more squared like the font `Raster Fonts` with a `Size` of `8x8`.<br>
That way it looks like in the screenshots.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- HOW TO USE THE PROJECT -->
## How to Use the Project
Here is described how you use the projects features.

### Keybindings
Move the current Tetromino left and right with the left and right arrow key.<br>
Move it on block down with the down arrow key.<br>
And move it immediately to the bottom with the up arrow key.<br>
Start or restart the game with Return.<br>
Exit the game with Escape.<br>

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->
## Contributing

Contributions to this project can be done by writing me.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->
## License

Distributed under the MIT License License. See `LICENSE` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

mail: [contact@marcfriedrich.com](mailto:contact@marcfriedrich.com)<br>
project link: [https://github.com/VRSimDude/Tetris](https://github.com/VRSimDude/Tetris)

<p align="right">(<a href="#readme-top">back to top</a>)</p>